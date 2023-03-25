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
 ** @brief Digital inputs/outputs on lpc43xx implementation
 **
 ** @addtogroup lpc43xx LPC43xx
 ** @ingroup hal
 ** @brief LPC43xx SOC Hardware abstraction layer
 ** @cond INTERNAL
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "soc_gpio.h"
#include "chip.h"
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

/**
 * @brief Macro to generate the name of an descriptor from the gpio port and bit
 */
#define GPIO_NAME(PORT, BIT) HAL_GPIO##PORT##_##BIT

/**
 * @brief Macro to define an gpio descriptor
 */
#define GPIO_BIT(GPIO, BIT, FUNC, PORT, PIN)                                                       \
    GPIO_NAME(GPIO, BIT) = &(struct hal_gpio_bit_s) {                                              \
        .gpio = GPIO, .bit = BIT, .function = FUNC, .port = PORT, .pin = PIN                       \
    }

/* === Private data type declarations ========================================================== */

/**
 * @brief Structure with the gpio terminal descriptor
 */
struct hal_gpio_bit_s {
    uint8_t gpio : 3;     /**< Number of GPIO port */
    uint8_t bit : 5;      /**< Number of GPIO terminal in port */
    uint8_t function : 3; /**< Function to be assigned for use as a gpio terminal */
    uint8_t pin : 5;      /**< Number of terminals port */
    uint8_t port : 4;     /**< Number of pin in terminal port */
};

/**
 * @brief Structure to store a gpio bit event handler
 */
typedef struct event_handler_s {
    hal_gpio_bit_t gpio;      /**< Pointer to the structure with the gpio terminal descriptor */
    hal_gpio_event_t handler; /**< Function to call on the serial port events */
    void * object;            /**< Pointer to user data sended as parameter in handler calls */
} * event_handler_t;

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/**
 * @brief Function to find the handler used by an gpio or an empty if none was assigned before
 *
 * @param  gpio         Pointer to the structure with the gpio terminal descriptor
 * @param  descriptor   Pointer to variable te return the selected descriptor
 * @return uint8_t      Index descriptor in array, used to assign the channel interrupt
 */
static uint8_t FindHandlerDescriptor(hal_gpio_bit_t gpio, event_handler_t * descriptor);

/**
 * @brief Function to dispatch an gpio bit event when then raises an interrupt
 *
 * @param  index    Index of gpio interrupt channel that raises the event
 */
static void GpioHandleEvent(uint8_t index);

/* === Public variable definitions ============================================================= */

/**
 * @addtogroup lpc43xxGpio GPIO Constants
 * @brief Constant for gpio terminals on board
 * @{
 */
const hal_gpio_bit_t GPIO_BIT(0, 0, 0, 0, 0);   /**< Constant to define Bit 0 on GPIO 0 */
const hal_gpio_bit_t GPIO_BIT(0, 1, 0, 0, 1);   /**< Constant to define Bit 1 on GPIO 0 */
const hal_gpio_bit_t GPIO_BIT(0, 2, 0, 1, 15);  /**< Constant to define Bit 2 on GPIO 0 */
const hal_gpio_bit_t GPIO_BIT(0, 3, 0, 1, 16);  /**< Constant to define Bit 3 on GPIO 0 */
const hal_gpio_bit_t GPIO_BIT(0, 4, 0, 1, 0);   /**< Constant to define Bit 4 on GPIO 0 */
const hal_gpio_bit_t GPIO_BIT(0, 5, 0, 6, 6);   /**< Constant to define Bit 5 on GPIO 0 */
const hal_gpio_bit_t GPIO_BIT(0, 7, 0, 2, 7);   /**< Constant to define Bit 7 on GPIO 0 */
const hal_gpio_bit_t GPIO_BIT(0, 8, 0, 1, 1);   /**< Constant to define Bit 8 on GPIO 0 */
const hal_gpio_bit_t GPIO_BIT(0, 9, 0, 1, 2);   /**< Constant to define Bit 9 on GPIO 0 */
const hal_gpio_bit_t GPIO_BIT(0, 10, 0, 1, 3);  /**< Constant to define Bit 10 on GPIO 0 */
const hal_gpio_bit_t GPIO_BIT(0, 11, 0, 1, 4);  /**< Constant to define Bit 11 on GPIO 0 */
const hal_gpio_bit_t GPIO_BIT(0, 12, 0, 1, 17); /**< Constant to define Bit 12 on GPIO 0 */
const hal_gpio_bit_t GPIO_BIT(0, 13, 0, 1, 18); /**< Constant to define Bit 13 on GPIO 0 */
const hal_gpio_bit_t GPIO_BIT(0, 14, 0, 2, 10); /**< Constant to define Bit 14 on GPIO 0 */
const hal_gpio_bit_t GPIO_BIT(0, 15, 0, 1, 20); /**< Constant to define Bit 15 on GPIO 0 */

const hal_gpio_bit_t GPIO_BIT(1, 8, 0, 1, 5);   /**< Constant to define Bit 4 on GPIO 1 */
const hal_gpio_bit_t GPIO_BIT(1, 9, 0, 1, 6);   /**< Constant to define Bit 8 on GPIO 1 */
const hal_gpio_bit_t GPIO_BIT(1, 11, 0, 2, 11); /**< Constant to define Bit 9 on GPIO 1 */
const hal_gpio_bit_t GPIO_BIT(1, 12, 0, 2, 12); /**< Constant to define Bit 10 on GPIO 1 */

const hal_gpio_bit_t GPIO_BIT(2, 0, 0, 4, 0);  /**< Constant to define Bit 0 on GPIO 2 */
const hal_gpio_bit_t GPIO_BIT(2, 1, 0, 4, 1);  /**< Constant to define Bit 1 on GPIO 2 */
const hal_gpio_bit_t GPIO_BIT(2, 2, 0, 4, 2);  /**< Constant to define Bit 2 on GPIO 2 */
const hal_gpio_bit_t GPIO_BIT(2, 3, 0, 4, 3);  /**< Constant to define Bit 3 on GPIO 2 */
const hal_gpio_bit_t GPIO_BIT(2, 4, 0, 4, 4);  /**< Constant to define Bit 4 on GPIO 2 */
const hal_gpio_bit_t GPIO_BIT(2, 5, 0, 4, 5);  /**< Constant to define Bit 5 on GPIO 2 */
const hal_gpio_bit_t GPIO_BIT(2, 6, 0, 4, 6);  /**< Constant to define Bit 6 on GPIO 2 */
const hal_gpio_bit_t GPIO_BIT(2, 8, 0, 6, 12); /**< Constant to define Bit 8 on GPIO 2 */

const hal_gpio_bit_t GPIO_BIT(3, 0, 0, 6, 1);  /**< Constant to define Bit 0 on GPIO 3 */
const hal_gpio_bit_t GPIO_BIT(3, 1, 0, 6, 2);  /**< Constant to define Bit 1 on GPIO 4 */
const hal_gpio_bit_t GPIO_BIT(3, 2, 0, 6, 3);  /**< Constant to define Bit 2 on GPIO 3 */
const hal_gpio_bit_t GPIO_BIT(3, 3, 0, 6, 4);  /**< Constant to define Bit 3 on GPIO 3 */
const hal_gpio_bit_t GPIO_BIT(3, 4, 0, 6, 5);  /**< Constant to define Bit 4 on GPIO 3 */
const hal_gpio_bit_t GPIO_BIT(3, 5, 0, 6, 9);  /**< Constant to define Bit 5 on GPIO 3 */
const hal_gpio_bit_t GPIO_BIT(3, 6, 0, 6, 10); /**< Constant to define Bit 6 on GPIO 3 */
const hal_gpio_bit_t GPIO_BIT(3, 7, 0, 6, 11); /**< Constant to define Bit 7 on GPIO 3 */
const hal_gpio_bit_t GPIO_BIT(3, 12, 0, 7, 4); /**< Constant to define Bit 12 on GPIO 3 */
const hal_gpio_bit_t GPIO_BIT(3, 13, 0, 7, 5); /**< Constant to define Bit 13 on GPIO 3 */
const hal_gpio_bit_t GPIO_BIT(3, 14, 0, 7, 6); /**< Constant to define Bit 14 on GPIO 3 */
const hal_gpio_bit_t GPIO_BIT(3, 15, 0, 7, 7); /**< Constant to define Bit 15 on GPIO 3 */

const hal_gpio_bit_t GPIO_BIT(4, 11, 0, 9, 6); /**< Constant to define Bit 11 on GPIO 4 */

const hal_gpio_bit_t GPIO_BIT(5, 0, 4, 2, 0);   /**< Constant to define Bit 0 on GPIO 5 */
const hal_gpio_bit_t GPIO_BIT(5, 1, 4, 2, 1);   /**< Constant to define Bit 1 on GPIO 5 */
const hal_gpio_bit_t GPIO_BIT(5, 2, 4, 2, 2);   /**< Constant to define Bit 2 on GPIO 5 */
const hal_gpio_bit_t GPIO_BIT(5, 3, 4, 2, 3);   /**< Constant to define Bit 3 on GPIO 5 */
const hal_gpio_bit_t GPIO_BIT(5, 4, 4, 2, 4);   /**< Constant to define Bit 4 on GPIO 5 */
const hal_gpio_bit_t GPIO_BIT(5, 8, 4, 3, 1);   /**< Constant to define Bit 8 on GPIO 5 */
const hal_gpio_bit_t GPIO_BIT(5, 9, 4, 3, 2);   /**< Constant to define Bit 9 on GPIO 5 */
const hal_gpio_bit_t GPIO_BIT(5, 12, 4, 4, 8);  /**< Constant to define Bit 12 on GPIO 5 */
const hal_gpio_bit_t GPIO_BIT(5, 13, 4, 4, 9);  /**< Constant to define Bit 13 on GPIO 5 */
const hal_gpio_bit_t GPIO_BIT(5, 14, 4, 4, 10); /**< Constant to define Bit 14 on GPIO 5 */
const hal_gpio_bit_t GPIO_BIT(5, 15, 4, 6, 7);  /**< Constant to define Bit 15 on GPIO 5 */
const hal_gpio_bit_t GPIO_BIT(5, 16, 4, 6, 8);  /**< Constant to define Bit 16 on GPIO 5 */
const hal_gpio_bit_t GPIO_BIT(5, 18, 4, 9, 5);  /**< Constant to define Bit 18 on GPIO 5 */
/** @} End of group lpc43xxGpio */

/* === Private variable definitions ============================================================ */

/**
 * @brief Vector to store the event handlers of the serial ports
 */
static struct event_handler_s event_handlers[8] = {0};

/* === Private function implementation ========================================================= */

static uint8_t FindHandlerDescriptor(hal_gpio_bit_t gpio, event_handler_t * descriptor) {
    uint8_t index;
    *descriptor = NULL;

    for (index = 0; index < 7; index++) {
        if (event_handlers[index].gpio == gpio) {
            *descriptor = &event_handlers[index];
            break;
        }
    }
    if (*descriptor == NULL) {
        for (index = 0; index < 7; index++) {
            if (event_handlers[index].gpio == NULL) {
                *descriptor = &event_handlers[index];
                break;
            }
        }
    }
    return index;
}

static void GpioHandleEvent(uint8_t index) {
    event_handler_t descriptor = &event_handlers[index];
    bool rissing = (Chip_PININT_GetRiseStates(LPC_GPIO_PIN_INT) & (1 << index));
    Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, 1 << index);

    if (descriptor->handler != NULL) {
        descriptor->handler(descriptor->gpio, rissing, descriptor->object);
    }
}

/* === Public function implementation ========================================================== */

void GpioSetDirection(hal_gpio_bit_t gpio, bool output) {
    uint32_t value;

    if (output) {
        value = SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS;
    } else {
        value = SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS;
    }
    if (gpio) {
        Chip_SCU_PinMux(gpio->port, gpio->pin, value, gpio->function);
        Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, gpio->gpio, gpio->bit, output);
    }
}

bool GpioGetState(hal_gpio_bit_t gpio) {
    bool value = false;
    if (gpio) {
        value = Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, gpio->gpio, gpio->bit);
    }
    return value;
}

void GpioSetState(hal_gpio_bit_t gpio, bool state) {
    if (gpio) {
        Chip_GPIO_SetPinState(LPC_GPIO_PORT, gpio->gpio, gpio->bit, state);
    }
}

void GpioBitSet(hal_gpio_bit_t gpio) {
    if (gpio) {
        Chip_GPIO_SetPinState(LPC_GPIO_PORT, gpio->gpio, gpio->bit, true);
    }
}

void GpioBitClear(hal_gpio_bit_t gpio) {
    if (gpio) {
        Chip_GPIO_SetPinState(LPC_GPIO_PORT, gpio->gpio, gpio->bit, false);
    }
}

void GpioBitToogle(hal_gpio_bit_t gpio) {
    if (gpio) {
        Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, gpio->gpio, gpio->bit);
    }
}

void GpioSetEventHandler(hal_gpio_bit_t gpio, hal_gpio_event_t handler, void * object, bool rising,
                         bool falling) {

    event_handler_t descriptor;
    uint8_t index = FindHandlerDescriptor(gpio, &descriptor);

    if (descriptor != NULL) {
        if (((rising) || (falling)) && (handler)) {
            descriptor->gpio = gpio;
            descriptor->handler = handler;
            descriptor->object = object;

            Chip_SCU_GPIOIntPinSel(index, gpio->gpio, gpio->bit);
            Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, 1 << index);
            if (rising) {
                Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT, 1 << index);
            }
            if (falling) {
                Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, 1 << index);
            }
            NVIC_ClearPendingIRQ(PIN_INT0_IRQn + index);
            NVIC_SetPriority(PIN_INT0_IRQn + index, HAL_GPIO_NVIC_PRIORITY);
            NVIC_EnableIRQ(PIN_INT0_IRQn + index);
        } else {
            memset(descriptor, 0, sizeof(*descriptor));
            NVIC_EnableIRQ(PIN_INT0_IRQn + index);
        }
    }
}

void GPIO0_IRQHandler(void) {
    GpioHandleEvent(0);
}

void GPIO1_IRQHandler(void) {
    GpioHandleEvent(1);
}

void GPIO2_IRQHandler(void) {
    GpioHandleEvent(2);
}

void GPIO3_IRQHandler(void) {
    GpioHandleEvent(3);
}

void GPIO4_IRQHandler(void) {
    GpioHandleEvent(4);
}

void GPIO5_IRQHandler(void) {
    GpioHandleEvent(5);
}

void GPIO6_IRQHandler(void) {
    GpioHandleEvent(6);
}
void GPIO7_IRQHandler(void) {
    GpioHandleEvent(7);
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen
 ** @endcond */
