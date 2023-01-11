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
 ** @brief Simple sample of use MUJU hal functions
 **
 ** @addtogroup sample-hal HAL Sample
 ** @ingroup samples
 ** @brief Samples applications with MUJU Framwork
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "board.h"
#include "hal.h"
#include <string.h>

/* === Macros definitions ====================================================================== */

#if !defined(EDU_CIAA_NXP) && !defined(POSIX)
#error "This program does not have support for the selected board"
#endif

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

/**
 * @brief Structure with gpio outputs to drive an RGB led
 */
typedef struct led_rgb_s {
    hal_gpio_bit_t red;   /**< Gpio output used to drive red channel of RGB led */
    hal_gpio_bit_t green; /**< Gpio output used to drive green channel of RGB led */
    hal_gpio_bit_t blue;  /**< Gpio output used to drive blue channel of RGB led */
} const * const led_rgb_t;

/**
 * @brief Structure with gpio terminals usted by board
 */
typedef struct board_s {
    struct led_rgb_s led_rgb; /**< Structure with gpio output used by RGB led */
    hal_gpio_bit_t led_1;     /**< Gpio output used to drive led 1 on board */
    hal_gpio_bit_t led_2;     /**< Gpio output used to drive led 2 on board */
    hal_gpio_bit_t led_3;     /**< Gpio output used to drive led 3 on board */
    hal_gpio_bit_t tec_1;     /**< Gpio output used to read status of key 1 on board */
    hal_gpio_bit_t tec_2;     /**< Gpio output used to read status of key 2 on board */
    hal_gpio_bit_t tec_3;     /**< Gpio output used to read status of key 3 on board */
    hal_gpio_bit_t tec_4;     /**< Gpio output used to read status of key 4 on board */
    hal_sci_t console;        /**< Serial port used as console on board */
} const * const board_t;

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/**
 * @brief Function to initialize the board and create an descriptor to his resources
 *
 * @return  board_t  Pointer to descriptor with board resources
 */
static board_t BoardCreate(void);

/**
 * @brief Function to handle system timer events
 *
 * @param  object   Pointer to boolean variable to signal to main loop a new tick
 */
static void TickEvent(void * object);

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
static void FlashLed(led_rgb_t led, hal_sci_t console);

/**
 * @brief Function to switch on and off a led with two keys
 *
 * @param  key_on   Gpio input used by the key that turns on the led
 * @param  key_off  Gpio input used by the key that turns off the led
 * @param  led      Gpio output used by the led drived by the keys
 */
static void SwitchLed(hal_gpio_bit_t key_on, hal_gpio_bit_t key_off, hal_gpio_bit_t led);

/**
 * @brief Function to switch on and off a led with a single key
 *
 * @param  key      Gpio input used by the key that turn on and off the led
 * @param  led      Gpio output used by the led drived by the key
 */
static void ToggleLed(hal_gpio_bit_t key, hal_gpio_bit_t led);

/**
 * @brief Function to turn on a led while a key is pressed
 *
 * @param  key      Gpio input used by the key that turn on the led
 * @param  led      Gpio output used by the led drived by the key
 */
static void TestLed(hal_gpio_bit_t key, hal_gpio_bit_t led);

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

static board_t BoardCreate(void) {
    static const struct hal_sci_line_s console_config = {
        .baud_rate = 115200,
        .data_bits = 8,
        .parity = HAL_SCI_NO_PARITY,
    };
    struct hal_sci_pins_s console_pins = {0};
    static struct board_s board;

#ifdef EDU_CIAA_NXP
    board.led_rgb.red = HAL_GPIO5_0;
    board.led_rgb.green = HAL_GPIO5_1;
    board.led_rgb.blue = HAL_GPIO5_2;

    board.led_1 = HAL_GPIO0_14;
    board.led_2 = HAL_GPIO1_11;
    board.led_3 = HAL_GPIO1_12;

    board.tec_1 = HAL_GPIO0_4;
    board.tec_2 = HAL_GPIO0_8;
    board.tec_3 = HAL_GPIO0_9;
    board.tec_4 = HAL_GPIO1_9;

    board.console = HAL_SCI_USART2;
    console_pins.txd_pin = HAL_PIN_P7_1;
    console_pins.rxd_pin = HAL_PIN_P7_2;
#elif POSIX
    board.led_rgb.red = HAL_GPIO3_7;
    board.led_rgb.green = HAL_GPIO3_6;
    board.led_rgb.blue = HAL_GPIO3_5;

    board.led_1 = HAL_GPIO3_2;
    board.led_2 = HAL_GPIO3_1;
    board.led_3 = HAL_GPIO3_0;

    board.tec_1 = HAL_GPIO0_0;
    board.tec_2 = HAL_GPIO0_1;
    board.tec_3 = HAL_GPIO0_2;
    board.tec_4 = HAL_GPIO0_3;
#endif
    BoardSetup();

    GpioSetDirection(board.led_rgb.red, true);
    GpioSetDirection(board.led_rgb.green, true);
    GpioSetDirection(board.led_rgb.blue, true);

    GpioSetDirection(board.led_1, true);
    GpioSetDirection(board.led_2, true);
    GpioSetDirection(board.led_3, true);

    GpioSetDirection(board.tec_1, false);
    GpioSetDirection(board.tec_2, false);
    GpioSetDirection(board.tec_3, false);
    GpioSetDirection(board.tec_4, false);

    SciSetConfig(board.console, &console_config, &console_pins);
    return &board;
}

static void TickEvent(void * object) {
    *((bool *)object) = true;
}

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

static void FlashLed(led_rgb_t led, hal_sci_t console) {
    static int divisor = 0;
    static rgb_color_t state = LED_BLUE_OFF;

    divisor++;
    if (divisor == 500) {
        divisor = 0;
        state = (state + 1) % (LED_BLUE_OFF + 1);

        switch (state) {
        case LED_RED_ON:
            GpioBitClear(led->green);
            GpioBitClear(led->blue);
            GpioBitSet(led->red);
            ConsoleSend(console, "RED Channel of RGB led is on\n");
            break;
        case LED_GREEN_ON:
            GpioBitClear(led->red);
            GpioBitClear(led->blue);
            GpioBitSet(led->green);
            ConsoleSend(console, "GREEN Channel of RGB led is on\n");
            break;
        case LED_BLUE_ON:
            GpioBitClear(led->red);
            GpioBitClear(led->green);
            GpioBitSet(led->blue);
            ConsoleSend(console, "BLUE Channel of RGB led is on\n");
            break;
        default:
            GpioBitClear(led->red);
            GpioBitClear(led->green);
            GpioBitClear(led->blue);
            ConsoleSend(console, "All Channels of RGB led are off\n");
            break;
        }
    }
}

static void SwitchLed(hal_gpio_bit_t key_on, hal_gpio_bit_t key_off, hal_gpio_bit_t led) {
    if (GpioGetState(key_on) == 0) {
        GpioSetState(led, true);
    }
    if (GpioGetState(key_off) == 0) {
        GpioSetState(led, false);
    }
}

static void ToggleLed(hal_gpio_bit_t key, hal_gpio_bit_t led) {
    static bool last_state = false;
    bool current_state;

    current_state = (GpioGetState(key) == 0);
    if ((current_state) && (!last_state)) {
        GpioBitToogle(led);
    }
    last_state = current_state;
}

static void TestLed(hal_gpio_bit_t key, hal_gpio_bit_t led) {
    if (GpioGetState(key) == 0) {
        GpioSetState(led, true);
    } else {
        GpioSetState(led, false);
    }
}

/* === Public function implementation ========================================================= */

int main(void) {
    int divisor = 0;
    volatile bool new_tick = false;
    board_t board = BoardCreate();

    TickStart(TickEvent, (void *)&new_tick, 1000);
    SciSetEventHandler(board->console, ConsoleEvent, (void *)board);

    while (true) {
        while (!new_tick) {
            __asm("NOP");
        }
        new_tick = false;

        FlashLed(&board->led_rgb, board->console);

        divisor++;
        if (divisor == 150) {
            divisor = 0;
            SwitchLed(board->tec_1, board->tec_2, board->led_1);
            ToggleLed(board->tec_3, board->led_2);
            TestLed(board->tec_4, board->led_3);
        }
    }
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
