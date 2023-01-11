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

#ifndef HAL_SCI_H
#define HAL_SCI_H

/** @file
 ** @brief Serial ports declarations
 **
 ** @addtogroup hal HAL
 ** @brief Hardware abstraction layer
 ** @{ */

/* === Headers files inclusions ================================================================ */

#include "hal_pin.h"
#include <stdbool.h>
#include <stdint.h>

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

/* === Public data type declarations =========================================================== */

/**
 * @brief Enumeration to define parity control used by a serial port
 */
typedef enum {
    HAL_SCI_NO_PARITY,    /**< The parity bit is not calculated or transmitted */
    HAL_SCI_ODD_PARITY,   /**< The parity bit is calculated as an odd amount of 1's */
    HAL_SCI_EVEN_PARITY,  /**< The parity bit is calculated as an even amount of 1's */
    HAL_SCI_MARK_PARITY,  /**< The parity bit is always set to 0 */
    HAL_SCI_SPACE_PARITY, /**< The parity bit is always set to 1 */
} sci_parity_t;

/**
 * @brief Structure to define serial port line parameters
 */
typedef struct hal_sci_line_s {
    uint32_t baud_rate;  /**< Baud rate to be used in serial port */
    uint8_t data_bits;   /**< Bit per character to be used in serial port */
    sci_parity_t parity; /**< Parity control to be used in serial port */
} const * hal_sci_line_t;

/**
 * @brief Structure to define chip pins used by a serial port
 */
typedef struct hal_sci_pins_s {
    hal_chip_pin_t txd_pin; /**< Chip pin to be used as transmission line */
    hal_chip_pin_t rxd_pin; /**< Chip pin to be used as reception line */
} const * hal_sci_pins_t;

/**
 * @brief Structure with the status flags of a serial port
 */
typedef struct sci_status_s {
    bool data_ready : 1;          /**< The new data is ready in the input fifo on hardware */
    bool overrun : 1;             /**< Data in input fifo on hardware was overwritten by new data */
    bool parity_error : 1;        /**< Error in the parity check of the received data */
    bool framing_error : 1;       /**< Error in the start or stop bits in the received data */
    bool break_signal : 1;        /**< Signal break detected on reception line */
    bool fifo_empty : 1;          /**< Output fifo on hardware are ready to accept more data */
    bool tramition_completed : 1; /**< Tranmission of data in output fifo on hardware completed */
} * sci_status_t;

/**
 * @brief Pointer to the structure with the serial port descriptor
 */
typedef struct hal_sci_s * hal_sci_t;

/**
 * @brief Callback function to handle a serial port events
 *
 * @param  sci      Pointer to structure with descriptor of serial port that raises the event
 * @param  status   Pointer to structure with flags that raises the event
 * @param  object   Pointer to user data declared when handler event has installed
 */
typedef void (*hal_sci_event_t)(hal_sci_t sci, sci_status_t status, void * object);

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */

/**
 * @brief Function to configure a serial port before to use it
 *
 * @param  sci      Pointer to the structure with the serial port descriptor
 * @param  line     Pointer to structure with line configuration for serial port
 * @param  pins     Pointer to structure with chip pins used by serial port
 * @return true     The settings are valid and the serial port is ready to operate
 * @return false    The settings are invalid and the serial port was not initialized
 */
bool SciSetConfig(hal_sci_t sci, hal_sci_line_t line, hal_sci_pins_t pins);

/**
 * @brief Function to put data into output fifo on hardware
 *
 * @param  sci      Pointer to the structure with the serial port descriptor
 * @param  data     Pointer to buffer with data to put in output fifo
 * @param  size     Length of data to put in output fifo
 * @return uint16_t Amount of data actually put in output fifo
 */
uint16_t SciSendData(hal_sci_t sci, void const * const data, uint16_t size);

/**
 * @brief Function to get data from input fifo on hardware
 *
 * @param  sci      Pointer to the structure with the serial port descriptor
 * @param  data     Pointer to the buffer to store data from input fifo
 * @param  size     Length of data to get from input fifo
 * @return uint16_t Amount of data actually get from input fifo
 */
uint16_t SciReceiveData(hal_sci_t sci, void * data, uint16_t size);

/**
 * @brief Function to read serial port status flags
 *
 * @param  sci      Pointer to the structure with the serial port descriptor
 * @param  result   Pointer to structure to write the status flags of a serial port
 */
void SciReadStatus(hal_sci_t sci, sci_status_t result);

/**
 * @brief Function enable serial port interrupts and handle its as events
 *
 * @param  sci      Pointer to the structure with the serial port descriptor
 * @param  handler  Function to call on the serial port events
 * @param  object   Pointer to user data sended as parameter in handler calls
 */
void SciSetEventHandler(hal_sci_t sci, hal_sci_event_t handler, void * object);

/* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* HAL_SCI_H */
