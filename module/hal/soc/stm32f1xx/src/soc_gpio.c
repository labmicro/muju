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
 ** @brief Digital inputs/outputs on STM32F1xx implementation
 **
 ** @addtogroup stmf32f1xx STM32F1xx
 ** @ingroup hal
 ** @brief STM32F1xx SOC Hardware abstraction layer
 ** @cond INTERNAL
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "soc_gpio.h"
#include "stm32f1xx_hal.h"
#include <string.h>

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
#ifndef HAL_GPIO_NVIC_PRIORITY
#define HAL_GPIO_NVIC_PRIORITY 0
#endif

/* === Private data type declarations ========================================================== */

/** @brief Structure to store a gpio bit event handler */
typedef struct event_handler_s {
    hal_gpio_bit_t gpio;      /**< Pointer to the structure with the gpio terminal descriptor */
    hal_gpio_event_t handler; /**< Function to call on the serial port events */
    void * object;            /**< Pointer to user data sended as parameter in handler calls */
} * event_handler_t;

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/**
 * @brief Function to dispatch an gpio bit event when then raises an interrupt
 *
 * @param  index    Index of gpio interrupt channel that raises the event
 */
static void GpioHandleEvent(uint8_t index);

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/**
 * @brief Vector to store the event handlers of the serial ports
 */
static struct event_handler_s event_handlers[16] = {0};

/**
 * @brief Vector to store the port address required to operate with ST HAL functions
 */
static GPIO_TypeDef * const gpio_ports[] = {GPIOA, GPIOB, GPIOC, GPIOD};

/* === Private function implementation ========================================================= */

static void GpioHandleEvent(uint8_t index) {
    event_handler_t descriptor = &event_handlers[index];
    SET_BIT(EXTI->PR, 1 << index);
    bool rissing = GpioGetState(descriptor->gpio);

    if (descriptor->handler != NULL) {
        descriptor->handler(descriptor->gpio, rissing, descriptor->object);
    }
}

/* === Public function implementation ========================================================== */

void GpioSetDirection(hal_gpio_bit_t gpio, bool output) {
    GPIO_InitTypeDef pin_config = {0};

    if (output) {
        pin_config.Mode = GPIO_MODE_OUTPUT_PP;
        pin_config.Pull = GPIO_NOPULL;
        pin_config.Speed = GPIO_SPEED_FREQ_LOW;
    } else {
        pin_config.Mode = GPIO_MODE_INPUT;
        pin_config.Pull = GPIO_PULLUP;
    }

    if (gpio) {
        hal_chip_pin_t pin = (hal_chip_pin_t)gpio;
        switch (pin->port) {
        case HAL_PORT_A:
            __HAL_RCC_GPIOA_CLK_ENABLE();
            break;
        case HAL_PORT_B:
            __HAL_RCC_GPIOB_CLK_ENABLE();
            break;
        case HAL_PORT_C:
            __HAL_RCC_GPIOC_CLK_ENABLE();
            break;
        case HAL_PORT_D:
            __HAL_RCC_GPIOD_CLK_ENABLE();
            break;
        default:
            break;
        }

        pin_config.Pin = 1 << pin->pin;
        HAL_GPIO_Init(gpio_ports[pin->port], &pin_config);
    }
}

bool GpioGetState(hal_gpio_bit_t gpio) {
    bool value = false;
    if (gpio) {
        hal_chip_pin_t pin = (hal_chip_pin_t)gpio;
        value = HAL_GPIO_ReadPin(gpio_ports[pin->port], 1 << pin->pin);
    }
    return value;
}

void GpioSetState(hal_gpio_bit_t gpio, bool state) {
    if (gpio) {
        hal_chip_pin_t output = (hal_chip_pin_t)gpio;
        HAL_GPIO_WritePin(gpio_ports[output->port], 1 << output->pin,
                          state ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
}

void GpioBitSet(hal_gpio_bit_t gpio) {
    if (gpio) {
        hal_chip_pin_t output = (hal_chip_pin_t)gpio;
        HAL_GPIO_WritePin(gpio_ports[output->port], 1 << output->pin, GPIO_PIN_SET);
    }
}

void GpioBitClear(hal_gpio_bit_t gpio) {
    if (gpio) {
        hal_chip_pin_t output = (hal_chip_pin_t)gpio;
        HAL_GPIO_WritePin(gpio_ports[output->port], 1 << output->pin, GPIO_PIN_RESET);
    }
}

void GpioBitToogle(hal_gpio_bit_t gpio) {
    if (gpio) {
        hal_chip_pin_t output = (hal_chip_pin_t)gpio;
        HAL_GPIO_TogglePin(gpio_ports[output->port], 1 << output->pin);
    }
}

void GpioSetEventHandler(hal_gpio_bit_t gpio, hal_gpio_event_t handler, void * object, bool rising,
                         bool falling) {

    uint32_t value;
    IRQn_Type irq_number;
    hal_chip_pin_t input = (hal_chip_pin_t)gpio;
    event_handler_t descriptor = &event_handlers[input->pin];

    if (input->pin >= 10) {
        irq_number = EXTI15_10_IRQn;
    } else if (input->pin >= 5) {
        irq_number = EXTI9_5_IRQn;
    } else {
        irq_number = EXTI0_IRQn + input->pin;
    }

    if (((rising) || (falling)) && (handler)) {
        if (descriptor->handler == NULL) {
            descriptor->gpio = gpio;
            descriptor->handler = handler;
            descriptor->object = object;

            /* Enable AFIO Clock */
            __HAL_RCC_AFIO_CLK_ENABLE();
            value = AFIO->EXTICR[input->pin >> 2u];
            CLEAR_BIT(value, (0x0Fu) << (4u * (input->pin & 0x03u)));
            SET_BIT(value, (input->port) << (4u * (input->pin & 0x03u)));
            AFIO->EXTICR[input->pin >> 2u] = value;

            /* Configure the interrupt mask */
            SET_BIT(EXTI->IMR, 1 << input->pin);

            /* Configure the event mask */
            CLEAR_BIT(EXTI->EMR, 1 << input->pin);

            /* Enable or disable the rising trigger */
            if (rising) {
                SET_BIT(EXTI->RTSR, 1 << input->pin);
            } else {
                CLEAR_BIT(EXTI->RTSR, 1 << input->pin);
            }

            /* Enable or disable the falling trigger */
            if (falling) {
                SET_BIT(EXTI->FTSR, 1 << input->pin);
            } else {
                CLEAR_BIT(EXTI->FTSR, 1 << input->pin);
            }

            SET_BIT(EXTI->PR, 1 << input->pin);
            NVIC_ClearPendingIRQ(irq_number);
            NVIC_SetPriority(irq_number, HAL_GPIO_NVIC_PRIORITY);
            NVIC_EnableIRQ(irq_number);
        }
    } else {
        descriptor->handler = NULL;
        SET_BIT(EXTI->PR, 1 << input->pin);
        NVIC_ClearPendingIRQ(irq_number);
        NVIC_DisableIRQ(irq_number);
    }
}

void EXTI0_IRQHandler(void) {
    GpioHandleEvent(0);
}

void EXTI1_IRQHandler(void) {
    GpioHandleEvent(1);
}

void EXTI2_IRQHandler(void) {
    GpioHandleEvent(2);
}

void EXTI3_IRQHandler(void) {
    GpioHandleEvent(3);
}

void EXTI4_IRQHandler(void) {
    GpioHandleEvent(4);
}

void EXTI9_5_IRQHandler(void) {
    for (int index = 5; index <= 9; index++) {
        if (READ_BIT(EXTI->PR, 1 << index)) {
            GpioHandleEvent(index);
        }
    }
}

void EXTI15_10_IRQHandler(void) {
    for (int index = 10; index <= 15; index++) {
        if (READ_BIT(EXTI->PR, 1 << index)) {
            GpioHandleEvent(index);
        }
    }
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen
 ** @endcond */
