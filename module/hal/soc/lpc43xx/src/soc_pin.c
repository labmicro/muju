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
 ** @brief Chip pins on lpc43xx implementation
 **
 ** @addtogroup lpc43xx LPC43xx
 ** @ingroup hal
 ** @brief LPC43xx SOC Hardware abstraction layer
 ** @cond INTERNAL
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "soc_pin.h"
#include "chip.h"

/* === Macros definitions ====================================================================== */

/**
 * @brief Macro to generate the name of an descriptor from the gpio port and bit
 */
#define PIN_NAME(PORT, PIN) HAL_PIN_P##PORT##_##PIN

/**
 * @brief Macro to define an gpio descriptor
 */
#define CHIP_PIN(PORT, PIN)                                                                        \
    PIN_NAME(PORT, PIN) = &(struct hal_chip_pin_s) { .port = PORT, .pin = PIN }

/* === Private data type declarations ========================================================== */

/**
 * @brief Structure with the gpio terminal descriptor
 */
struct hal_chip_pin_s {
    uint8_t pin : 5;  /**< Number of chip pin port */
    uint8_t port : 4; /**< Number of pin in chip port */
};

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/**
 * @addtogroup lpc43xxPin PIN Constants
 * @brief Constant for chip pin on board
 * @{
 */
const hal_chip_pin_t CHIP_PIN(0, 0); /**< Constant to define Pin 0 on chip port 0 */
const hal_chip_pin_t CHIP_PIN(0, 1); /**< Constant to define Pin 1 on chip port 0 */

const hal_chip_pin_t CHIP_PIN(1, 0);  /**< Constant to define Pin 0 on chip port 1 */
const hal_chip_pin_t CHIP_PIN(1, 1);  /**< Constant to define Pin 1 on chip port 1 */
const hal_chip_pin_t CHIP_PIN(1, 2);  /**< Constant to define Pin 2 on chip port 1 */
const hal_chip_pin_t CHIP_PIN(1, 3);  /**< Constant to define Pin 3 on chip port 1 */
const hal_chip_pin_t CHIP_PIN(1, 4);  /**< Constant to define Pin 4 on chip port 1 */
const hal_chip_pin_t CHIP_PIN(1, 5);  /**< Constant to define Pin 5 on chip port 1 */
const hal_chip_pin_t CHIP_PIN(1, 6);  /**< Constant to define Pin 6 on chip port 1 */
const hal_chip_pin_t CHIP_PIN(1, 7);  /**< Constant to define Pin 7 on chip port 1 */
const hal_chip_pin_t CHIP_PIN(1, 8);  /**< Constant to define Pin 8 on chip port 1 */
const hal_chip_pin_t CHIP_PIN(1, 9);  /**< Constant to define Pin 9 on chip port 1 */
const hal_chip_pin_t CHIP_PIN(1, 10); /**< Constant to define Pin 10 on chip port 1 */
const hal_chip_pin_t CHIP_PIN(1, 11); /**< Constant to define Pin 11 on chip port 1 */
const hal_chip_pin_t CHIP_PIN(1, 12); /**< Constant to define Pin 12 on chip port 1 */
const hal_chip_pin_t CHIP_PIN(1, 13); /**< Constant to define Pin 13 on chip port 1 */
const hal_chip_pin_t CHIP_PIN(1, 14); /**< Constant to define Pin 14 on chip port 1 */
const hal_chip_pin_t CHIP_PIN(1, 15); /**< Constant to define Pin 15 on chip port 1 */
const hal_chip_pin_t CHIP_PIN(1, 16); /**< Constant to define Pin 16 on chip port 1 */
const hal_chip_pin_t CHIP_PIN(1, 17); /**< Constant to define Pin 17 on chip port 1 */
const hal_chip_pin_t CHIP_PIN(1, 18); /**< Constant to define Pin 18 on chip port 1 */
const hal_chip_pin_t CHIP_PIN(1, 20); /**< Constant to define Pin 20 on chip port 1 */

const hal_chip_pin_t CHIP_PIN(2, 0);  /**< Constant to define Pin 0 on chip port 2 */
const hal_chip_pin_t CHIP_PIN(2, 1);  /**< Constant to define Pin 1 on chip port 2 */
const hal_chip_pin_t CHIP_PIN(2, 2);  /**< Constant to define Pin 2 on chip port 2 */
const hal_chip_pin_t CHIP_PIN(2, 3);  /**< Constant to define Pin 3 on chip port 2 */
const hal_chip_pin_t CHIP_PIN(2, 4);  /**< Constant to define Pin 4 on chip port 2 */
const hal_chip_pin_t CHIP_PIN(2, 5);  /**< Constant to define Pin 5 on chip port 2 */
const hal_chip_pin_t CHIP_PIN(2, 6);  /**< Constant to define Pin 6 on chip port 2 */
const hal_chip_pin_t CHIP_PIN(2, 7);  /**< Constant to define Pin 7 on chip port 2 */
const hal_chip_pin_t CHIP_PIN(2, 8);  /**< Constant to define Pin 8 on chip port 2 */
const hal_chip_pin_t CHIP_PIN(2, 9);  /**< Constant to define Pin 9 on chip port 2 */
const hal_chip_pin_t CHIP_PIN(2, 10); /**< Constant to define Pin 10 on chip port 2 */
const hal_chip_pin_t CHIP_PIN(2, 11); /**< Constant to define Pin 11 on chip port 2 */
const hal_chip_pin_t CHIP_PIN(2, 12); /**< Constant to define Pin 12 on chip port 2 */
const hal_chip_pin_t CHIP_PIN(2, 13); /**< Constant to define Pin 13 on chip port 2 */

const hal_chip_pin_t CHIP_PIN(3, 1); /**< Constant to define Pin 1 on chip port 3 */
const hal_chip_pin_t CHIP_PIN(3, 2); /**< Constant to define Pin 2 on chip port 3 */
const hal_chip_pin_t CHIP_PIN(3, 3); /**< Constant to define Pin 3 on chip port 3 */
const hal_chip_pin_t CHIP_PIN(3, 4); /**< Constant to define Pin 4 on chip port 3 */
const hal_chip_pin_t CHIP_PIN(3, 5); /**< Constant to define Pin 5 on chip port 3 */
const hal_chip_pin_t CHIP_PIN(3, 6); /**< Constant to define Pin 6 on chip port 3 */
const hal_chip_pin_t CHIP_PIN(3, 7); /**< Constant to define Pin 7 on chip port 3 */
const hal_chip_pin_t CHIP_PIN(3, 8); /**< Constant to define Pin 8 on chip port 3 */

const hal_chip_pin_t CHIP_PIN(4, 0);  /**< Constant to define Pin 0 on chip port 4 */
const hal_chip_pin_t CHIP_PIN(4, 1);  /**< Constant to define Pin 1 on chip port 4 */
const hal_chip_pin_t CHIP_PIN(4, 2);  /**< Constant to define Pin 2 on chip port 4 */
const hal_chip_pin_t CHIP_PIN(4, 3);  /**< Constant to define Pin 3 on chip port 4 */
const hal_chip_pin_t CHIP_PIN(4, 4);  /**< Constant to define Pin 4 on chip port 4 */
const hal_chip_pin_t CHIP_PIN(4, 5);  /**< Constant to define Pin 5 on chip port 4 */
const hal_chip_pin_t CHIP_PIN(4, 6);  /**< Constant to define Pin 6 on chip port 4 */
const hal_chip_pin_t CHIP_PIN(4, 7);  /**< Constant to define Pin 7 on chip port 4 */
const hal_chip_pin_t CHIP_PIN(4, 8);  /**< Constant to define Pin 8 on chip port 4 */
const hal_chip_pin_t CHIP_PIN(4, 9);  /**< Constant to define Pin 9 on chip port 4 */
const hal_chip_pin_t CHIP_PIN(4, 10); /**< Constant to define Pin 10 on chip port 4 */

const hal_chip_pin_t CHIP_PIN(5, 1); /**< Constant to define Pin 1 on chip port 5 */
const hal_chip_pin_t CHIP_PIN(5, 2); /**< Constant to define Pin 2 on chip port 5 */
const hal_chip_pin_t CHIP_PIN(5, 3); /**< Constant to define Pin 3 on chip port 5 */
const hal_chip_pin_t CHIP_PIN(5, 4); /**< Constant to define Pin 4 on chip port 5 */
const hal_chip_pin_t CHIP_PIN(5, 5); /**< Constant to define Pin 5 on chip port 5 */
const hal_chip_pin_t CHIP_PIN(5, 6); /**< Constant to define Pin 6 on chip port 5 */
const hal_chip_pin_t CHIP_PIN(5, 7); /**< Constant to define Pin 7 on chip port 5 */

const hal_chip_pin_t CHIP_PIN(6, 0);  /**< Constant to define Pin 0 on chip port 6 */
const hal_chip_pin_t CHIP_PIN(6, 1);  /**< Constant to define Pin 1 on chip port 6 */
const hal_chip_pin_t CHIP_PIN(6, 2);  /**< Constant to define Pin 2 on chip port 6 */
const hal_chip_pin_t CHIP_PIN(6, 3);  /**< Constant to define Pin 3 on chip port 6 */
const hal_chip_pin_t CHIP_PIN(6, 4);  /**< Constant to define Pin 4 on chip port 6 */
const hal_chip_pin_t CHIP_PIN(6, 5);  /**< Constant to define Pin 5 on chip port 6 */
const hal_chip_pin_t CHIP_PIN(6, 6);  /**< Constant to define Pin 6 on chip port 6 */
const hal_chip_pin_t CHIP_PIN(6, 7);  /**< Constant to define Pin 7 on chip port 6 */
const hal_chip_pin_t CHIP_PIN(6, 8);  /**< Constant to define Pin 8 on chip port 6 */
const hal_chip_pin_t CHIP_PIN(6, 9);  /**< Constant to define Pin 9 on chip port 6 */
const hal_chip_pin_t CHIP_PIN(6, 10); /**< Constant to define Pin 10 on chip port 6 */
const hal_chip_pin_t CHIP_PIN(6, 11); /**< Constant to define Pin 11 on chip port 6 */
const hal_chip_pin_t CHIP_PIN(6, 12); /**< Constant to define Pin 12 on chip port 6 */

const hal_chip_pin_t CHIP_PIN(7, 0); /**< Constant to define Pin 0 on chip port 7 */
const hal_chip_pin_t CHIP_PIN(7, 1); /**< Constant to define Pin 1 on chip port 7 */
const hal_chip_pin_t CHIP_PIN(7, 2); /**< Constant to define Pin 2 on chip port 7 */
const hal_chip_pin_t CHIP_PIN(7, 4); /**< Constant to define Pin 4 on chip port 7 */
const hal_chip_pin_t CHIP_PIN(7, 5); /**< Constant to define Pin 5 on chip port 7 */
const hal_chip_pin_t CHIP_PIN(7, 6); /**< Constant to define Pin 6 on chip port 7 */
const hal_chip_pin_t CHIP_PIN(7, 7); /**< Constant to define Pin 7 on chip port 7 */

const hal_chip_pin_t CHIP_PIN(9, 5); /**< Constant to define Pin 5 on chip port 9 */
const hal_chip_pin_t CHIP_PIN(9, 6); /**< Constant to define Pin 6 on chip port 9 */

/** Constant to define Pin 4 on chip port F */
const hal_chip_pin_t HAL_PIN_PF_4 = &(struct hal_chip_pin_s){.port = 15, .pin = 4};

/** @} End of group lpc43xxPin */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */

void ChipPinSetFunction(hal_chip_pin_t pin, uint8_t function, bool pullup, bool puldown) {
    uint32_t value;

    value = SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS;

    if (pullup && puldown) {
        value |= SCU_MODE_REPEATER;
    } else if (pullup) {
        value |= SCU_MODE_PULLUP;
    } else if (puldown) {
        value |= SCU_MODE_PULLDOWN;
    } else {
        value |= SCU_MODE_INACT;
    }

    Chip_SCU_PinMux(pin->port, pin->pin, value, function);
}

void ChipPinSetPullUp(hal_chip_pin_t pin, bool enable) {
    uint32_t current;

    current = LPC_SCU->SFSP[pin->port][pin->pin];
    if (enable) {
        current &= ~(1 << 3);
    } else {
        current |= (1 << 3);
    }
    Chip_SCU_PinMuxSet(pin->port, pin->pin, current);
}

void ChipPinSetPullDown(hal_chip_pin_t pin, bool enable) {
    uint32_t current;

    current = LPC_SCU->SFSP[pin->port][pin->pin];
    if (enable) {
        current |= (1 << 4);
    } else {
        current &= ~(1 << 4);
    }
    Chip_SCU_PinMuxSet(pin->port, pin->pin, current);
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen
 ** @endcond */
