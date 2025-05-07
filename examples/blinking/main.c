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

/** \brief Hello World sample application
 **
 ** \addtogroup samples Samples
 ** \brief Samples applications with MUJU Framwork
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "board.h"
#include <stdio.h>

/* === Macros definitions ====================================================================== */

#define LEDn           4U

#define LED1_PIN       GPIO_PIN_13
#define LED1_GPIO_PORT GPIOC
#define LED1_GPIO_CLK  RCU_GPIOC

#define LED2_PIN       GPIO_PIN_1
#define LED2_GPIO_PORT GPIOA
#define LED2_GPIO_CLK  RCU_GPIOA

#define LED3_PIN       GPIO_PIN_2
#define LED3_GPIO_PORT GPIOA
#define LED3_GPIO_CLK  RCU_GPIOA

#define LED4_PIN       GPIO_PIN_1
#define LED4_GPIO_PORT GPIOE
#define LED4_GPIO_CLK  RCU_GPIOE

/* === Private data type declarations ========================================================== */

typedef enum {
    LED1 = 0,
    LED2 = 1,
    LED3 = 2,
    LED4 = 3,
} led_typedef_enum;

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/*!
    \brief      delay a time in milliseconds
    \param[in]  count: count in milliseconds
    \param[out] none
    \retval     none
*/
void delay_1ms(uint32_t count);

/*!
    \brief      configure led GPIO
    \param[in]  lednum: specify the led to be configured
      \arg        LED1
      \arg        LED2
      \arg        LED3
      \arg        LED4
    \param[out] none
    \retval     none
*/
void gd_eval_led_init(led_typedef_enum lednum);

/*!
    \brief      turn on selected led
    \param[in]  lednum: specify the led to be turned on
      \arg        LED1
      \arg        LED2
      \arg        LED3
      \arg        LED4
    \param[out] none
    \retval     none
*/
void gd_eval_led_off(led_typedef_enum lednum);

/*!
    \brief      turn off selected led
    \param[in]  lednum: specify the led to be turned off
      \arg        LED1
      \arg        LED2
      \arg        LED3
      \arg        LED4
    \param[out] none
    \retval     none
*/
void gd_eval_led_on(led_typedef_enum lednum);

/* === Public variable definitions ============================================================= */

static uint32_t GPIO_PORT[LEDn] = {
    LED1_GPIO_PORT,
    LED2_GPIO_PORT,
    LED3_GPIO_PORT,
    LED4_GPIO_PORT,
};

static uint32_t GPIO_PIN[LEDn] = {
    LED1_PIN,
    LED2_PIN,
    LED3_PIN,
    LED4_PIN,
};

static rcu_periph_enum GPIO_CLK[LEDn] = {
    LED1_GPIO_CLK,
    LED2_GPIO_CLK,
    LED3_GPIO_CLK,
    LED4_GPIO_CLK,
};

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

void delay_1ms(uint32_t count) {
    volatile uint64_t start_mtime, delta_mtime;

    volatile uint64_t tmp = get_timer_value();
    do {
        start_mtime = get_timer_value();
    } while (start_mtime == tmp);

    uint64_t delay_ticks = SystemCoreClock / 4; // 1 second
    delay_ticks = delay_ticks * count / 1000;

    do {
        delta_mtime = get_timer_value() - start_mtime;
    } while (delta_mtime < delay_ticks);
}

void gd_eval_led_init(led_typedef_enum lednum) {
    /* enable the led clock */
    rcu_periph_clock_enable(GPIO_CLK[lednum]);
    /* configure led GPIO port */
    gpio_init(GPIO_PORT[lednum], GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN[lednum]);

    GPIO_BOP(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}

void gd_eval_led_off(led_typedef_enum lednum) {
    GPIO_BOP(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}

void gd_eval_led_on(led_typedef_enum lednum) {
    GPIO_BC(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}
/* === Public function implementation ========================================================== */

int main(void) {

    BoardSetup();

    gd_eval_led_init(LED1);
    gd_eval_led_init(LED2);
    gd_eval_led_init(LED3);

    while (1) {
        /* turn on led1, turn off led4 */
        gd_eval_led_on(LED1);
        gd_eval_led_off(LED3);
        delay_1ms(500);
        /* turn on led2, turn off led1 */
        gd_eval_led_on(LED2);
        gd_eval_led_off(LED1);
        delay_1ms(500);
        /* turn on led3, turn off led2 */
        gd_eval_led_on(LED3);
        gd_eval_led_off(LED2);
        delay_1ms(500);
    }
    return 0;
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
