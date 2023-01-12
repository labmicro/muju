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
 * @param  led      Pointer to structure with gpio outputs used by rgb led
 * @param  console  Pointer to structure with serial port used by console
 */
static void FlashLed(void * object);

/**
 * @brief Function to switch on and off a led with two keys
 *
 * @param  key_on   Gpio input used by the key that turns on the led
 * @param  key_off  Gpio input used by the key that turns off the led
 * @param  led      Gpio output used by the led drived by the keys
 */
static void SwitchLed(void * object);

/**
 * @brief Function to switch on and off a led with a single key
 *
 * @param  key      Gpio input used by the key that turn on and off the led
 * @param  led      Gpio output used by the led drived by the key
 */
static void ToggleLed(void * object);

/**
 * @brief Function to turn on a led while a key is pressed
 *
 * @param  key      Gpio input used by the key that turn on the led
 * @param  led      Gpio output used by the led drived by the key
 */
static void TestLed(void * object);

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

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

    while (pending) {
        sended = SciSendData(console, message, pending);
        message += sended;
        pending -= sended;
    }
}

static void FlashLed(void * object) {
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

static void SwitchLed(void * object) {
    board_t board = object;
    hal_gpio_bit_t key_on = board->tec_1;
    hal_gpio_bit_t key_off = board->tec_2;
    hal_gpio_bit_t led = board->led_1;

    while (true) {
        if (GpioGetState(key_on) == 0) {
            GpioSetState(led, true);
        }
        if (GpioGetState(key_off) == 0) {
            GpioSetState(led, false);
        }
        vTaskDelay(pdMS_TO_TICKS(150));
    }
}

static void ToggleLed(void * object) {
    board_t board = object;
    hal_gpio_bit_t key = board->tec_3;
    hal_gpio_bit_t led = board->led_2;
    static bool last_state = false;
    bool current_state;

    while (true) {
        current_state = (GpioGetState(key) == 0);
        if ((current_state) && (!last_state)) {
            GpioBitToogle(led);
        }
        last_state = current_state;
        vTaskDelay(pdMS_TO_TICKS(150));
    }
}

static void TestLed(void * object) {
    board_t board = object;
    hal_gpio_bit_t key = board->tec_4;
    hal_gpio_bit_t led = board->led_3;

    while (true) {
        if (GpioGetState(key) == 0) {
            GpioSetState(led, true);
        } else {
            GpioSetState(led, false);
        }
        vTaskDelay(pdMS_TO_TICKS(150));
    }
}

/* === Public function implementation ========================================================= */

int main(void) {
    /* Inicializaciones y configuraciones de dispositivos */
    board_t board = BoardCreate();

    /* Creación de las tareas */
    xTaskCreate(FlashLed, "FlashLed", 256, (void *)board, tskIDLE_PRIORITY + 2, NULL);
    xTaskCreate(ToggleLed, "ToogleLed", 256, (void *)board, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(SwitchLed, "SwitchLed", 256, (void *)board, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(TestLed, "TestLed", 256, (void *)board, tskIDLE_PRIORITY + 1, NULL);

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
