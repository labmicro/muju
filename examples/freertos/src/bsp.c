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
 ** @brief Board support hardware abstraction layer implementation
 **
 ** @addtogroup sample-freertos FreeRTOS Sample
 ** @ingroup samples
 ** @brief Samples applications with MUJU Framwork
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "bsp.h"
#include "board.h"
#include <string.h>

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

static board_t AssignResources(struct hal_sci_pins_s * console_pins) {
    static struct board_s board = {0};

#ifdef EDU_CIAA_NXP
    board.led_rgb[0].red = HAL_GPIO5_0;
    board.led_rgb[0].green = HAL_GPIO5_1;
    board.led_rgb[0].blue = HAL_GPIO5_2;

    board.led_1 = HAL_GPIO0_14;
    board.led_2 = HAL_GPIO1_11;
    board.led_3 = HAL_GPIO1_12;

    board.tec_1 = HAL_GPIO0_4;
    board.tec_2 = HAL_GPIO0_8;
    board.tec_3 = HAL_GPIO0_9;
    board.tec_4 = HAL_GPIO1_9;

    board.console = HAL_SCI_USART2;
    console_pins->txd_pin = HAL_PIN_P7_1;
    console_pins->rxd_pin = HAL_PIN_P7_2;
#elif BLUE_PILL
    board.led_2 = HAL_GPIO_PB9;
    board.tec_3 = HAL_GPIO_PB13;

    board.console = HAL_SCI_USART1;
    console_pins->txd_pin = HAL_PIN_PA9;
    console_pins->rxd_pin = HAL_PIN_PA10;
#elif POSIX
    board.led_rgb[0].red = HAL_GPIO3_7;
    board.led_rgb[0].green = HAL_GPIO3_6;
    board.led_rgb[0].blue = HAL_GPIO3_5;

    board.led_1 = HAL_GPIO3_2;
    board.led_2 = HAL_GPIO3_1;
    board.led_3 = HAL_GPIO3_0;

    board.tec_1 = HAL_GPIO0_0;
    board.tec_2 = HAL_GPIO0_1;
    board.tec_3 = HAL_GPIO0_2;
    board.tec_4 = HAL_GPIO0_3;
#else
#error "This program does not have support for the selected board"
#endif
    return (board_t)&board;
}

/* === Public function implementation ========================================================= */

board_t BoardCreate(void) {
    static const struct hal_sci_line_s console_config = {
        .baud_rate = 115200,
        .data_bits = 8,
        .parity = HAL_SCI_NO_PARITY,
    };
    struct hal_sci_pins_s console_pins = {0};

    BoardSetup();
    board_t board = AssignResources(&console_pins);

    GpioSetDirection(board->led_rgb->red, true);
    GpioSetDirection(board->led_rgb->green, true);
    GpioSetDirection(board->led_rgb->blue, true);

    GpioSetDirection(board->led_1, true);
    GpioSetDirection(board->led_2, true);
    GpioSetDirection(board->led_3, true);

    GpioSetDirection(board->tec_1, false);
    GpioSetDirection(board->tec_2, false);
    GpioSetDirection(board->tec_3, false);
    GpioSetDirection(board->tec_4, false);

    SciSetConfig(board->console, &console_config, &console_pins);
    return board;
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
