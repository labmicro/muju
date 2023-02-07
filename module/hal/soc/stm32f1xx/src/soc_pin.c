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
 ** @brief Chip pins on STM32F1xx implementation
 **
 ** @addtogroup stmf32f1xx STM32F1xx
 ** @ingroup hal
 ** @brief STM32F1xx SOC Hardware abstraction layer
 ** @cond INTERNAL
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "soc_pin.h"
#include "stm32f1xx_hal.h"

/* === Macros definitions ====================================================================== */

/**
 * @brief Macro to generate the name of an descriptor from the gpio port and bit
 */
#define PIN_NAME(PORT, PIN) HAL_PIN_P##PORT##PIN

/**
 * @brief Macro to generate the name of an descriptor from the gpio port and bit
 */
#define PORT_NAME(PORT) HAL_PORT_##PORT

/**
 * @brief Macro to define an gpio descriptor
 */
#define CHIP_PIN(PORT, PIN)                                                                        \
    PIN_NAME(PORT, PIN) = &(struct hal_chip_pin_s) { .port = PORT_NAME(PORT), .pin = PIN }

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/**
 * @addtogroup stmf32f1xx PIN Constants
 * @brief Constant for chip pin on board
 * @{
 */
const hal_chip_pin_t CHIP_PIN(A, 0);  /**< Constant to define Pin 0 on chip port A */
const hal_chip_pin_t CHIP_PIN(A, 1);  /**< Constant to define Pin 1 on chip port A */
const hal_chip_pin_t CHIP_PIN(A, 2);  /**< Constant to define Pin 2 on chip port A */
const hal_chip_pin_t CHIP_PIN(A, 3);  /**< Constant to define Pin 3 on chip port A */
const hal_chip_pin_t CHIP_PIN(A, 4);  /**< Constant to define Pin 4 on chip port A */
const hal_chip_pin_t CHIP_PIN(A, 5);  /**< Constant to define Pin 6 on chip port A */
const hal_chip_pin_t CHIP_PIN(A, 6);  /**< Constant to define Pin 7 on chip port A */
const hal_chip_pin_t CHIP_PIN(A, 7);  /**< Constant to define Pin 8 on chip port A */
const hal_chip_pin_t CHIP_PIN(A, 8);  /**< Constant to define Pin 9 on chip port A */
const hal_chip_pin_t CHIP_PIN(A, 9);  /**< Constant to define Pin 10 on chip port A */
const hal_chip_pin_t CHIP_PIN(A, 10); /**< Constant to define Pin 11 on chip port A */
const hal_chip_pin_t CHIP_PIN(A, 11); /**< Constant to define Pin 12 on chip port A */
const hal_chip_pin_t CHIP_PIN(A, 12); /**< Constant to define Pin 13 on chip port A */
const hal_chip_pin_t CHIP_PIN(A, 13); /**< Constant to define Pin 14 on chip port A */
const hal_chip_pin_t CHIP_PIN(A, 14); /**< Constant to define Pin 15 on chip port A */
const hal_chip_pin_t CHIP_PIN(A, 15); /**< Constant to define Pin 16 on chip port A */

const hal_chip_pin_t CHIP_PIN(B, 0);  /**< Constant to define Pin 0 on chip port B */
const hal_chip_pin_t CHIP_PIN(B, 1);  /**< Constant to define Pin 1 on chip port B */
const hal_chip_pin_t CHIP_PIN(B, 2);  /**< Constant to define Pin 2 on chip port B */
const hal_chip_pin_t CHIP_PIN(B, 3);  /**< Constant to define Pin 3 on chip port B */
const hal_chip_pin_t CHIP_PIN(B, 4);  /**< Constant to define Pin 4 on chip port B */
const hal_chip_pin_t CHIP_PIN(B, 5);  /**< Constant to define Pin 6 on chip port B */
const hal_chip_pin_t CHIP_PIN(B, 6);  /**< Constant to define Pin 7 on chip port B */
const hal_chip_pin_t CHIP_PIN(B, 7);  /**< Constant to define Pin 8 on chip port B */
const hal_chip_pin_t CHIP_PIN(B, 8);  /**< Constant to define Pin 9 on chip port B */
const hal_chip_pin_t CHIP_PIN(B, 9);  /**< Constant to define Pin 10 on chip port B */
const hal_chip_pin_t CHIP_PIN(B, 10); /**< Constant to define Pin 11 on chip port B */
const hal_chip_pin_t CHIP_PIN(B, 11); /**< Constant to define Pin 12 on chip port B */
const hal_chip_pin_t CHIP_PIN(B, 12); /**< Constant to define Pin 13 on chip port B */
const hal_chip_pin_t CHIP_PIN(B, 13); /**< Constant to define Pin 14 on chip port B */
const hal_chip_pin_t CHIP_PIN(B, 14); /**< Constant to define Pin 15 on chip port B */
const hal_chip_pin_t CHIP_PIN(B, 15); /**< Constant to define Pin 16 on chip port B */

const hal_chip_pin_t CHIP_PIN(C, 13); /**< Constant to define Pin 14 on chip port C */
const hal_chip_pin_t CHIP_PIN(C, 14); /**< Constant to define Pin 15 on chip port C */
const hal_chip_pin_t CHIP_PIN(C, 15); /**< Constant to define Pin 16 on chip port C */

const hal_chip_pin_t CHIP_PIN(D, 0); /**< Constant to define Pin 0 on chip port D */
const hal_chip_pin_t CHIP_PIN(D, 1); /**< Constant to define Pin 1 on chip port D */
/** @} End of group stmf32f1xx */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */

void ChipPinSetFunction(hal_chip_pin_t pin, uint8_t function, bool pullup, bool puldown) {
    // uint32_t value;

    // value = SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS;

    // if (pullup && puldown) {
    //     value |= SCU_MODE_REPEATER;
    // } else if (pullup) {
    //     value |= SCU_MODE_PULLUP;
    // } else if (puldown) {
    //     value |= SCU_MODE_PULLDOWN;
    // } else {
    //     value |= SCU_MODE_INACT;
    // }

    // Chip_SCU_PinMux(pin->port, pin->pin, value, function);
}

void ChipPinSetPullUp(hal_chip_pin_t pin, bool enable) {
    // uint32_t current;

    // current = LPC_SCU->SFSP[pin->port][pin->pin];
    // if (enable) {
    //     current &= ~(1 << 3);
    // } else {
    //     current |= (1 << 3);
    // }
    // Chip_SCU_PinMuxSet(pin->port, pin->pin, current);
}

void ChipPinSetPullDown(hal_chip_pin_t pin, bool enable) {
    // uint32_t current;

    // current = LPC_SCU->SFSP[pin->port][pin->pin];
    // if (enable) {
    //     current |= (1 << 4);
    // } else {
    //     current &= ~(1 << 4);
    // }
    // Chip_SCU_PinMuxSet(pin->port, pin->pin, current);
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen
 ** @endcond */
