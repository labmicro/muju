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
 ** @brief System timer on posix implementation
 **
 ** @addtogroup posix Posix
 ** @ingroup hal
 ** @brief Posix SOC Hardware abstraction layer
 ** @cond INTERNAL
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "soc_tick.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/**
 * @brief Pointer to the structure with the system timer descriptor
 */
typedef struct hal_tick_s {
    pthread_t thread;         /**< Pointer to thread used to simulate timers events */
    hal_tick_event_t handler; /**< Function to call on the system timer events */
    void * object;            /**< Pointer to user data sended as parameter in handler calls */
    uint32_t period;          /**< Period, in microseconds, between each system timer event */
} * hal_tick_t;

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/**
 * @brief Function to implement a main loop of a thread send timer events
 *
 * @param _         Pointer to initial data, required by function prototype, unused
 * @return void*    Pointer to result data, required by function prototype, unused
 */
static void * TimerThread(void * _);

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/**
 * @brief Variable with the instance of system timer descriptor
 */
static struct hal_tick_s instance[1] = {0};

/* === Private function implementation ========================================================= */

static void * TimerThread(void * _) {
    while (true) {
        usleep(instance->period);
        if (instance->handler) {
            instance->handler(instance->object);
        }
    }
    return 0;
}

/* === Public function implementation ========================================================== */

void TickStart(hal_tick_event_t handler, void * object, uint32_t period) {
    instance->handler = handler;
    instance->object = object;
    instance->period = period;
    pthread_create(&instance->thread, NULL, TimerThread, NULL);
}

void SysTick_Handler(void) {
    if (instance->handler) {
        instance->handler(instance->object);
    }
}
/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen
 ** @endcond */
