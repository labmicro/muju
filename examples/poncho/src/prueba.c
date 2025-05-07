/* Copyright 2016, Laboratorio de Microprocesadores
 * Facultad de Ciencias Exactas y Tecnología
 * Universidad Nacional de Tucuman
 * http://www.microprocesadores.unt.edu.ar/
 * Copyright 2016, Esteban Volentini <evolentini@gmail.com>
 * Copyright 2016, Matias Giori <matias.giori@domotech.com.ar>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/** @brief Prueba de funcionamiento del poncho educativo
 **
 ** Programa de prueba para los ponchos educativos desarrollados para las placas
 ** EDU-CIAA por el Laboratorio de Microcontroladores de la Universidad Nacional
 ** de Tucumán.
 **
 ** @addtogroup test Pruebas de sistema
 ** @brief Prueba de funcionamiento del poncho educativo
 ** @{ */

/* === Inclusiones de cabeceras ================================================================ */
#if (lpc4337 == CPU)
#include "chip.h"
#elif (mk60fx512vlq15 == CPU)
#error Por el momento este programa solo puede ser compilado para la EDU-CIAA-NXP
#endif

#include "display.h"

/* === Definicion y Macros ===================================================================== */

#define SCU_MODE_SAL              (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS)
#define SCU_MODE_ENT              (SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN)

#define TECLA_SI                  (1 << 8)
#define TECLA_NO                  (1 << 9)
#define TECLA_F1                  (1 << 15)
#define TECLA_F2                  (1 << 14)
#define TECLA_F3                  (1 << 13)
#define TECLA_F4                  (1 << 12)

#define apagarSegmentos()         Chip_GPIO_ClearValue(LPC_GPIO_PORT, 2, 0x7F)
#define prenderSegmentos(mascara) Chip_GPIO_SetValue(LPC_GPIO_PORT, 2, (mascara)&0x7F)
#define apagarDigitos()           Chip_GPIO_ClearValue(LPC_GPIO_PORT, 0, 0x0F)
#define prenderDigito(digito)     Chip_GPIO_SetValue(LPC_GPIO_PORT, 0, (1 << (digito)) & 0x0F)
#define prenderPunto(valor)       Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 16, valor)

/* === Declaraciones de tipos de datos internos ================================================ */

/* === Declaraciones de funciones internas ===================================================== */

void configurarPuertos(void);

void configurarInterrupcion(void);

/* === Definiciones de variables internas ====================================================== */
const uint8_t digitos[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67};

uint8_t numero[4] = {0, 0, 0, 0};

/* === Definiciones de variables externas ====================================================== */

/* === Definiciones de funciones internas ====================================================== */
void configurarDigitos() {
    apagarDigitos();
    apagarSegmentos();
    prenderPunto(false);

    /* Pines de los digitos */
    Chip_SCU_PinMux(0, 0, SCU_MODE_SAL, SCU_MODE_FUNC0);
    Chip_SCU_PinMux(0, 1, SCU_MODE_SAL, SCU_MODE_FUNC0);
    Chip_SCU_PinMux(1, 15, SCU_MODE_SAL, SCU_MODE_FUNC0);
    Chip_SCU_PinMux(1, 17, SCU_MODE_SAL, SCU_MODE_FUNC0);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, 0, 0x0F, 1);

    /* Pines de los segmentos */
    Chip_SCU_PinMux(4, 0, SCU_MODE_SAL, SCU_MODE_FUNC0);
    Chip_SCU_PinMux(4, 1, SCU_MODE_SAL, SCU_MODE_FUNC0);
    Chip_SCU_PinMux(4, 2, SCU_MODE_SAL, SCU_MODE_FUNC0);
    Chip_SCU_PinMux(4, 3, SCU_MODE_SAL, SCU_MODE_FUNC0);
    Chip_SCU_PinMux(4, 4, SCU_MODE_SAL, SCU_MODE_FUNC0);
    Chip_SCU_PinMux(4, 5, SCU_MODE_SAL, SCU_MODE_FUNC0);
    Chip_SCU_PinMux(4, 6, SCU_MODE_SAL, SCU_MODE_FUNC0);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, 2, 0x7F, 1);

    /* Pin del punto */
    Chip_SCU_PinMux(6, 8, SCU_MODE_SAL, SCU_MODE_FUNC4);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, 5, 0x10000, 1);
}

void configurarLcd(void) {
    lcdWriteEnable(0);

    /* Pines de datos  y control */
    Chip_SCU_PinMux(6, 4, SCU_MODE_SAL, SCU_MODE_FUNC0);
    Chip_SCU_PinMux(6, 5, SCU_MODE_SAL, SCU_MODE_FUNC0);
    Chip_SCU_PinMux(6, 9, SCU_MODE_SAL, SCU_MODE_FUNC0);
    Chip_SCU_PinMux(6, 10, SCU_MODE_SAL, SCU_MODE_FUNC0);
    Chip_SCU_PinMux(6, 11, SCU_MODE_SAL, SCU_MODE_FUNC0);
    Chip_SCU_PinMux(6, 12, SCU_MODE_SAL, SCU_MODE_FUNC0);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, 2, 0x100, 1);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, 3, 0xF8, 1);

    lcdInit();
}

void configurarLeds(void) {
    /* Puerto Led RGB */
    Chip_SCU_PinMux(2, 0, SCU_MODE_SAL, SCU_MODE_FUNC4);
    Chip_SCU_PinMux(2, 1, SCU_MODE_SAL, SCU_MODE_FUNC4);
    Chip_SCU_PinMux(2, 2, SCU_MODE_SAL, SCU_MODE_FUNC4);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, 5, (1 << 0) | (1 << 1) | (1 << 2));
    Chip_GPIO_SetDir(LPC_GPIO_PORT, 5, (1 << 0) | (1 << 1) | (1 << 2), 1);

    /* Puerto Leds 1 a 3 */
    Chip_SCU_PinMux(2, 10, SCU_MODE_SAL, SCU_MODE_FUNC0);
    Chip_SCU_PinMux(2, 11, SCU_MODE_SAL, SCU_MODE_FUNC0);
    Chip_SCU_PinMux(2, 12, SCU_MODE_SAL, SCU_MODE_FUNC0);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, 0, (1 << 14));
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, 1, (1 << 11) | (1 << 12));
    Chip_GPIO_SetDir(LPC_GPIO_PORT, 0, (1 << 14), true);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, 1, (1 << 11) | (1 << 12), true);
}

void configurarTeclas(void) {

    /* Puerto Teclas 1 a 4 */
    Chip_SCU_PinMux(4, 8, SCU_MODE_ENT, SCU_MODE_FUNC4);
    Chip_SCU_PinMux(4, 9, SCU_MODE_ENT, SCU_MODE_FUNC4);
    Chip_SCU_PinMux(4, 10, SCU_MODE_ENT, SCU_MODE_FUNC4);
    Chip_SCU_PinMux(6, 7, SCU_MODE_ENT, SCU_MODE_FUNC4);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, 4, (1 << 8) | (1 << 9) | (1 << 10), false);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, 6, (1 << 7), false);

    /* Puerto Teclas Aceptar y Cancelar */
    Chip_SCU_PinMux(3, 1, SCU_MODE_ENT, SCU_MODE_FUNC4);
    Chip_SCU_PinMux(3, 2, SCU_MODE_ENT, SCU_MODE_FUNC4);
    Chip_GPIO_SetDir(LPC_GPIO_PORT, 3, (1 << 1) | (1 << 2), false);
}

void configurarRGB(void) {
    /* Puerto Leds RGB */
    Chip_SCU_PinMux(1, 3, SCU_MODE_SAL, SCU_MODE_FUNC1);
    Chip_SCU_PinMux(1, 4, SCU_MODE_SAL, SCU_MODE_FUNC1);
    Chip_SCU_PinMux(1, 5, SCU_MODE_SAL, SCU_MODE_FUNC1);

    Chip_SCTPWM_Init(LPC_SCT);
    Chip_SCTPWM_SetRate(LPC_SCT, 100000);
    Chip_SCTPWM_SetOutPin(LPC_SCT, 1, 8);
    Chip_SCTPWM_SetOutPin(LPC_SCT, 2, 9);
    Chip_SCTPWM_SetOutPin(LPC_SCT, 3, 10);
    Chip_SCTPWM_Start(LPC_SCT);
}

void configurarPuertos(void) {

    // Chip_GPIO_SetValue(LPC_GPIO_PORT, 2, 0x7F); //prende todos los led
    // Chip_GPIO_SetDir(LPC_GPIO_PORT, 2, 0x7F, 1);

    Chip_GPIO_SetValue(LPC_GPIO_PORT, 0, 0x1);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, 0, 0xF);
    Chip_GPIO_SetValue(LPC_GPIO_PORT, 0, 0x2);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, 0, 0xF);
    Chip_GPIO_SetValue(LPC_GPIO_PORT, 0, 0x4);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, 0, 0xF);
    Chip_GPIO_SetValue(LPC_GPIO_PORT, 0, 0x8);
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, 0, 0xF);

    /* todos los LED del display a 1 */
    /* multiplex a 0 */
    /* Chip_GPIO_SetDir(LPC_GPIO_PORT, port, mask, output); */
    // Chip_GPIO_SetDir(LPC_GPIO_PORT, 5, (1 << 0) | (1 << 1) | (1 << 2), 1);
}

void configurarInterrupcion(void) {
    asm volatile("cpsid i");

    /* Activate SysTick */
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / 10000);

    /* Update priority set by SysTick_Config */
    NVIC_SetPriority(SysTick_IRQn, (1 << __NVIC_PRIO_BITS) - 1);

    asm volatile("cpsie i");
}

void refrescarDigitos(void) {
    static int activo = 0;

    activo = ((activo + 1) & 0x03);
    apagarDigitos();
    apagarSegmentos();
    prenderSegmentos(digitos[numero[activo] & 0x0F]);
    prenderDigito(3 - activo);
}

int escanearTeclado(void) {
    int pulsadas;
    int actuales;
    static int anteriores = 0;

    actuales = Chip_GPIO_ReadValue(LPC_GPIO_PORT, 5);
    pulsadas = ((actuales ^ anteriores) & actuales);
    anteriores = actuales;

    return pulsadas;
}

/* === Definiciones de funciones externas ====================================================== */
void SysTick_Handler(void) {
    static int divisor = 0;

    divisor = (divisor + 1) % 10;
    if (divisor == 0) {
        refrescarDigitos();
    }
}

int main(void) {
    int pulsadas;

    configurarRGB();
    configurarLeds();
    configurarTeclas();
    configurarDigitos();
    configurarLcd();
    configurarInterrupcion();

    while (1) {
        pulsadas = escanearTeclado();
        if (pulsadas & TECLA_F1) {
            numero[0] = (numero[0] + 1) % 10;
        }
        if (pulsadas & TECLA_F2) {
            numero[1] = (numero[1] + 1) % 10;
        }
        if (pulsadas & TECLA_F3) {
            numero[2] = (numero[2] + 1) % 10;
        }
        if (pulsadas & TECLA_F4) {
            numero[3] = (numero[3] + 1) % 10;
        }
        if (pulsadas & TECLA_SI) {
            numero[0] = 9;
            numero[1] = 9;
            numero[2] = 9;
            numero[3] = 9;
        }
        if (pulsadas & TECLA_NO) {
            numero[0] = 0;
            numero[1] = 0;
            numero[2] = 0;
            numero[3] = 0;
        }
        Chip_SCTPWM_SetDutyCycle(LPC_SCT, 1,
                                 Chip_SCTPWM_PercentageToTicks(LPC_SCT, numero[0] * numero[1]));
        Chip_SCTPWM_SetDutyCycle(LPC_SCT, 2,
                                 Chip_SCTPWM_PercentageToTicks(LPC_SCT, numero[0] * numero[2]));
        Chip_SCTPWM_SetDutyCycle(LPC_SCT, 3,
                                 Chip_SCTPWM_PercentageToTicks(LPC_SCT, numero[0] * numero[3]));
    }
    return 0;
}
/* === Ciere de documentacion ================================================================== */

/** @} Final de la definición del modulo para doxygen */
