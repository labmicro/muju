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
 ** @brief Digital inputs/outputs on posix implementation
 **
 ** @addtogroup posix Posix
 ** @ingroup hal
 ** @brief Posix SOC Hardware abstraction layer
 ** @cond INTERNAL
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "soc_gpio.h"
#include <stdio.h>
#include <pthread.h>
#include <termios.h>
#include <unistd.h>

/* === Macros definitions ====================================================================== */

/**
 * @brief Macro to generate the name of an descriptor from the gpio port and bit
 */
#define GPIO_NAME(PORT, BIT) HAL_GPIO##PORT##_##BIT

/**
 * @brief Macro to define an gpio descriptor
 */
#define GPIO_BIT(GPIO, BIT)                                                                        \
    GPIO_NAME(GPIO, BIT) = &(struct hal_gpio_bit_s) { .gpio = GPIO, .bit = BIT }

/* === Private data type declarations ========================================================== */

/**
 * @brief Structure with the gpio terminal descriptor
 */
struct hal_gpio_bit_s {
    uint8_t gpio : 3; /**< Number of GPIO port */
    uint8_t bit : 5;  /**< Number of GPIO terminal in port */
};

/**
 * @brief Structure to store a gpio bit event handler
 */
typedef struct event_handler_s {
    hal_gpio_event_t handler; /**< Function to call on the gpio bits events */
    void * object;            /**< Pointer to user data sended as parameter in handler calls */
    bool rising : 1;          /**< Flag to indicate if rissig edge raises an event */
    bool falling : 1;         /**< Flag to indicate if falling edge raises an event */
} * event_handler_t;

/* === Private variable declarations =========================================================== */

/**
 * @brief Variable to maintain the state of the emulated gpio terminals
 */
static uint8_t gpio_emulation[4];

/**
 * @brief Vector to store the event handlers of the gpio bits
 */
static struct event_handler_s event_handlers[32] = {0};

/* === Private function declarations =========================================================== */

/**
 * @brief Function to implement a main loop of a thread to scan keyboard
 *
 * @param _         Pointer to initial data, required by function prototype, unused
 * @return void*    Pointer to result data, required by function prototype, unused
 */
static void * KeyboardThread(void * _);

/**
 * @brief Function to draw on screen initial state of emulated gpio terminals
 */
void DrawStatus(void);

/**
 * @brief Function to refresh on screen current state of one emulated gpio terminal
 *
 * @param  gpio     Pointer to the structure with the gpio terminal descriptor
 */
void RefreshStatus(hal_gpio_bit_t gpio);

/* === Public variable definitions ============================================================= */

/**
 * @addtogroup posixGpio GPIO Constants
 * @brief Constant for gpio terminals on board
 * @{
 */
const hal_gpio_bit_t GPIO_BIT(0, 0); /**< Constant to define Bit 0 on GPIO 0 */
const hal_gpio_bit_t GPIO_BIT(0, 1); /**< Constant to define Bit 1 on GPIO 0 */
const hal_gpio_bit_t GPIO_BIT(0, 2); /**< Constant to define Bit 2 on GPIO 0 */
const hal_gpio_bit_t GPIO_BIT(0, 3); /**< Constant to define Bit 3 on GPIO 0 */
const hal_gpio_bit_t GPIO_BIT(0, 4); /**< Constant to define Bit 4 on GPIO 0 */
const hal_gpio_bit_t GPIO_BIT(0, 5); /**< Constant to define Bit 5 on GPIO 0 */
const hal_gpio_bit_t GPIO_BIT(0, 6); /**< Constant to define Bit 6 on GPIO 0 */
const hal_gpio_bit_t GPIO_BIT(0, 7); /**< Constant to define Bit 7 on GPIO 0 */

const hal_gpio_bit_t GPIO_BIT(1, 0); /**< Constant to define Bit 0 on GPIO 1 */
const hal_gpio_bit_t GPIO_BIT(1, 1); /**< Constant to define Bit 1 on GPIO 1 */
const hal_gpio_bit_t GPIO_BIT(1, 2); /**< Constant to define Bit 2 on GPIO 1 */
const hal_gpio_bit_t GPIO_BIT(1, 3); /**< Constant to define Bit 3 on GPIO 1 */
const hal_gpio_bit_t GPIO_BIT(1, 4); /**< Constant to define Bit 4 on GPIO 1 */
const hal_gpio_bit_t GPIO_BIT(1, 5); /**< Constant to define Bit 5 on GPIO 1 */
const hal_gpio_bit_t GPIO_BIT(1, 6); /**< Constant to define Bit 6 on GPIO 1 */
const hal_gpio_bit_t GPIO_BIT(1, 7); /**< Constant to define Bit 7 on GPIO 1 */

const hal_gpio_bit_t GPIO_BIT(2, 0); /**< Constant to define Bit 0 on GPIO 2 */
const hal_gpio_bit_t GPIO_BIT(2, 1); /**< Constant to define Bit 1 on GPIO 2 */
const hal_gpio_bit_t GPIO_BIT(2, 2); /**< Constant to define Bit 2 on GPIO 2 */
const hal_gpio_bit_t GPIO_BIT(2, 3); /**< Constant to define Bit 3 on GPIO 2 */
const hal_gpio_bit_t GPIO_BIT(2, 4); /**< Constant to define Bit 4 on GPIO 2 */
const hal_gpio_bit_t GPIO_BIT(2, 5); /**< Constant to define Bit 5 on GPIO 2 */
const hal_gpio_bit_t GPIO_BIT(2, 6); /**< Constant to define Bit 6 on GPIO 2 */
const hal_gpio_bit_t GPIO_BIT(2, 7); /**< Constant to define Bit 7 on GPIO 2 */

const hal_gpio_bit_t GPIO_BIT(3, 0); /**< Constant to define Bit 0 on GPIO 3 */
const hal_gpio_bit_t GPIO_BIT(3, 1); /**< Constant to define Bit 1 on GPIO 3 */
const hal_gpio_bit_t GPIO_BIT(3, 2); /**< Constant to define Bit 2 on GPIO 3 */
const hal_gpio_bit_t GPIO_BIT(3, 3); /**< Constant to define Bit 3 on GPIO 3 */
const hal_gpio_bit_t GPIO_BIT(3, 4); /**< Constant to define Bit 4 on GPIO 3 */
const hal_gpio_bit_t GPIO_BIT(3, 5); /**< Constant to define Bit 5 on GPIO 3 */
const hal_gpio_bit_t GPIO_BIT(3, 6); /**< Constant to define Bit 6 on GPIO 3 */
const hal_gpio_bit_t GPIO_BIT(3, 7); /**< Constant to define Bit 7 on GPIO 3 */
/** @} End of group posixGpio */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

static void * KeyboardThread(void * _) {
    struct termios ttystate;
    struct hal_gpio_bit_s gpio = {.gpio = 0, .bit = 0};
    char key;

    tcgetattr(STDIN_FILENO, &ttystate);
    ttystate.c_lflag &= (~ICANON & ~ECHO);
    ttystate.c_cc[VMIN] = 1;
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

    while (true) {
        key = getchar();
        if ((key >= '1') && (key <= '8')) {
            gpio.gpio = 0;
            gpio.bit = key - '1';
            GpioBitToogle(&gpio);

            event_handler_t descriptor = &event_handlers[8 * gpio.gpio + gpio.bit];
            if (descriptor->handler != NULL) {
                if (GpioGetState(&gpio)) {
                    if (descriptor->rising) {
                        descriptor->handler(&gpio, true, descriptor->object);
                    }
                } else {
                    if (descriptor->falling) {
                        descriptor->handler(&gpio, false, descriptor->object);
                    }
                }
            }
        }
    }
    return 0;
}

void DrawStatus(void) {
    static const char DRAW_INIT[] = "\033[2J\033[1;1H";
    static const char DRAW_BIT[] = "%d=\033[1;31m%d\033[0m";
    static const char DRAW_END[] = "\033[5A\n";

    int gpio, bit;

    printf(DRAW_INIT);
    for (gpio = 0; gpio < 4; gpio++) {
        printf("GPIO %d: ", gpio);
        for (bit = 7; bit >= 0; bit--) {
            printf(DRAW_BIT, bit, (gpio_emulation[gpio] >> (bit)) & 0x01);
            if (bit > 0) {
                printf(", ");
            }
        }
        printf("\n");
    }
    printf(DRAW_END);
}

void RefreshStatus(hal_gpio_bit_t gpio) {
    static const char DRAW_BIT[] = "\033[%d;%dH\033[1;%dm%d\033[0m";

    uint8_t value = (gpio_emulation[gpio->gpio] >> (gpio->bit)) & 0x01;

    printf(DRAW_BIT, gpio->gpio + 1, 46 - 5 * gpio->bit, value ? 32 : 31, value);
    fflush(stdout);
}

/* === Public function implementation ========================================================== */

void GpioSetDirection(hal_gpio_bit_t gpio, bool output) {
    static bool initied_status = false;
    static pthread_t thread;

    if (!initied_status) {
        initied_status = true;
        DrawStatus();
        pthread_create(&thread, NULL, KeyboardThread, NULL);
    }
    if (!output) {
        GpioBitSet(gpio);
    }
}

bool GpioGetState(hal_gpio_bit_t gpio) {
    bool result = false;
    if (gpio) {
        result = (gpio_emulation[gpio->gpio] & (1 << gpio->bit)) != 0;
    }
    return result;
}

void GpioSetState(hal_gpio_bit_t gpio, bool state) {
    if (state) {
        GpioBitSet(gpio);
    } else {
        GpioBitClear(gpio);
    }
}

void GpioBitSet(hal_gpio_bit_t gpio) {
    if (gpio) {
        gpio_emulation[gpio->gpio] |= (1 << gpio->bit);
        RefreshStatus(gpio);
    }
}

void GpioBitClear(hal_gpio_bit_t gpio) {
    if (gpio) {
        gpio_emulation[gpio->gpio] &= ~(1 << gpio->bit);
        RefreshStatus(gpio);
    }
}

void GpioBitToogle(hal_gpio_bit_t gpio) {
    if (gpio) {
        gpio_emulation[gpio->gpio] ^= (1 << gpio->bit);
        RefreshStatus(gpio);
    }
}

void GpioSetEventHandler(hal_gpio_bit_t gpio, hal_gpio_event_t handler, void * object, bool rising,
                         bool falling) {

    uint8_t index = 8 * gpio->gpio + gpio->bit;
    event_handler_t descriptor = &event_handlers[index];

    descriptor->handler = handler;
    descriptor->object = object;
    descriptor->rising = rising;
    descriptor->falling = falling;
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen
 ** @endcond */
