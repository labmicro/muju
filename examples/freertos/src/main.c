/************************************************************************************************
Copyright (c) 2022-2023, Laboratorio de Microprocesadores
Facultad de Ciencias Exactas y Tecnología, Universidad Nacional de Tucumán
https://www.microprocesadores.unt.edu.ar/

Copyright (c) 2022-2023, Esteban Volentini <evolentini@herrera.unt.edu.ar>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

/** @file
 ** @brief Simple sample of use FreeROTS with MUJU hal functions
 **
 ** @addtogroup sample-freertos FreeRTOS Sample
 ** @ingroup samples
 ** @brief Samples applications with MUJU Framwork
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "bsp.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <string.h>

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/**
 * @brief Enumeration with color sequence of RGB led
 */
typedef enum rgb_color_e {
    LED_RED_ON = 0, /**< Red led is On */
    LED_RED_OFF,    /**< Red led is Off */
    LED_GREEN_ON,   /**< Green led is On */
    LED_GREEN_OFF,  /**< Green led is Off */
    LED_BLUE_ON,    /**< Blue led is On */
    LED_BLUE_OFF,   /**< Blue led is Off */
} rgb_color_t;

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/**
 * @brief Function to handle events of serial port used as console by board
 *
 * @param  console  Pointer to structure with descriptor of serial port that raises the event
 * @param  status   Pointer to structure with flags that raises the event
 * @param  data     Pointer to user data declared when handler event has installed
 */
static void ConsoleEvent(hal_sci_t console, sci_status_t status, void * data);

/**
 * @brief Function to make a blocking sending of a string through the serial port used as console
 *
 * @param  console  Pointer to structure with descriptor of serial port used as console
 * @param  message  Pointer to string to send by serial port used as console
 */
static void ConsoleSend(hal_sci_t console, char const * message);

/**
 * @brief Function to flash RGB led in sequence
 *
 * @param  object   Pointer to board structure, used as parameter when task created
 */
static void FlashTask(void * object);

/**
 * @brief Function to switch on and off a led with two keys
 *
 * @param  object   Pointer to board structure, used as parameter when task created
 */
static void SwitchTask(void * object);

/**
 * @brief Function to switch on and off a led with a single key
 *
 * @param  object   Pointer to board structure, used as parameter when task created
 */
static void ToggleTask(void * object);

/**
 * @brief Function to handle events of gpio bit used by a key
 *
 * @param  gpio     Gpio input used by the key that rise event
 * @param  rissing  Flag to indicate if is an rissing edge or and falling edge
 * @param  data     Pointer to board structure, used as parameter when handler installed
 */
static void KeyEvent(hal_gpio_bit_t gpio, bool rissing, void * object);

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/**
 * @brief Constant with led on message to send by console
 */
static const char LED_IS_ON[] = "Led 1 is on\n";

/**
 * @brief Constant with led off message to send by console
 */
static const char LED_IS_OFF[] = "Led 1 is off\n";

/**
 * @brief Constant with led toggle message to send by console
 */
static const char LED_TOGGLED[] = "Led 2 was taggled\n";

/**
 * @brief Mutex to protect serial console transmission
 */
static SemaphoreHandle_t console_mutex;

/* === Private function implementation ========================================================= */

static void ConsoleEvent(hal_sci_t console, sci_status_t status, void * data) {
    board_t board = data;
    char key;
    uint8_t received;

    if (status->data_ready) {
        received = SciReceiveData(console, &key, sizeof(key));
        if (received) {
            if (key == '1') {
                GpioSetState(board->led_1, true);
            } else if (key == '2') {
                GpioSetState(board->led_1, false);
            } else if (key == '3') {
                GpioBitToogle(board->led_2);
            }
        }
    }
}

static void ConsoleSend(hal_sci_t console, char const * message) {
    uint8_t pending = strlen(message);
    uint8_t sended;

    xSemaphoreTake(console_mutex, portMAX_DELAY);
    while (pending) {
        sended = SciSendData(console, message, pending);
        message += sended;
        pending -= sended;
    }
    xSemaphoreGive(console_mutex);
}

static void FlashTask(void * object) {
    static rgb_color_t state = LED_BLUE_OFF;

    board_t board = object;
    led_rgb_t led = board->led_rgb;

    while (true) {
        state = (state + 1) % (LED_BLUE_OFF + 1);
        switch (state) {
        case LED_RED_ON:
            GpioBitClear(led->green);
            GpioBitClear(led->blue);
            GpioBitSet(led->red);
            break;
        case LED_GREEN_ON:
            GpioBitClear(led->red);
            GpioBitClear(led->blue);
            GpioBitSet(led->green);
            break;
        case LED_BLUE_ON:
            GpioBitClear(led->red);
            GpioBitClear(led->green);
            GpioBitSet(led->blue);
            break;
        default:
            GpioBitClear(led->red);
            GpioBitClear(led->green);
            GpioBitClear(led->blue);
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

static void SwitchTask(void * object) {
    board_t board = object;
    hal_gpio_bit_t key_on = board->tec_1;
    hal_gpio_bit_t key_off = board->tec_2;
    hal_gpio_bit_t led = board->led_1;

    while (true) {
        if (GpioGetState(key_on) == 0) {
            if (GpioGetState(led) != true) {
                GpioSetState(led, true);
                ConsoleSend(board->console, LED_IS_ON);
            }
        }
        if (GpioGetState(key_off) == 0) {
            if (GpioGetState(led) != false) {
                GpioSetState(led, false);
                ConsoleSend(board->console, LED_IS_OFF);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(150));
    }
}

static void ToggleTask(void * object) {
    board_t board = object;
    hal_gpio_bit_t key = board->tec_3;
    hal_gpio_bit_t led = board->led_2;
    static bool last_state = false;
    bool current_state;

    while (true) {
        current_state = (GpioGetState(key) == 0);
        if ((current_state) && (!last_state)) {
            GpioBitToogle(led);
            ConsoleSend(board->console, LED_TOGGLED);
        }
        last_state = current_state;
        vTaskDelay(pdMS_TO_TICKS(150));
    }
}

static void KeyEvent(hal_gpio_bit_t gpio, bool rissing, void * object) {
    board_t board = object;
    hal_gpio_bit_t led = board->led_3;

    if (!rissing) {
        GpioSetState(led, true);
    } else {
        GpioSetState(led, false);
    }
}

/* === Public function implementation ========================================================= */

int main(void) {
    /* Inicializaciones y configuraciones de dispositivos */
    board_t board = BoardCreate();

    /* Creación de las tareas */
    console_mutex = xSemaphoreCreateMutex();

    xTaskCreate(FlashTask, "FlashLed", 256, (void *)board, tskIDLE_PRIORITY + 2, NULL);
    xTaskCreate(ToggleTask, "ToogleLed", 256, (void *)board, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(SwitchTask, "SwitchLed", 256, (void *)board, tskIDLE_PRIORITY + 1, NULL);

    SciSetEventHandler(board->console, ConsoleEvent, (void *)board);
    GpioSetEventHandler(board->tec_4, KeyEvent, (void *)board, true, true);

    /* Arranque del sistema operativo */
    vTaskStartScheduler();

    /* vTaskStartScheduler solo retorna si se detiene el sistema operativo */
    while (true) {
    }

    /* El valor de retorno es solo para evitar errores en el compilador*/
    return 0;
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
