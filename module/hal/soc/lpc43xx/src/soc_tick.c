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
 ** @brief System timer on lpc43xx implementation
 **
 ** @addtogroup lpc43xx LPC43xx
 ** @ingroup hal
 ** @brief LPC43xx SOC Hardware abstraction layer
 ** @cond INTERNAL
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "soc_tick.h"
#include "chip.h"

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/**
 * @brief Pointer to the structure with the system timer descriptor
 */
typedef struct hal_tick_s {
    hal_tick_event_t handler; /**< Function to call on the system timer events */
    void * object;            /**< Pointer to user data sended as parameter in handler calls */
} * hal_tick_t;

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/**
 * @brief Variable with the instance of system timer descriptor
 */
static struct hal_tick_s instance[1] = {0};

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */

void TickStart(hal_tick_event_t handler, void * object, uint32_t period) {
    __asm volatile("cpsid i");

    instance->handler = handler;
    instance->object = object;

    /* Activate SysTick */
    SystemCoreClockUpdate();
    SysTick_Config((SystemCoreClock / 1000000) * period);

    /* Update priority set by SysTick_Config */
    NVIC_SetPriority(SysTick_IRQn, (1 << __NVIC_PRIO_BITS) - 1);

    __asm volatile("cpsie i");
}

void SysTick_Handler(void) {
    if (instance->handler) {
        instance->handler(instance->object);
    }
}
/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen
 ** @endcond */
