/************************************************************************************************
Copyright (c) <year>, <copyright holders>

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

/** \brief Board agnostic declarations
 **
 ** \addtogroup board Board support
 ** \brief Board agnostic configuration module
 ** @{ */

/* === Headers files inclusions ================================================================ */

#if defined(USE_HAL)
#include "hal.h"
#endif
#if defined(USE_DRIVERS)
#include "chip.h"
#endif

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

#if defined(USE_HAL)
#define LED_R  HAL_GPIO5_0
#define LED_G  HAL_GPIO5_1
#define LED_B  HAL_GPIO5_2

#define LED_1  HAL_GPIO0_14
#define LED_2  HAL_GPIO1_11
#define LED_3  HAL_GPIO1_12

#define TEC_1  HAL_GPIO0_4
#define TEC_2  HAL_GPIO0_8
#define TEC_3  HAL_GPIO0_9
#define TEC_4  HAL_GPIO1_9

#define GPIO0  HAL_GPIO3_0
#define GPIO1  HAL_GPIO3_3
#define GPIO2  HAL_GPIO3_4
#define GPIO3  HAL_GPIO5_15
#define GPIO4  HAL_GPIO5_16
#define GPIO5  HAL_GPIO3_5
#define GPIO6  HAL_GPIO3_6
#define GPIO7  HAL_GPIO3_7
#define GPIO8  HAL_GPIO2_8

#define LCD1   HAL_GPIO2_4
#define LCD2   HAL_GPIO2_5
#define LCD3   HAL_GPIO2_6
#define LCD4   HAL_GPIO5_14
#define LCD_RS HAL_GPIO5_12
#define LCD_EN HAL_GPIO5_13

#define T_FIL0 HAL_GPIO2_0
#define T_FIL1 HAL_GPIO2_1
#define T_FIL2 HAL_GPIO2_2
#define T_FIL3 HAL_GPIO2_3
#define T_COL0 HAL_GPIO1_8
#define T_COL1 HAL_GPIO3_12
#define T_COL2 HAL_GPIO3_13
#elif defined(USE_DRIVERS)
#define LED_R_PORT 2
#define LED_R_PIN  0
#define LED_R_FUNC SCU_MODE_FUNC4
#define LED_R_GPIO 5
#define LED_R_BIT  0

#define LED_G_PORT 2
#define LED_G_PIN  1
#define LED_G_FUNC SCU_MODE_FUNC4
#define LED_G_GPIO 5
#define LED_G_BIT  1

#define LED_B_PORT 2
#define LED_B_PIN  2
#define LED_B_FUNC SCU_MODE_FUNC4
#define LED_B_GPIO 5
#define LED_B_BIT  2

#define LED_1_PORT 2
#define LED_1_PIN  10
#define LED_1_FUNC SCU_MODE_FUNC0
#define LED_1_GPIO 0
#define LED_1_BIT  14

#define LED_2_PORT 2
#define LED_2_PIN  11
#define LED_2_FUNC SCU_MODE_FUNC0
#define LED_2_GPIO 1
#define LED_2_BIT  11

#define LED_3_PORT 2
#define LED_3_PIN  12
#define LED_3_FUNC SCU_MODE_FUNC0
#define LED_3_GPIO 1
#define LED_3_BIT  12

#define TEC_1_PORT 1
#define TEC_1_PIN  0
#define TEC_1_FUNC SCU_MODE_FUNC0
#define TEC_1_GPIO 0
#define TEC_1_BIT  4

#define TEC_2_PORT 1
#define TEC_2_PIN  1
#define TEC_2_FUNC SCU_MODE_FUNC0
#define TEC_2_GPIO 0
#define TEC_2_BIT  8

#define TEC_3_PORT 1
#define TEC_3_PIN  2
#define TEC_3_FUNC SCU_MODE_FUNC0
#define TEC_3_GPIO 0
#define TEC_3_BIT  9

#define TEC_4_PORT 1
#define TEC_4_PIN  6
#define TEC_4_FUNC SCU_MODE_FUNC0
#define TEC_4_GPIO 1
#define TEC_4_BIT  9
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
