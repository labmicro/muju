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

#ifndef HAL_PIN_H
#define HAL_PIN_H

/** @file
 ** @brief Chip pins declarations
 **
 ** @addtogroup hal HAL
 ** @brief Hardware abstraction layer
 ** @{ */

/* === Headers files inclusions ================================================================ */

#include <stdbool.h>
#include <stdint.h>

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

/* === Public data type declarations =========================================================== */

/**
 * @brief Pointer to the structure with the chip pin descriptor
 */
typedef struct hal_chip_pin_s const * hal_chip_pin_t;

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/**
 * @brief Function to configure a chip pin with function and pull resistors
 *
 * @param  pin      Pointer to the structure with the chip pin descriptor
 * @param  function Numeric function asineg to chip pin
 * @param  pullup   State to be assigned to the internal pullup resistor
 * @param  puldown  State to be assigned to the internal pulldown resistor
 */
void ChipPinSetFunction(hal_chip_pin_t pin, uint8_t function, bool pullup, bool puldown);

/**
 * @brief Function to change the internal pullup resistor configuratioxn on chip pin
 *
 * @param  pin      Pointer to the structure with the chip pin descriptor
 * @param  enable   State to be assigned to the internal pullup resistor
 * @arg @c true     The internal pullup resistor must be enabled
 * @arg @c false    The internal pullup resistor must be disabled
 */
void ChipPinSetPullUp(hal_chip_pin_t pin, bool enable);

/**
 * @brief Function to change the internal pulldown resistor configuration on chip pin
 *
 * @param  pin      Pointer to the structure with the chip pin descriptor
 * @param  enable   State to be assigned to the internal pullup resistor
 * @arg @c true     The internal pulldown resistor must be enabled
 * @arg @c false    The internal pulldown resistor must be disabled
 */
void ChipPinSetPullDown(hal_chip_pin_t pin, bool enable);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* HAL_PIN_H */
