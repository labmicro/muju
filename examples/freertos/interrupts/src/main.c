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
#include "semphr.h"
#include "keyboard.h"
#include "serial.h"

/* === Macros definitions ====================================================================== */

#define CONSOLE_SERIAL_PORT 2

#define CONSOLE_BITRATE     115200

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

board_t board;

keyboard_t keyboard;

SemaphoreHandle_t semaforo;

serial_port_t consola;

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
static void SendTask(void * object);

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

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

void EventoSerial(serial_port_t port) {
    BaseType_t planificar = pdFALSE;

    if (xSemaphoreGiveFromISR(semaforo, &planificar) != pdFAIL) {
        portYIELD_FROM_ISR(planificar);
    } else {
        StopByError(board, 7);
    }
}

static void SendTask(void * object) {
    board_t board = object;

    SerialPortOnTransmited(consola, EventoSerial);

    while (true) {
        KeyboardWait(keyboard, EVENT_TEC4_ON);

        GpioBitSet(board->led_3);
        /* Espera que se transmita la primera cadena */
        if (SerialPortTransmit(consola, "Hola ", 5)) {
        }

        /* Espera que se transmita la segunda cadena */
        if (SerialPortTransmit(consola, "Mundo\r\n", 7)) {
        }
        ... Un monton de cosas...

            xSemaphoreTake(semaforo, portMAX_DELAY);

        GpioBitClear(board->led_3);
    }
}

/* === Public function implementation ========================================================= */

int main(void) {

    /* Inicializaciones y configuraciones de dispositivos */
    board = BoardCreate();

    keyboard = KeyboardCreate(board);
    if (keyboard == NULL) {
        StopByError(board, 0);
    }

    consola = SerialPortCreate(CONSOLE_SERIAL_PORT, CONSOLE_BITRATE);

    semaforo = xSemaphoreCreateCounting(1, 0);
    if (semaforo == NULL) {
        StopByError(board, 1);
    }

    /* Creación de las tareas */
    if (xTaskCreate(SendTask, "Serial", 256, (void *)board, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
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
