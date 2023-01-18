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
 ** @brief Serial ports on lpc43xx implementation
 **
 ** @addtogroup lpc43xx LPC43xx
 ** @ingroup hal
 ** @brief LPC43xx SOC Hardware abstraction layer
 ** @cond INTERNAL
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "soc_sci.h"
#include "soc_pin.h"
#include "chip.h"

/**
 *  @brief Include global project config file if it's defined
 */
#ifdef HAL_CONFIG_FILE
#define STR(x)    #x     /**< Macro to convert the argument string to a constant string */
#define TO_STR(x) STR(x) /**< Macro to convert the argument value to a constant string */
#include TO_STR(HAL_CONFIG_FILE)
#endif

/* === Macros definitions ====================================================================== */

/**
 * @brief Macro to configure priority to set on NVIC for serial port interrupts
 */
#ifndef HAL_SCI_NVIC_PRIORITY
#define HAL_SCI_NVIC_PRIORITY 0
#endif

/* === Private data type declarations ========================================================== */

/**
 * @brief Strcuture to store a serial port descriptor
 */
struct hal_sci_s {
    LPC_USART_T * port; /**< Pointer to the memory area with the serial port registers */
    IRQn_Type interupt; /**< Interrupt number corresponding to the serial port */
    uint8_t index;      /**< Numeric index of serial port */
};

/**
 * @brief Structure to store a serial port event handler
 */
typedef struct event_handler_s {
    hal_sci_event_t handler; /**< Function to call on the serial port events */
    void * data;             /**< Pointer to user data sended as parameter in handler calls */
} * event_handler_t;

/* === Private variable declarations =========================================================== */

/* === Private function declarations ===========================================================  */

/**
 * @brief Function to validate and configurate chip pins used by serial port USART0
 *
 * @param   pins    Pointer to structure with chip pins asigned to serial port
 * @return  true    The configuration is valid and has been applied
 * @return  false   The configuration is invalid and has not been applied
 */
static bool ConfigPinsUsart0(hal_sci_pins_t pins);

/**
 * @brief Function to validate and configurate chip pins used by serial port UART1
 *
 * @param   pins    Pointer to structure with chip pins asigned to serial port
 * @return  true    The configuration is valid and has been applied
 * @return  false   The configuration is invalid and has not been applied
 */
static bool ConfigPinsUart1(hal_sci_pins_t pins);

/**
 * @brief Function to validate and configurate chip pins used by serial port USART2
 *
 * @param   pins    Pointer to structure with chip pins asigned to serial port
 * @return  true    The configuration is valid and has been applied
 * @return  false   The configuration is invalid and has not been applied
 */
static bool ConfigPinsUsart2(hal_sci_pins_t pins);

/**
 * @brief Function to validate and configurate chip pins used by serial port USART3
 *
 * @param   pins    Pointer to structure with chip pins asigned to serial port
 * @return  true    The configuration is valid and has been applied
 * @return  false   The configuration is invalid and has not been applied
 */
static bool ConfigPinsUsart3(hal_sci_pins_t pins);

/**
 * @brief Function to encode serial port line parameters as bits required by control register
 *
 * @param   line      Pointer to structure with serial port line parameters
 * @return  uint32_t  Field of bits as defined in control register of serial port
 */
static uint32_t LineEncodeBits(hal_sci_line_t line);

/**
 * @brief Function to dispatch an sci port event when the device raises an interrupt
 *
 * @param  sci  Pointer to the structure with the serial port descriptor
 */
static void SciHandleEvent(hal_sci_t sci);

/* === Public variable definitions ============================================================= */

/**
 * @addtogroup lpc43xxSci USART Constants
 * @brief Constant for serial ports on board
 * @{
 */

/** Constant to define serial port 0 */
const hal_sci_t HAL_SCI_USART0 =
    &(struct hal_sci_s){.port = LPC_USART0, .interupt = USART0_IRQn, .index = 0};

/** Constant to define serial port 1 */
const hal_sci_t HAL_SCI_UART1 =
    &(struct hal_sci_s){.port = LPC_UART1, .interupt = UART1_IRQn, .index = 1};

/** Constant to define serial port 2 */
const hal_sci_t HAL_SCI_USART2 =
    &(struct hal_sci_s){.port = LPC_USART2, .interupt = USART2_IRQn, .index = 2};

/** Constant to define serial port 3 */
const hal_sci_t HAL_SCI_USART3 =
    &(struct hal_sci_s){.port = LPC_USART3, .interupt = USART3_IRQn, .index = 3};

/** @} End of group lpc43xxSci */

/* === Private variable definitions ============================================================ */

/**
 * @brief Vector to store the event handlers of the serial ports
 */
static struct event_handler_s event_handlers[4] = {0};

/* === Private function implementation ========================================================= */

static bool ConfigPinsUsart0(hal_sci_pins_t pins) {
    /*
     * U0_TXD = (P2_0: F1), (P6_4: F2), (P9_5: F7), (PF_10: F1)
     * U0_RXD = (P2_1: F1), (P6_5: F2), (P9_6: F7), (PF_11: F1)
     */
    uint8_t txd_function = 0xFF;
    uint8_t rxd_function = 0xFF;
    bool result = false;

    if (pins->txd_pin == HAL_PIN_P2_0) {
        txd_function = 1;
    } else if (pins->txd_pin == HAL_PIN_P6_4) {
        txd_function = 2;
    } else if (pins->txd_pin == HAL_PIN_P9_5) {
        txd_function = 7;
    }

    if (pins->rxd_pin == HAL_PIN_P2_1) {
        rxd_function = 1;
    } else if (pins->rxd_pin == HAL_PIN_P6_5) {
        rxd_function = 2;
    } else if (pins->rxd_pin == HAL_PIN_P9_6) {
        rxd_function = 7;
    }

    if ((txd_function != 0xFF) && (rxd_function != 0xFF)) {
        ChipPinSetFunction(pins->txd_pin, txd_function, false, false);
        ChipPinSetFunction(pins->rxd_pin, rxd_function, true, false);
        result = true;
    }
    return result;
}

static bool ConfigPinsUart1(hal_sci_pins_t pins) {
    /*
     * U1_TXD = (P1_13: F1), (P3_4: F4), (P5_6: F4), (PC_13: F2), (PE_11: F2)
     * U1_RXD = (P1_14: F1), (P3_5: F4), (P5_7: F4), (PC_14: F2), (PE_12: F2)
     */
    uint8_t txd_function = 0xFF;
    uint8_t rxd_function = 0xFF;
    bool result = false;

    if (pins->txd_pin == HAL_PIN_P1_13) {
        txd_function = 1;
    } else if (pins->txd_pin == HAL_PIN_P3_4) {
        txd_function = 4;
    } else if (pins->txd_pin == HAL_PIN_P5_6) {
        txd_function = 4;
    }

    if (pins->rxd_pin == HAL_PIN_P1_14) {
        rxd_function = 1;
    } else if (pins->rxd_pin == HAL_PIN_P3_5) {
        rxd_function = 4;
    } else if (pins->rxd_pin == HAL_PIN_P5_7) {
        rxd_function = 4;
    }

    if ((txd_function != 0xFF) && (rxd_function != 0xFF)) {
        ChipPinSetFunction(pins->txd_pin, txd_function, false, false);
        ChipPinSetFunction(pins->rxd_pin, rxd_function, true, false);
        result = true;
    }
    return result;
}

static bool ConfigPinsUsart2(hal_sci_pins_t pins) {
    /*
     * U2_TXD = (P1_15: F1), (P2_10: F2), (P7_1: F6), (PA_1: F3)
     * U2_RXD = (P1_16: F1), (P2_11: F2), (P7_2: F6), (PA_2: F3)
     */
    uint8_t txd_function = 0xFF;
    uint8_t rxd_function = 0xFF;
    bool result = false;

    if (pins->txd_pin == HAL_PIN_P1_15) {
        txd_function = 1;
    } else if (pins->txd_pin == HAL_PIN_P2_10) {
        txd_function = 2;
    } else if (pins->txd_pin == HAL_PIN_P7_1) {
        txd_function = 6;
    }

    if (pins->rxd_pin == HAL_PIN_P1_16) {
        rxd_function = 1;
    } else if (pins->rxd_pin == HAL_PIN_P2_11) {
        rxd_function = 2;
    } else if (pins->rxd_pin == HAL_PIN_P7_2) {
        rxd_function = 6;
    }

    if ((txd_function != 0xFF) && (rxd_function != 0xFF)) {
        ChipPinSetFunction(pins->txd_pin, txd_function, false, false);
        ChipPinSetFunction(pins->rxd_pin, rxd_function, true, false);
        result = true;
    }
    return result;
}

static bool ConfigPinsUsart3(hal_sci_pins_t pins) {
    /*
     * U2_TXD = (P2_3: F2), (P4_1: F6), (P9_3: F7), (PF_2: F1)
     * U2_RXD = (P2_4: F2), (P4_2: F6), (P9_4: F7), (PF_3: F1)
     */
    uint8_t txd_function = 0xFF;
    uint8_t rxd_function = 0xFF;
    bool result = false;

    if (pins->txd_pin == HAL_PIN_P2_3) {
        txd_function = 2;
    } else if (pins->txd_pin == HAL_PIN_P4_1) {
        txd_function = 6;
    }

    if (pins->rxd_pin == HAL_PIN_P2_4) {
        rxd_function = 2;
    } else if (pins->rxd_pin == HAL_PIN_P4_2) {
        rxd_function = 6;
    }

    if ((txd_function != 0xFF) && (rxd_function != 0xFF)) {
        ChipPinSetFunction(pins->txd_pin, txd_function, false, false);
        ChipPinSetFunction(pins->rxd_pin, rxd_function, true, false);
        result = true;
    }
    return result;
}

static uint32_t LineEncodeBits(hal_sci_line_t line) {
    uint32_t config;

    config = UART_LCR_SBS_1BIT;
    switch (line->data_bits) {
    case 5:
        config |= UART_LCR_WLEN5;
        break;
    case 6:
        config |= UART_LCR_WLEN6;
        break;
    case 7:
        config |= UART_LCR_WLEN7;
        break;
    default:
        config |= UART_LCR_WLEN8;
        break;
    }

    switch (line->parity) {
    case HAL_SCI_ODD_PARITY:
        config |= UART_LCR_PARITY_EN | UART_LCR_PARITY_ODD;
        break;
    case HAL_SCI_EVEN_PARITY:
        config |= UART_LCR_PARITY_EN | UART_LCR_PARITY_EVEN;
        break;
    case HAL_SCI_MARK_PARITY:
        config |= UART_LCR_PARITY_EN | UART_LCR_PARITY_F_1;
        break;
    case HAL_SCI_SPACE_PARITY:
        config |= UART_LCR_PARITY_EN | UART_LCR_PARITY_F_0;
        break;
    default:
        config |= UART_LCR_PARITY_DIS;
        break;
    }

    return config;
}

static void SciHandleEvent(hal_sci_t sci) {
    if (sci) {
        event_handler_t event_handler = &event_handlers[sci->index];
        struct sci_status_s status;

        (void)Chip_UART_ReadIntIDReg(sci->port);

        SciReadStatus(sci, &status);
        if (event_handler->handler) {
            event_handler->handler(sci, &status, event_handler->data);
        }
    }
}

/* === Public function implementation ========================================================== */

bool SciSetConfig(hal_sci_t sci, hal_sci_line_t line, hal_sci_pins_t pins) {
    bool result = false;

    if (sci) {
        switch (sci->index) {
        case 0:
            result = ConfigPinsUsart0(pins);
            break;
        case 1:
            result = ConfigPinsUart1(pins);
            break;
        case 2:
            result = ConfigPinsUsart2(pins);
            break;
        case 3:
            result = ConfigPinsUsart3(pins);
            break;
        }

        if (result) {
            Chip_UART_Init(sci->port);
            Chip_UART_SetBaud(sci->port, line->baud_rate);
            Chip_UART_ConfigData(sci->port, LineEncodeBits(line));
            Chip_UART_SetupFIFOS(sci->port, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0);
            Chip_UART_TXEnable(sci->port);
        }
    }
    return result;
}

uint16_t SciSendData(hal_sci_t sci, void const * const data, uint16_t size) {
    uint16_t result = 0;
    if (sci) {
        result = Chip_UART_Send(sci->port, data, size);
    }
    return result;
}

uint16_t SciReceiveData(hal_sci_t sci, void * data, uint16_t size) {
    uint16_t result = 0;
    if (sci) {
        result = Chip_UART_Read(sci->port, data, size);
    }
    return result;
}

void SciReadStatus(hal_sci_t sci, sci_status_t result) {
    if (sci) {
        uint32_t status = Chip_UART_ReadLineStatus(sci->port);
        result->data_ready = status & UART_LSR_RDR;
        result->overrun = status & UART_LSR_OE;
        result->parity_error = status & UART_LSR_PE;
        result->framing_error = status & UART_LSR_FE;
        result->break_signal = status & UART_LSR_BI;
        result->fifo_empty = status & UART_LSR_THRE;
        result->tramition_completed = status & UART_LSR_TEMT;
    }
}

void SciSetEventHandler(hal_sci_t sci, hal_sci_event_t handler, void * data) {
    if (sci) {
        event_handler_t event_handler = &event_handlers[sci->index];
        event_handler->handler = handler;
        event_handler->data = data;

        Chip_UART_ReadLineStatus(sci->port);
        NVIC_ClearPendingIRQ(sci->interupt);
        NVIC_SetPriority(sci->interupt, HAL_SCI_NVIC_PRIORITY);
        NVIC_EnableIRQ(sci->interupt);
        Chip_UART_IntEnable(sci->port, UART_IER_RBRINT);
        Chip_UART_IntEnable(sci->port, UART_IER_THREINT);
        Chip_UART_IntEnable(sci->port, UART_IER_RLSINT);
    }
}

void UART0_IRQHandler(void) {
    SciHandleEvent(HAL_SCI_USART0);
}

void UART1_IRQHandler(void) {
    SciHandleEvent(HAL_SCI_UART1);
}

void UART2_IRQHandler(void) {
    SciHandleEvent(HAL_SCI_USART2);
}

void UART3_IRQHandler(void) {
    SciHandleEvent(HAL_SCI_USART3);
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen
 ** @endcond */
