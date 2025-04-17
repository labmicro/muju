/************************************************************************************************
Copyright (c) 2022-2024, Laboratorio de Microprocesadores
Facultad de Ciencias Exactas y Tecnología, Universidad Nacional de Tucumán
https://www.microprocesadores.unt.edu.ar/

Copyright (c) 2022-2024, Esteban Volentini <evolentini@herrera.unt.edu.ar>

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

#ifndef BOARD_H
#define BOARD_H

/** \brief Longan NANO board declarations
 **
 ** \addtogroup board Board support
 ** \brief Board agnostic configuration module
 ** @{ */

/* === Headers files inclusions ================================================================ */

#if defined(USE_HAL)
#include "hal.h"
#endif
#if defined(USE_DRIVERS)
#include "gd32vf103.h"
#endif

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

#if defined(USE_HAL)

#elif defined(USE_DRIVERS)

// #define LED_R_GPIO GPIOA
// #define LED_R_PIN  GPIO_PIN_0

// #define LED_G_GPIO GPIOA
// #define LED_G_PIN  GPIO_PIN_1

// #define LED_B_GPIO GPIOA
// #define LED_B_PIN  GPIO_PIN_2

#endif

/* === Public data type declarations =========================================================== */

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/**
 * @brief Function to initilize board configuration
 */
void BoardSetup(void);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* BOARD_H */
