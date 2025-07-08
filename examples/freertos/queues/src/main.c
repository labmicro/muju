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

#include "bsp.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

typedef struct action_s {
    hal_gpio_bit_t led;
    uint32_t delay;
} * action_t;

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/**
 * @brief Function to inform an error and stop program execution
 *
 * @param  board   Pointer to board descriptor
 * @param  code    Code of error ocurred
 */
void StopByError(board_t board, uint8_t code);

/**
 * @brief Function to flash a led for a while
 *
 * @param  object   Pointer to task parameters structure, used as parameter when task created
 */
static void FlashTask(void * object);

/**
 * @brief Function to scan keyboard and send events to another tasks
 *
 * @param  object   Pointer to board descriptor, used as parameter when task created
 */
static void KeyTask(void * object);

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/**
 * @brief Queue data to comunicate tasks
 */
QueueHandle_t actions;

/* === Private function implementation ========================================================= */

void StopByError(board_t board, uint8_t code) {
    // Signal error condition
    GpioBitSet(board->led_rgb->red);

    // Show error code
    GpioSetState(board->led_1, code & (1 << 0));
    GpioSetState(board->led_2, code & (1 << 1));
    GpioSetState(board->led_3, code & (1 << 2));

    // Stop program execution
    while (true) {
    };
}

static void FlashTask(void * object) {
    board_t board = object;
    struct action_s action;

    while (true) {
        xQueueReceive(actions, &action, portMAX_DELAY);
        GpioBitToogle(board->led_rgb->blue);

        GpioBitSet(action.led);
        vTaskDelay(pdMS_TO_TICKS(action.delay));
        GpioBitClear(action.led);
        vTaskDelay(pdMS_TO_TICKS(action.delay));
    }
}

static void KeyTask(void * object) {
    board_t board = object;
    bool current_state, last_state[4] = {false, false, false, false};
    struct action_s action;

    while (true) {
        vTaskDelay(pdMS_TO_TICKS(150));

        current_state = !GpioGetState(board->tec_1);
        if ((current_state != last_state[0]) && (current_state)) {
        }
        last_state[0] = current_state;

        current_state = !GpioGetState(board->tec_2);
        if ((current_state != last_state[1]) && (current_state)) {
            action.led = board->led_1;
            action.delay = 750;
            xQueueSend(actions, &action, portMAX_DELAY);
        }
        last_state[1] = current_state;

        current_state = !GpioGetState(board->tec_3);
        if ((current_state != last_state[2]) && (current_state)) {
            action.led = board->led_2;
            action.delay = 500;
            xQueueSend(actions, &action, portMAX_DELAY);
        }
        last_state[2] = current_state;

        current_state = !GpioGetState(board->tec_4);
        if ((current_state != last_state[3]) && (current_state)) {
            action.led = board->led_3;
            action.delay = 1000;
            xQueueSend(actions, &action, portMAX_DELAY);
            xQueueSend(actions, &action, portMAX_DELAY);
        }
        last_state[3] = current_state;
    }
}

/* === Public function implementation ========================================================= */

int main(void) {
    /* Inicializaciones y configuraciones de dispositivos */
    board_t board = BoardCreate();

    actions = xQueueCreate(4, sizeof(struct action_s));
    if (actions == NULL) {
        StopByError(board, 0);
    }

    /* Creación de las tareas */
    if (xTaskCreate(KeyTask, "Keys", 256, (void *)board, tskIDLE_PRIORITY + 2, NULL) != pdPASS) {
        StopByError(board, 1);
    }
    if (xTaskCreate(FlashTask, "Flash", 256, (void *)board, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
        StopByError(board, 2);
    }

    /* Arranque del sistema operativo */
    vTaskStartScheduler();

    /* vTaskStartScheduler solo retorna si se detiene el sistema operativo */
    while (true) {
    }

    /* El valor de retorno es solo para evitar errores en el compilador*/
    return 0;
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
