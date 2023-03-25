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

#ifndef SOC_GPIO_H
#define SOC_GPIO_H

/** @file
 ** @brief Digital inputs/outputs on lpc43xx declarations
 **
 ** @addtogroup lpc43xx LPC43xx
 ** @ingroup hal
 ** @brief LPC43xx SOC Hardware abstraction layer
 ** @{ */

/* === Headers files inclusions ================================================================ */

#include "hal_gpio.h"

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

/* === Public data type declarations =========================================================== */

/* === Public variable declarations ============================================================ */

/** @cond !INTERNAL */
extern const hal_gpio_bit_t HAL_GPIO0_0;  /**< Constant to define Bit 0 on GPIO 0 */
extern const hal_gpio_bit_t HAL_GPIO0_1;  /**< Constant to define Bit 1 on GPIO 0 */
extern const hal_gpio_bit_t HAL_GPIO0_2;  /**< Constant to define Bit 2 on GPIO 0 */
extern const hal_gpio_bit_t HAL_GPIO0_3;  /**< Constant to define Bit 3 on GPIO 0 */
extern const hal_gpio_bit_t HAL_GPIO0_4;  /**< Constant to define Bit 4 on GPIO 0 */
extern const hal_gpio_bit_t HAL_GPIO0_5;  /**< Constant to define Bit 5 on GPIO 0 */
extern const hal_gpio_bit_t HAL_GPIO0_7;  /**< Constant to define Bit 7 on GPIO 0 */
extern const hal_gpio_bit_t HAL_GPIO0_8;  /**< Constant to define Bit 8 on GPIO 0 */
extern const hal_gpio_bit_t HAL_GPIO0_9;  /**< Constant to define Bit 9 on GPIO 0 */
extern const hal_gpio_bit_t HAL_GPIO0_10; /**< Constant to define Bit 10 on GPIO 0 */
extern const hal_gpio_bit_t HAL_GPIO0_11; /**< Constant to define Bit 11 on GPIO 0 */
extern const hal_gpio_bit_t HAL_GPIO0_12; /**< Constant to define Bit 12 on GPIO 0 */
extern const hal_gpio_bit_t HAL_GPIO0_13; /**< Constant to define Bit 13 on GPIO 0 */
extern const hal_gpio_bit_t HAL_GPIO0_14; /**< Constant to define Bit 14 on GPIO 0 */
extern const hal_gpio_bit_t HAL_GPIO0_15; /**< Constant to define Bit 15 on GPIO 0 */

extern const hal_gpio_bit_t HAL_GPIO1_8;  /**< Constant to define Bit 8 on GPIO 1 */
extern const hal_gpio_bit_t HAL_GPIO1_9;  /**< Constant to define Bit 9 on GPIO 1 */
extern const hal_gpio_bit_t HAL_GPIO1_11; /**< Constant to define Bit 11 on GPIO 1 */
extern const hal_gpio_bit_t HAL_GPIO1_12; /**< Constant to define Bit 12 on GPIO 1 */

extern const hal_gpio_bit_t HAL_GPIO2_0; /**< Constant to define Bit 0 on GPIO 2 */
extern const hal_gpio_bit_t HAL_GPIO2_1; /**< Constant to define Bit 1 on GPIO 2 */
extern const hal_gpio_bit_t HAL_GPIO2_2; /**< Constant to define Bit 2 on GPIO 2 */
extern const hal_gpio_bit_t HAL_GPIO2_3; /**< Constant to define Bit 3 on GPIO 2 */
extern const hal_gpio_bit_t HAL_GPIO2_4; /**< Constant to define Bit 4 on GPIO 2 */
extern const hal_gpio_bit_t HAL_GPIO2_5; /**< Constant to define Bit 5 on GPIO 2 */
extern const hal_gpio_bit_t HAL_GPIO2_6; /**< Constant to define Bit 6 on GPIO 2 */
extern const hal_gpio_bit_t HAL_GPIO2_8; /**< Constant to define Bit 8 on GPIO 2 */

extern const hal_gpio_bit_t HAL_GPIO3_0;  /**< Constant to define Bit 0 on GPIO 3 */
extern const hal_gpio_bit_t HAL_GPIO3_1;  /**< Constant to define Bit 1 on GPIO 3 */
extern const hal_gpio_bit_t HAL_GPIO3_2;  /**< Constant to define Bit 2 on GPIO 3 */
extern const hal_gpio_bit_t HAL_GPIO3_3;  /**< Constant to define Bit 3 on GPIO 3 */
extern const hal_gpio_bit_t HAL_GPIO3_4;  /**< Constant to define Bit 4 on GPIO 3 */
extern const hal_gpio_bit_t HAL_GPIO3_5;  /**< Constant to define Bit 5 on GPIO 3 */
extern const hal_gpio_bit_t HAL_GPIO3_6;  /**< Constant to define Bit 6 on GPIO 3 */
extern const hal_gpio_bit_t HAL_GPIO3_7;  /**< Constant to define Bit 7 on GPIO 3 */
extern const hal_gpio_bit_t HAL_GPIO3_12; /**< Constant to define Bit 12 on GPIO 3 */
extern const hal_gpio_bit_t HAL_GPIO3_13; /**< Constant to define Bit 13 on GPIO 3 */
extern const hal_gpio_bit_t HAL_GPIO3_14; /**< Constant to define Bit 14 on GPIO 3 */
extern const hal_gpio_bit_t HAL_GPIO3_15; /**< Constant to define Bit 15 on GPIO 3 */

extern const hal_gpio_bit_t HAL_GPIO4_11; /**< Constant to define Bit 11 on GPIO 4 */

extern const hal_gpio_bit_t HAL_GPIO5_0;  /**< Constant to define Bit 0 on GPIO 5 */
extern const hal_gpio_bit_t HAL_GPIO5_1;  /**< Constant to define Bit 1 on GPIO 5 */
extern const hal_gpio_bit_t HAL_GPIO5_2;  /**< Constant to define Bit 2 on GPIO 5 */
extern const hal_gpio_bit_t HAL_GPIO5_3;  /**< Constant to define Bit 3 on GPIO 5 */
extern const hal_gpio_bit_t HAL_GPIO5_4;  /**< Constant to define Bit 4 on GPIO 5 */
extern const hal_gpio_bit_t HAL_GPIO5_8;  /**< Constant to define Bit 8 on GPIO 5 */
extern const hal_gpio_bit_t HAL_GPIO5_9;  /**< Constant to define Bit 9 on GPIO 5 */
extern const hal_gpio_bit_t HAL_GPIO5_12; /**< Constant to define Bit 12 on GPIO 5 */
extern const hal_gpio_bit_t HAL_GPIO5_13; /**< Constant to define Bit 13 on GPIO 5 */
extern const hal_gpio_bit_t HAL_GPIO5_14; /**< Constant to define Bit 14 on GPIO 5 */
extern const hal_gpio_bit_t HAL_GPIO5_15; /**< Constant to define Bit 15 on GPIO 5 */
extern const hal_gpio_bit_t HAL_GPIO5_16; /**< Constant to define Bit 16 on GPIO 5 */
extern const hal_gpio_bit_t HAL_GPIO5_18; /**< Constant to define Bit 18 on GPIO 5 */
/** @endcond */

/* === Public function declarations ============================================================ */

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* SOC_GPIO_H */
