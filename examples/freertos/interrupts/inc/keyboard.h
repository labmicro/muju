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

#ifndef KEYBOARD_H
#define KEYBOARD_H

/** @file
 ** @brief Board support hardware abstraction layer declarations
 **
 ** @addtogroup sample-freertos FreeRTOS Sample
 ** @ingroup samples
 ** @brief Samples applications with MUJU Framwork
 ** @{ */

/* === Headers files inclusions ================================================================ */

#include "bsp.h"

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

#define EVENT_TEC1_ON  (1 << 0)
#define EVENT_TEC2_ON  (1 << 1)
#define EVENT_TEC3_ON  (1 << 2)
#define EVENT_TEC4_ON  (1 << 3)

#define EVENT_TEC1_OFF (1 << 4)
#define EVENT_TEC2_OFF (1 << 5)
#define EVENT_TEC3_OFF (1 << 6)
#define EVENT_TEC4_OFF (1 << 7)

/* === Public data type declarations =========================================================== */

typedef struct keyboard_s * keyboard_t;

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/**
 * @brief Function to create a keyboard descriptor
 *
 * @param  board   Pointer to board descriptor
 *
 * @return keyboard_t Pointer to keyboard descriptor
 */
keyboard_t KeyboardCreate(board_t board);

/**
 * @brief Functio to wait a keyboard event
 *
 * @param  keyboard Pointer to keyboard descriptor
 *
 * @return uint8_t Bit mask with events received
 */
uint8_t KeyboardWait(keyboard_t keyboard, uint8_t events);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* KEYBOARD_H */
