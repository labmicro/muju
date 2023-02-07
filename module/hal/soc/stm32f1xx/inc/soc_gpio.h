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
 ** @brief Digital inputs/outputs on STM32F1xx declarations
 **
 ** @addtogroup stmf32f1xx STM32F1xx
 ** @ingroup hal
 ** @brief STM32F1xx SOC Hardware abstraction layer
 ** @{ */

/* === Headers files inclusions ================================================================ */

#include "soc_pin.h"
#include "hal_gpio.h"

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

/** @cond !INTERNAL */
#define HAL_GPIO_PA0  ((hal_gpio_bit_t)HAL_PIN_PA0)  /**< Constant to define Bit 0 on GPIO A */
#define HAL_GPIO_PA1  ((hal_gpio_bit_t)HAL_PIN_PA1)  /**< Constant to define Bit 1 on GPIO A */
#define HAL_GPIO_PA2  ((hal_gpio_bit_t)HAL_PIN_PA2)  /**< Constant to define Bit 2 on GPIO A */
#define HAL_GPIO_PA3  ((hal_gpio_bit_t)HAL_PIN_PA3)  /**< Constant to define Bit 3 on GPIO A */
#define HAL_GPIO_PA4  ((hal_gpio_bit_t)HAL_PIN_PA4)  /**< Constant to define Bit 4 on GPIO A */
#define HAL_GPIO_PA5  ((hal_gpio_bit_t)HAL_PIN_PA5)  /**< Constant to define Bit 5 on GPIO A */
#define HAL_GPIO_PA6  ((hal_gpio_bit_t)HAL_PIN_PA6)  /**< Constant to define Bit 6 on GPIO A */
#define HAL_GPIO_PA7  ((hal_gpio_bit_t)HAL_PIN_PA7)  /**< Constant to define Bit 7 on GPIO A */
#define HAL_GPIO_PA8  ((hal_gpio_bit_t)HAL_PIN_PA8)  /**< Constant to define Bit 8 on GPIO A */
#define HAL_GPIO_PA9  ((hal_gpio_bit_t)HAL_PIN_PA9)  /**< Constant to define Bit 9 on GPIO A */
#define HAL_GPIO_PA10 ((hal_gpio_bit_t)HAL_PIN_PA10) /**< Constant to define Bit 10 on GPIO A */
#define HAL_GPIO_PA11 ((hal_gpio_bit_t)HAL_PIN_PA11) /**< Constant to define Bit 11 on GPIO A */
#define HAL_GPIO_PA12 ((hal_gpio_bit_t)HAL_PIN_PA12) /**< Constant to define Bit 12 on GPIO A */
#define HAL_GPIO_PA13 ((hal_gpio_bit_t)HAL_PIN_PA13) /**< Constant to define Bit 13 on GPIO A */
#define HAL_GPIO_PA14 ((hal_gpio_bit_t)HAL_PIN_PA14) /**< Constant to define Bit 14 on GPIO A */
#define HAL_GPIO_PA15 ((hal_gpio_bit_t)HAL_PIN_PA15) /**< Constant to define Bit 15 on GPIO A */

#define HAL_GPIO_PB0  ((hal_gpio_bit_t)HAL_PIN_PB0)  /**< Constant to define Bit 0 on GPIO B */
#define HAL_GPIO_PB1  ((hal_gpio_bit_t)HAL_PIN_PB1)  /**< Constant to define Bit 1 on GPIO B */
#define HAL_GPIO_PB2  ((hal_gpio_bit_t)HAL_PIN_PB2)  /**< Constant to define Bit 2 on GPIO B */
#define HAL_GPIO_PB3  ((hal_gpio_bit_t)HAL_PIN_PB3)  /**< Constant to define Bit 3 on GPIO B */
#define HAL_GPIO_PB4  ((hal_gpio_bit_t)HAL_PIN_PB4)  /**< Constant to define Bit 4 on GPIO B */
#define HAL_GPIO_PB5  ((hal_gpio_bit_t)HAL_PIN_PB5)  /**< Constant to define Bit 5 on GPIO B */
#define HAL_GPIO_PB6  ((hal_gpio_bit_t)HAL_PIN_PB6)  /**< Constant to define Bit 6 on GPIO B */
#define HAL_GPIO_PB7  ((hal_gpio_bit_t)HAL_PIN_PB7)  /**< Constant to define Bit 7 on GPIO B */
#define HAL_GPIO_PB8  ((hal_gpio_bit_t)HAL_PIN_PB8)  /**< Constant to define Bit 8 on GPIO B */
#define HAL_GPIO_PB9  ((hal_gpio_bit_t)HAL_PIN_PB9)  /**< Constant to define Bit 9 on GPIO B */
#define HAL_GPIO_PB10 ((hal_gpio_bit_t)HAL_PIN_PB10) /**< Constant to define Bit 10 on GPIO B */
#define HAL_GPIO_PB11 ((hal_gpio_bit_t)HAL_PIN_PB11) /**< Constant to define Bit 11 on GPIO B */
#define HAL_GPIO_PB12 ((hal_gpio_bit_t)HAL_PIN_PB12) /**< Constant to define Bit 12 on GPIO B */
#define HAL_GPIO_PB13 ((hal_gpio_bit_t)HAL_PIN_PB13) /**< Constant to define Bit 13 on GPIO B */
#define HAL_GPIO_PB14 ((hal_gpio_bit_t)HAL_PIN_PB14) /**< Constant to define Bit 14 on GPIO B */
#define HAL_GPIO_PB15 ((hal_gpio_bit_t)HAL_PIN_PB15) /**< Constant to define Bit 15 on GPIO B */

#define HAL_GPIO_PC13 ((hal_gpio_bit_t)HAL_PIN_PC13) /**< Constant to define Bit 13 on GPIO C */
#define HAL_GPIO_PC14 ((hal_gpio_bit_t)HAL_PIN_PC14) /**< Constant to define Bit 14 on GPIO C */
#define HAL_GPIO_PC15 ((hal_gpio_bit_t)HAL_PIN_PC15) /**< Constant to define Bit 15 on GPIO C */

#define HAL_GPIO_PD0  ((hal_gpio_bit_t)HAL_PIN_PD0) /**< Constant to define Bit 0 on GPIO D */
#define HAL_GPIO_PD1  ((hal_gpio_bit_t)HAL_PIN_PD1) /**< Constant to define Bit 1 on GPIO D */
/** @endcond */

/* === Public data type declarations =========================================================== */

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* SOC_GPIO_H */
