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
 ** @brief Chip pins on lpc43xx declarations
 **
 ** @addtogroup lpc43xx LPC43xx
 ** @ingroup hal
 ** @brief LPC43xx SOC Hardware abstraction layer
 ** @{ */

/* === Headers files inclusions ================================================================ */

#include "hal_pin.h"

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

/* === Public data type declarations =========================================================== */

/* === Public variable declarations ============================================================ */

/** @cond !INTERNAL */
extern const hal_chip_pin_t HAL_PIN_P0_0; /**< Constant to define Pin 0 on chip port 0 */
extern const hal_chip_pin_t HAL_PIN_P0_1; /**< Constant to define Pin 1 on chip port 0 */

extern const hal_chip_pin_t HAL_PIN_P1_0;  /**< Constant to define Pin 0 on chip port 1 */
extern const hal_chip_pin_t HAL_PIN_P1_1;  /**< Constant to define Pin 1 on chip port 1 */
extern const hal_chip_pin_t HAL_PIN_P1_2;  /**< Constant to define Pin 2 on chip port 1 */
extern const hal_chip_pin_t HAL_PIN_P1_3;  /**< Constant to define Pin 3 on chip port 1 */
extern const hal_chip_pin_t HAL_PIN_P1_4;  /**< Constant to define Pin 4 on chip port 1 */
extern const hal_chip_pin_t HAL_PIN_P1_5;  /**< Constant to define Pin 5 on chip port 1 */
extern const hal_chip_pin_t HAL_PIN_P1_6;  /**< Constant to define Pin 6 on chip port 1 */
extern const hal_chip_pin_t HAL_PIN_P1_7;  /**< Constant to define Pin 7 on chip port 1 */
extern const hal_chip_pin_t HAL_PIN_P1_8;  /**< Constant to define Pin 8 on chip port 1 */
extern const hal_chip_pin_t HAL_PIN_P1_9;  /**< Constant to define Pin 9 on chip port 1 */
extern const hal_chip_pin_t HAL_PIN_P1_10; /**< Constant to define Pin 10 on chip port 1 */
extern const hal_chip_pin_t HAL_PIN_P1_11; /**< Constant to define Pin 11 on chip port 1 */
extern const hal_chip_pin_t HAL_PIN_P1_12; /**< Constant to define Pin 12 on chip port 1 */
extern const hal_chip_pin_t HAL_PIN_P1_13; /**< Constant to define Pin 13 on chip port 1 */
extern const hal_chip_pin_t HAL_PIN_P1_14; /**< Constant to define Pin 14 on chip port 1 */
extern const hal_chip_pin_t HAL_PIN_P1_15; /**< Constant to define Pin 15 on chip port 1 */
extern const hal_chip_pin_t HAL_PIN_P1_16; /**< Constant to define Pin 16 on chip port 1 */
extern const hal_chip_pin_t HAL_PIN_P1_17; /**< Constant to define Pin 17 on chip port 1 */
extern const hal_chip_pin_t HAL_PIN_P1_18; /**< Constant to define Pin 18 on chip port 1 */
extern const hal_chip_pin_t HAL_PIN_P1_20; /**< Constant to define Pin 20 on chip port 1 */

extern const hal_chip_pin_t HAL_PIN_P2_0;  /**< Constant to define Pin 0 on chip port 2 */
extern const hal_chip_pin_t HAL_PIN_P2_1;  /**< Constant to define Pin 1 on chip port 2 */
extern const hal_chip_pin_t HAL_PIN_P2_2;  /**< Constant to define Pin 2 on chip port 2 */
extern const hal_chip_pin_t HAL_PIN_P2_3;  /**< Constant to define Pin 3 on chip port 2 */
extern const hal_chip_pin_t HAL_PIN_P2_4;  /**< Constant to define Pin 4 on chip port 2 */
extern const hal_chip_pin_t HAL_PIN_P2_5;  /**< Constant to define Pin 5 on chip port 2 */
extern const hal_chip_pin_t HAL_PIN_P2_6;  /**< Constant to define Pin 6 on chip port 2 */
extern const hal_chip_pin_t HAL_PIN_P2_7;  /**< Constant to define Pin 7 on chip port 2 */
extern const hal_chip_pin_t HAL_PIN_P2_8;  /**< Constant to define Pin 8 on chip port 2 */
extern const hal_chip_pin_t HAL_PIN_P2_9;  /**< Constant to define Pin 9 on chip port 2 */
extern const hal_chip_pin_t HAL_PIN_P2_10; /**< Constant to define Pin 10 on chip port 2 */
extern const hal_chip_pin_t HAL_PIN_P2_11; /**< Constant to define Pin 11 on chip port 2 */
extern const hal_chip_pin_t HAL_PIN_P2_12; /**< Constant to define Pin 12 on chip port 2 */
extern const hal_chip_pin_t HAL_PIN_P2_13; /**< Constant to define Pin 13 on chip port 2 */

extern const hal_chip_pin_t HAL_PIN_P3_1; /**< Constant to define Pin 1 on chip port 3 */
extern const hal_chip_pin_t HAL_PIN_P3_2; /**< Constant to define Pin 2 on chip port 3 */
extern const hal_chip_pin_t HAL_PIN_P3_3; /**< Constant to define Pin 3 on chip port 3 */
extern const hal_chip_pin_t HAL_PIN_P3_4; /**< Constant to define Pin 4 on chip port 3 */
extern const hal_chip_pin_t HAL_PIN_P3_5; /**< Constant to define Pin 5 on chip port 3 */
extern const hal_chip_pin_t HAL_PIN_P3_6; /**< Constant to define Pin 6 on chip port 3 */
extern const hal_chip_pin_t HAL_PIN_P3_7; /**< Constant to define Pin 7 on chip port 3 */
extern const hal_chip_pin_t HAL_PIN_P3_8; /**< Constant to define Pin 8 on chip port 3 */

extern const hal_chip_pin_t HAL_PIN_P4_0;  /**< Constant to define Pin 0 on chip port 4 */
extern const hal_chip_pin_t HAL_PIN_P4_1;  /**< Constant to define Pin 1 on chip port 4 */
extern const hal_chip_pin_t HAL_PIN_P4_2;  /**< Constant to define Pin 2 on chip port 4 */
extern const hal_chip_pin_t HAL_PIN_P4_3;  /**< Constant to define Pin 3 on chip port 4 */
extern const hal_chip_pin_t HAL_PIN_P4_4;  /**< Constant to define Pin 4 on chip port 4 */
extern const hal_chip_pin_t HAL_PIN_P4_5;  /**< Constant to define Pin 5 on chip port 4 */
extern const hal_chip_pin_t HAL_PIN_P4_6;  /**< Constant to define Pin 6 on chip port 4 */
extern const hal_chip_pin_t HAL_PIN_P4_7;  /**< Constant to define Pin 7 on chip port 4 */
extern const hal_chip_pin_t HAL_PIN_P4_8;  /**< Constant to define Pin 8 on chip port 4 */
extern const hal_chip_pin_t HAL_PIN_P4_9;  /**< Constant to define Pin 9 on chip port 4 */
extern const hal_chip_pin_t HAL_PIN_P4_10; /**< Constant to define Pin 10 on chip port 4 */

extern const hal_chip_pin_t HAL_PIN_P5_1; /**< Constant to define Pin 1 on chip port 5 */
extern const hal_chip_pin_t HAL_PIN_P5_2; /**< Constant to define Pin 2 on chip port 5 */
extern const hal_chip_pin_t HAL_PIN_P5_3; /**< Constant to define Pin 3 on chip port 5 */
extern const hal_chip_pin_t HAL_PIN_P5_4; /**< Constant to define Pin 4 on chip port 5 */
extern const hal_chip_pin_t HAL_PIN_P5_5; /**< Constant to define Pin 5 on chip port 5 */
extern const hal_chip_pin_t HAL_PIN_P5_6; /**< Constant to define Pin 6 on chip port 5 */
extern const hal_chip_pin_t HAL_PIN_P5_7; /**< Constant to define Pin 7 on chip port 5 */

extern const hal_chip_pin_t HAL_PIN_P6_0;  /**< Constant to define Pin 0 on chip port 6 */
extern const hal_chip_pin_t HAL_PIN_P6_1;  /**< Constant to define Pin 1 on chip port 6 */
extern const hal_chip_pin_t HAL_PIN_P6_2;  /**< Constant to define Pin 2 on chip port 6 */
extern const hal_chip_pin_t HAL_PIN_P6_3;  /**< Constant to define Pin 3 on chip port 6 */
extern const hal_chip_pin_t HAL_PIN_P6_4;  /**< Constant to define Pin 4 on chip port 6 */
extern const hal_chip_pin_t HAL_PIN_P6_5;  /**< Constant to define Pin 5 on chip port 6 */
extern const hal_chip_pin_t HAL_PIN_P6_6;  /**< Constant to define Pin 6 on chip port 6 */
extern const hal_chip_pin_t HAL_PIN_P6_7;  /**< Constant to define Pin 7 on chip port 6 */
extern const hal_chip_pin_t HAL_PIN_P6_8;  /**< Constant to define Pin 8 on chip port 6 */
extern const hal_chip_pin_t HAL_PIN_P6_9;  /**< Constant to define Pin 9 on chip port 6 */
extern const hal_chip_pin_t HAL_PIN_P6_10; /**< Constant to define Pin 10 on chip port 6 */
extern const hal_chip_pin_t HAL_PIN_P6_11; /**< Constant to define Pin 11 on chip port 6 */
extern const hal_chip_pin_t HAL_PIN_P6_12; /**< Constant to define Pin 12 on chip port 6 */

extern const hal_chip_pin_t HAL_PIN_P7_0; /**< Constant to define Pin 0 on chip port 7 */
extern const hal_chip_pin_t HAL_PIN_P7_1; /**< Constant to define Pin 1 on chip port 7 */
extern const hal_chip_pin_t HAL_PIN_P7_2; /**< Constant to define Pin 2 on chip port 7 */
extern const hal_chip_pin_t HAL_PIN_P7_4; /**< Constant to define Pin 4 on chip port 7 */
extern const hal_chip_pin_t HAL_PIN_P7_5; /**< Constant to define Pin 5 on chip port 7 */
extern const hal_chip_pin_t HAL_PIN_P7_6; /**< Constant to define Pin 6 on chip port 7 */
extern const hal_chip_pin_t HAL_PIN_P7_7; /**< Constant to define Pin 7 on chip port 7 */

extern const hal_chip_pin_t HAL_PIN_P9_5; /**< Constant to define Pin 5 on chip port 9 */
extern const hal_chip_pin_t HAL_PIN_P9_6; /**< Constant to define Pin 6 on chip port 9 */

extern const hal_chip_pin_t HAL_PIN_PF_4; /**< Constant to define Pin 4 on chip port F */
/** @endcond */

/* === Public function declarations ============================================================ */

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* SOC_PIN_H */
