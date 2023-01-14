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

#ifndef HAL_GPIO_H
#define HAL_GPIO_H

/** @file
 ** @brief Digital inputs/outputs declarations
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
 * @brief Pointer to the structure with the gpio terminal descriptor
 */
typedef struct hal_gpio_bit_s const * hal_gpio_bit_t;

/**
 * @brief Callback function to handle a gpio port events
 *
 * @param  gpio     Pointer to the structure with the gpio terminal descriptor
 * @param  object   Pointer to user data declared when handler event has installed
 */
typedef void (*hal_gpio_event_t)(hal_gpio_bit_t gpio, bool rissing, void * object);

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/**
 * @brief Function to set an gpio pin as input or output
 *
 * @param  gpio     Pointer to the structure with the gpio terminal descriptor
 * @param  output   The gpio terminal should be configured as input or output
 * @arg @c true     The gpio terminal is configures as an output
 * @arg @c false    The gpio terminal is configures as an input
 *
 */
void GpioSetDirection(hal_gpio_bit_t gpio, bool output);

/**
 * @brief Function to the current value of an gpio input or output
 *
 * @param  gpio     Pointer to the structure with the gpio terminal descriptor
 * @return true     The current value of the gpio intput or output is high
 * @return false    The current value of the gpio intput or output is output
 */
bool GpioGetState(hal_gpio_bit_t gpio);

/**
 * @brief Function to update the current value of an gpio output
 *
 * @param  gpio     Pointer to the structure with the gpio terminal descriptor
 * @param  state    Value to write to the gpio output
 * @arg @c true     The current value of the gpio output is changed to high
 * @arg @c false    The current value of the gpio output is changed to low
 */
void GpioSetState(hal_gpio_bit_t gpio, bool state);

/**
 * @brief Function to set the current value to high of an gpio output
 *
 * @param  gpio     Pointer to the structure with the gpio terminal descriptor
 */
void GpioBitSet(hal_gpio_bit_t gpio);

/**
 * @brief Function to set the current value to low of an gpio output
 *
 * @param  gpio     Pointer to the structure with the gpio terminal descriptor
 */
void GpioBitClear(hal_gpio_bit_t gpio);

/**
 * @brief Function to interchange the current value of an gpio output
 *
 * @param  gpio     Pointer to the structure with the gpio terminal descriptor
 */
void GpioBitToogle(hal_gpio_bit_t gpio);

/**
 * @brief Function to enable gpio port interrupts and handle its as events
 *
 * @param  gpio     Pointer to the structure with the gpio terminal descriptor
 * @param  handler  Function to call on the gpio bit events
 * @param  object   Pointer to user data sended as parameter in handler calls
 */
void GpioSetEventHandler(hal_gpio_bit_t gpio, hal_gpio_event_t handler, void * object, bool rising,
                         bool falling);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* HAL_GPIO_H */
