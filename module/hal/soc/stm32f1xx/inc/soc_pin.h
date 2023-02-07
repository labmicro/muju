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

#ifndef SOC_PIN_H
#define SOC_PIN_H

/** @file
 ** @brief Chip pins on STM32F1xx declarations
 **
 ** @addtogroup stmf32f1xx STM32F1xx
 ** @ingroup hal
 ** @brief STM32F1xx SOC Hardware abstraction layer
 ** @{ */

/* === Headers files inclusions ================================================================ */

#include "hal_pin.h"

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

/** @brief Numeric constant assigned to input/output port A */
#define HAL_PORT_A 0

/** @brief Numeric constant assigned to input/output port B */
#define HAL_PORT_B 1

/** @brief Numeric constant assigned to input/output port C */
#define HAL_PORT_C 2

/** @brief Numeric constant assigned to input/output port D */
#define HAL_PORT_D 3

/* === Public data type declarations =========================================================== */

/**
 * @brief Structure with the gpio terminal descriptor
 */
struct hal_chip_pin_s {
    uint8_t pin : 4;  /**< Number of chip pin port */
    uint8_t port : 4; /**< Number of pin in chip port */
};

/* === Public variable declarations ============================================================ */

/** @cond !INTERNAL */
extern const hal_chip_pin_t HAL_PIN_PA0;  /**< Constant to define Pin 0 on chip port A */
extern const hal_chip_pin_t HAL_PIN_PA1;  /**< Constant to define Pin 1 on chip port A */
extern const hal_chip_pin_t HAL_PIN_PA2;  /**< Constant to define Pin 2 on chip port A */
extern const hal_chip_pin_t HAL_PIN_PA3;  /**< Constant to define Pin 3 on chip port A */
extern const hal_chip_pin_t HAL_PIN_PA4;  /**< Constant to define Pin 4 on chip port A */
extern const hal_chip_pin_t HAL_PIN_PA5;  /**< Constant to define Pin 5 on chip port A */
extern const hal_chip_pin_t HAL_PIN_PA6;  /**< Constant to define Pin 6 on chip port A */
extern const hal_chip_pin_t HAL_PIN_PA7;  /**< Constant to define Pin 7 on chip port A */
extern const hal_chip_pin_t HAL_PIN_PA8;  /**< Constant to define Pin 8 on chip port A */
extern const hal_chip_pin_t HAL_PIN_PA9;  /**< Constant to define Pin 9 on chip port A */
extern const hal_chip_pin_t HAL_PIN_PA10; /**< Constant to define Pin 10 on chip port A */
extern const hal_chip_pin_t HAL_PIN_PA11; /**< Constant to define Pin 11 on chip port A */
extern const hal_chip_pin_t HAL_PIN_PA12; /**< Constant to define Pin 12 on chip port A */
extern const hal_chip_pin_t HAL_PIN_PA13; /**< Constant to define Pin 13 on chip port A */
extern const hal_chip_pin_t HAL_PIN_PA14; /**< Constant to define Pin 14 on chip port A */
extern const hal_chip_pin_t HAL_PIN_PA15; /**< Constant to define Pin 15 on chip port A */

extern const hal_chip_pin_t HAL_PIN_PB0;  /**< Constant to define Pin 0 on chip port B */
extern const hal_chip_pin_t HAL_PIN_PB1;  /**< Constant to define Pin 1 on chip port B */
extern const hal_chip_pin_t HAL_PIN_PB2;  /**< Constant to define Pin 2 on chip port B */
extern const hal_chip_pin_t HAL_PIN_PB3;  /**< Constant to define Pin 3 on chip port B */
extern const hal_chip_pin_t HAL_PIN_PB4;  /**< Constant to define Pin 4 on chip port B */
extern const hal_chip_pin_t HAL_PIN_PB5;  /**< Constant to define Pin 5 on chip port B */
extern const hal_chip_pin_t HAL_PIN_PB6;  /**< Constant to define Pin 6 on chip port B */
extern const hal_chip_pin_t HAL_PIN_PB7;  /**< Constant to define Pin 7 on chip port B */
extern const hal_chip_pin_t HAL_PIN_PB8;  /**< Constant to define Pin 8 on chip port B */
extern const hal_chip_pin_t HAL_PIN_PB9;  /**< Constant to define Pin 9 on chip port B */
extern const hal_chip_pin_t HAL_PIN_PB10; /**< Constant to define Pin 10 on chip port B */
extern const hal_chip_pin_t HAL_PIN_PB11; /**< Constant to define Pin 11 on chip port B */
extern const hal_chip_pin_t HAL_PIN_PB12; /**< Constant to define Pin 12 on chip port B */
extern const hal_chip_pin_t HAL_PIN_PB13; /**< Constant to define Pin 13 on chip port B */
extern const hal_chip_pin_t HAL_PIN_PB14; /**< Constant to define Pin 14 on chip port B */
extern const hal_chip_pin_t HAL_PIN_PB15; /**< Constant to define Pin 15 on chip port B */

extern const hal_chip_pin_t HAL_PIN_PC13; /**< Constant to define Pin 13 on chip port C */
extern const hal_chip_pin_t HAL_PIN_PC14; /**< Constant to define Pin 14 on chip port C */
extern const hal_chip_pin_t HAL_PIN_PC15; /**< Constant to define Pin 15 on chip port C */

extern const hal_chip_pin_t HAL_PIN_PD0; /**< Constant to define Pin 0 on chip port D */
extern const hal_chip_pin_t HAL_PIN_PD1; /**< Constant to define Pin 1 on chip port D */
/** @endcond */

/* === Public function declarations ============================================================ */

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* SOC_PIN_H */
