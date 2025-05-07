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

#ifndef SERIAL_H
#define SERIAL_H

/** @file
 ** @brief Serial asynconous port declarations
 **
 ** @addtogroup sample-freertos FreeRTOS Sample
 ** @ingroup samples
 ** @brief Samples applications with MUJU Framwork
 ** @{ */

/* === Headers files inclusions ================================================================ */

#include <stdbool.h>
#include <stdint.h>

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

//! Referencia a un descriptor para gestionar puerto serial asincronico
typedef struct serial_port_s * serial_port_t;

typedef void (*serial_event_t)(serial_port_t);

/* === Public data type declarations =========================================================== */

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/**
 * @brief Metodo para crear un puerto serial asincronico
 *
 * @param   port            Puerto serial aseincrónico que se utiliza
 * @param   bitrate         Velocidad de transmisión del puerto
 * @return  serial_port_t   Puntero al descriptor de la salida creada
 */
serial_port_t SerialPortCreate(uint8_t port, uint32_t bitrate);

/**
 * @brief Metodo para enviar datos por un puerto serial
 *
 * @param   port    Puntero al descriptor de la entrada
 * @return  true    La entrada esta activa
 * @return  false   La entrada esta inactiva
 */
uint8_t SerialPortTransmit(serial_port_t port, void const * const data, uint8_t size);

/**
 * @brief Metodo para consultar cambios en el estado de una entrada digital
 *
 * @param   input   Puntero al descriptor de la entrada
 * @return  true    La entrada tuvo cambios desde la ultima llamada
 * @return  false   La entrada no tuvo cambios desde la ultima llamada
 */
uint8_t SerialPortReceive(serial_port_t port, void const * const data, uint8_t size);

void SerialPortOnTransmited(serial_port_t port, serial_event_t handler);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* SERIAL_H */
