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
 ** @brief Simple sample of use FreeROTS with MUJU hal functions
 **
 ** @addtogroup sample-freertos FreeRTOS Sample
 ** @ingroup samples
 ** @brief Samples applications with MUJU Framwork
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "keyboard.h"
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

/* === Macros definitions ====================================================================== */

#define TASK_STACK    256
#define TASK_PRIORITY tskIDLE_PRIORITY + 2

/* === Private data type declarations ========================================================== */

//! Structure to storage a keybaord descriptor
typedef struct keyboard_s {
    board_t board;                 //!< Pointer to board descriptor
    TaskHandle_t task;             //!< Pointer to task descriptor
    EventGroupHandle_t key_events; //!< Events group to comunicate key actions
};

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/**
 * @brief Allocate a keyboard descriptor
 *
 * @return keyboard_t Pointer to keyboard descriptor
 */
static keyboard_t CreateInstance(void);

/**
 * @brief Function to scan keyboard and send events to another tasks
 *
 * @param  object   Pointer to keyboard descriptor, used as parameter when task created
 */
void KeyboardTask(void * object);

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

static keyboard_t CreateInstance(void) {
    static struct keyboard_s instances = {0};
    keyboard_t result = NULL;

    if ((instances.board == NULL) || (instances.key_events == NULL)) {
        result = &instances;
    }
    return result;
}

static void KeyTask(void * object) {
    keyboard_t self = object;
    uint8_t last_state, current_state, changes, events;

    while (true) {
        vTaskDelay(pdMS_TO_TICKS(150));

        current_state = 0;
        if (!GpioGetState(self->board->tec_1)) {
            current_state |= EVENT_TEC1_ON;
        };
        if (!GpioGetState(self->board->tec_2)) {
            current_state |= EVENT_TEC2_ON;
        };
        if (!GpioGetState(self->board->tec_3)) {
            current_state |= EVENT_TEC3_ON;
        };
        if (!GpioGetState(self->board->tec_4)) {
            current_state |= EVENT_TEC4_ON;
        };

        changes = current_state ^ last_state;
        last_state = current_state;
        events = ((changes & !current_state) << 4) | (changes & current_state);

        xEventGroupSetBits(self->key_events, events);
    }
}

/* === Public function implementation ========================================================= */

keyboard_t KeyboardCreate(board_t board) {
    keyboard_t self = CreateInstance();

    if (self) {
        self->board = board;
        self->key_events = xEventGroupCreate();
        if (self->key_events) {
            xTaskCreate(KeyTask, "Keyboard", TASK_STACK, self, TASK_PRIORITY, &self->task);
        }
    }
    if (self->task == NULL) {
        self = NULL;
    }

    return self;
}

uint8_t KeyboardWait(keyboard_t keyboard, uint8_t events) {
    return xEventGroupWaitBits(keyboard->key_events, events, TRUE, FALSE, portMAX_DELAY);
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
