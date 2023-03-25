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
 ** @brief Serial ports on STM32F1xx implementation
 **
 ** @addtogroup stmf32f1xx STM32F1xx
 ** @ingroup hal
 ** @brief STM32F1xx SOC Hardware abstraction layer
 ** @cond INTERNAL
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "soc_sci.h"
#include "soc_pin.h"
#include "stm32f1xx_hal.h"

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
    USART_TypeDef * port; /**< Pointer to the memory area with the serial port registers */
    IRQn_Type interupt;   /**< Interrupt number corresponding to the serial port */
    uint8_t index;        /**< Numeric index of serial port */
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
 * @param   config    Pointer to structure with ST HAL uart config parameters
 * @return  true      The configuration is valid and has been applied
 * @return  false     The configuration is invalid and has not been applied
 */
static bool LineEncodeBits(hal_sci_line_t line, UART_InitTypeDef * config);

/**
 * @brief Function to dispatch an sci port event when the device raises an interrupt
 *
 * @param  sci  Pointer to the structure with the serial port descriptor
 */
static void SciHandleEvent(hal_sci_t sci);

/* === Public variable definitions ============================================================= */

/**
 * @addtogroup stmf32f1xx USART Constants
 * @brief Constant for serial ports on board
 * @{
 */

/** Constant to define serial port 1 */
const hal_sci_t HAL_SCI_USART1 =
    &(struct hal_sci_s){.port = USART1, .interupt = USART1_IRQn, .index = 0};

/** Constant to define serial port 2 */
const hal_sci_t HAL_SCI_USART2 =
    &(struct hal_sci_s){.port = USART2, .interupt = USART2_IRQn, .index = 1};

/** Constant to define serial port 3 */
const hal_sci_t HAL_SCI_USART3 =
    &(struct hal_sci_s){.port = USART3, .interupt = USART3_IRQn, .index = 2};

/** @} End of group stmf32f1xx */

/* === Private variable definitions ============================================================ */

/**
 * @brief Vector to store the event handlers of the serial ports
 */
static struct event_handler_s event_handlers[4] = {0};

/**
 * @brief Vector to store the usart handlers required by ST HAL to operate on serial ports
 */
UART_HandleTypeDef usart_handlers[3];

/* === Private function implementation ========================================================= */

static bool ConfigPinsUart1(hal_sci_pins_t pins) {
    GPIO_InitTypeDef pin_config = {0};
    uint8_t option = 0;
    bool result = false;

    if ((pins->txd_pin == HAL_PIN_PA9) && (pins->rxd_pin == HAL_PIN_PA10)) {
        option = 1;
    } else if ((pins->txd_pin == HAL_PIN_PB6) && (pins->rxd_pin == HAL_PIN_PB7)) {
        option = 2;
    }

    if (option != 0) {
        __HAL_RCC_USART1_CLK_ENABLE();
        if (option == 1) {
            __HAL_RCC_GPIOA_CLK_ENABLE();
            __HAL_AFIO_REMAP_USART1_DISABLE();
        } else {
            __HAL_RCC_GPIOB_CLK_ENABLE();
            __HAL_AFIO_REMAP_USART1_ENABLE();
        }

        pin_config.Mode = GPIO_MODE_AF_PP;
        pin_config.Speed = GPIO_SPEED_FREQ_HIGH;
        if (option == 1) {
            pin_config.Pin = GPIO_PIN_9;
            HAL_GPIO_Init(GPIOA, &pin_config);
        } else {
            pin_config.Pin = GPIO_PIN_6;
            HAL_GPIO_Init(GPIOB, &pin_config);
        }

        pin_config.Mode = GPIO_MODE_INPUT;
        pin_config.Pull = GPIO_NOPULL;
        if (option == 1) {
            pin_config.Pin = GPIO_PIN_10;
            HAL_GPIO_Init(GPIOA, &pin_config);
        } else {
            pin_config.Pin = GPIO_PIN_7;
            HAL_GPIO_Init(GPIOB, &pin_config);
        }

        result = true;
    }
    return result;
}

static bool ConfigPinsUsart2(hal_sci_pins_t pins) {
    /*
     * U2_TXD = (P1_15: F1), (P2_10: F2), (P7_1: F6), (PA_1: F3)
     * U2_RXD = (P1_16: F1), (P2_11: F2), (P7_2: F6), (PA_2: F3)
     */
    // uint8_t txd_function = 0xFF;
    // uint8_t rxd_function = 0xFF;
    bool result = false;

    // if (pins->txd_pin == HAL_PIN_P1_15) {
    //     txd_function = 1;
    // } else if (pins->txd_pin == HAL_PIN_P2_10) {
    //     txd_function = 2;
    // } else if (pins->txd_pin == HAL_PIN_P7_1) {
    //     txd_function = 6;
    // }

    // if (pins->rxd_pin == HAL_PIN_P1_16) {
    //     rxd_function = 1;
    // } else if (pins->rxd_pin == HAL_PIN_P2_11) {
    //     rxd_function = 2;
    // } else if (pins->rxd_pin == HAL_PIN_P7_2) {
    //     rxd_function = 6;
    // }

    // if ((txd_function != 0xFF) && (rxd_function != 0xFF)) {
    //     ChipPinSetFunction(pins->txd_pin, txd_function, false, false);
    //     ChipPinSetFunction(pins->rxd_pin, rxd_function, true, false);
    //     result = true;
    // }
    return result;
}

static bool ConfigPinsUsart3(hal_sci_pins_t pins) {
    /*
     * U2_TXD = (P2_3: F2), (P4_1: F6), (P9_3: F7), (PF_2: F1)
     * U2_RXD = (P2_4: F2), (P4_2: F6), (P9_4: F7), (PF_3: F1)
     */
    // uint8_t txd_function = 0xFF;
    // uint8_t rxd_function = 0xFF;
    bool result = false;

    // if (pins->txd_pin == HAL_PIN_P2_3) {
    //     txd_function = 2;
    // } else if (pins->txd_pin == HAL_PIN_P4_1) {
    //     txd_function = 6;
    // }

    // if (pins->rxd_pin == HAL_PIN_P2_4) {
    //     rxd_function = 2;
    // } else if (pins->rxd_pin == HAL_PIN_P4_2) {
    //     rxd_function = 6;
    // }

    // if ((txd_function != 0xFF) && (rxd_function != 0xFF)) {
    //     ChipPinSetFunction(pins->txd_pin, txd_function, false, false);
    //     ChipPinSetFunction(pins->rxd_pin, rxd_function, true, false);
    //     result = true;
    // }
    return result;
}

static bool LineEncodeBits(hal_sci_line_t line, UART_InitTypeDef * config) {
    bool result = true;

    config->StopBits = UART_STOPBITS_1;
    switch (line->data_bits) {
    case 8:
        config->WordLength = UART_WORDLENGTH_8B;
        break;
    default:
        result = false;
        break;
    }

    switch (line->parity) {
    case HAL_SCI_ODD_PARITY:
        config->Parity = UART_PARITY_ODD;
        break;
    case HAL_SCI_EVEN_PARITY:
        config->Parity = UART_PARITY_EVEN;
        break;
    case HAL_SCI_NO_PARITY:
        config->Parity = UART_PARITY_NONE;
        break;
    default:
        result = false;
        break;
    }

    return result;
}

static void SciHandleEvent(hal_sci_t sci) {
    if (sci) {
        event_handler_t event_handler = &event_handlers[sci->index];
        struct sci_status_s status;

        SciReadStatus(sci, &status);
        if (event_handler->handler) {
            event_handler->handler(sci, &status, event_handler->data);
        }

        UART_HandleTypeDef * handler = &usart_handlers[sci->index];
        if (__HAL_UART_GET_FLAG(handler, UART_FLAG_TXE)) {
            __HAL_UART_DISABLE_IT(handler, UART_IT_TXE);
        }
    }
}

/* === Public function implementation ========================================================== */

bool SciSetConfig(hal_sci_t sci, hal_sci_line_t line, hal_sci_pins_t pins) {
    bool result = false;

    if (sci) {
        switch (sci->index) {
        case 0:
            result = ConfigPinsUart1(pins);
            break;
        case 1:
            result = ConfigPinsUsart2(pins);
            break;
        case 2:
            result = ConfigPinsUsart3(pins);
            break;
        }

        if (result) {
            UART_HandleTypeDef * handler = &usart_handlers[sci->index];
            handler->Instance = sci->port;
            handler->Init.BaudRate = line->baud_rate;
            handler->Init.Mode = UART_MODE_TX_RX;
            handler->Init.HwFlowCtl = UART_HWCONTROL_NONE;
            handler->Init.OverSampling = UART_OVERSAMPLING_16;

            LineEncodeBits(line, &handler->Init);
            result = HAL_UART_Init(handler) == HAL_OK;
        }
    }
    return result;
}

uint16_t SciSendData(hal_sci_t sci, void const * const data, uint16_t size) {
    uint16_t result = 0;
    if (sci) {
        UART_HandleTypeDef * handler = &usart_handlers[sci->index];
        event_handler_t event_handler = &event_handlers[sci->index];

        HAL_UART_Transmit(handler, (uint8_t *)data, 1, 1);
        result = 1;

        if ((result < size) && (event_handler->handler != NULL)) {
            UART_HandleTypeDef * handler = &usart_handlers[sci->index];
            __HAL_UART_ENABLE_IT(handler, UART_IT_TXE);
        }
    }
    return result;
}

uint16_t SciReceiveData(hal_sci_t sci, void * data, uint16_t size) {
    uint16_t result = 0;
    if (sci) {
        UART_HandleTypeDef * handler = &usart_handlers[sci->index];

        HAL_UART_Receive(handler, (uint8_t *)data, 1, 1);
        result = 1;
    }
    return result;
}

void SciReadStatus(hal_sci_t sci, sci_status_t result) {
    if (sci) {
        UART_HandleTypeDef * handler = &usart_handlers[sci->index];
        result->data_ready = __HAL_UART_GET_FLAG(handler, UART_FLAG_RXNE);
        result->overrun = __HAL_UART_GET_FLAG(handler, UART_FLAG_ORE);
        result->parity_error = __HAL_UART_GET_FLAG(handler, UART_FLAG_PE);
        result->framing_error = __HAL_UART_GET_FLAG(handler, UART_FLAG_FE);
        result->break_signal = __HAL_UART_GET_FLAG(handler, UART_FLAG_LBD);
        result->fifo_empty = __HAL_UART_GET_FLAG(handler, UART_FLAG_TXE);
        result->tramition_completed = __HAL_UART_GET_FLAG(handler, UART_FLAG_TC);
    }
}

void SciSetEventHandler(hal_sci_t sci, hal_sci_event_t handler, void * data) {
    if (sci) {
        event_handler_t event_handler = &event_handlers[sci->index];
        event_handler->handler = handler;
        event_handler->data = data;

        NVIC_ClearPendingIRQ(sci->interupt);
        NVIC_SetPriority(sci->interupt, HAL_SCI_NVIC_PRIORITY);
        NVIC_EnableIRQ(sci->interupt);

        UART_HandleTypeDef * handler = &usart_handlers[sci->index];
        __HAL_UART_ENABLE_IT(handler, UART_IT_RXNE);
        __HAL_UART_ENABLE_IT(handler, UART_IT_PE | UART_IT_LBD | UART_IT_PE);
    }
}

void USART1_IRQHandler(void) {
    SciHandleEvent(HAL_SCI_USART1);
}

void USART2_IRQHandler(void) {
    SciHandleEvent(HAL_SCI_USART2);
}

void USART3_IRQHandler(void) {
    SciHandleEvent(HAL_SCI_USART3);
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen
 ** @endcond */
