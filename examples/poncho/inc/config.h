/* Copyright 2016, Laboratorio de Microprocesadores
 * Facultad de Ciencias Exactas y Tecnología
 * Universidad Nacional de Tucuman
 * http://www.microprocesadores.unt.edu.ar/
 * Copyright 2016, Esteban Volentini <evolentini@gmail.com>
 * Copyright 2016, Matias Schida
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

#ifndef CONFIG_H
#define CONFIG_H

/* === Inclusiones de archivos externos ======================================================== */
#include "stdint.h"
#include "chip.h"

/* === Cabecera C++ ============================================================================ */
#ifdef __cplusplus
extern "C" {
#endif

/* === Definicion y Macros ===================================================================== */

/** Señales de Control Display 7 Segmentos **/
#define D7_1              LPC_GPIO_T->B[0][0]
#define D7_2              LPC_GPIO_T->B[0][1]
#define D7_3              LPC_GPIO_T->B[0][2]
#define D7_4              LPC_GPIO_T->B[0][3]
#define D7_A              LPC_GPIO_T->B[2][0]
#define D7_B              LPC_GPIO_T->B[2][1]
#define D7_C              LPC_GPIO_T->B[2][2]
#define D7_D              LPC_GPIO_T->B[2][3]
#define D7_E              LPC_GPIO_T->B[2][4]
#define D7_F              LPC_GPIO_T->B[2][5]
#define D7_G              LPC_GPIO_T->B[2][6]
#define D7_P              LPC_GPIO_T->B[5][16]

#define Write_D7_1(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, 0, (value)))
#define Write_D7_2(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, 1, (value)))
#define Write_D7_3(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, 2, (value)))
#define Write_D7_4(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 0, 3, (value)))
#define Write_D7_A(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 2, 0, (value)))
#define Write_D7_B(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 2, 1, (value)))
#define Write_D7_C(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 2, 2, (value)))
#define Write_D7_D(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 2, 3, (value)))
#define Write_D7_E(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 2, 4, (value)))
#define Write_D7_F(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 2, 5, (value)))
#define Write_D7_G(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 2, 6, (value)))
#define Write_D7_P(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 16,(value))

/** Señales de control Display LCD**/
#define LCD_0   LPC_GPIO_T->B[3][4]
#define LCD_1   LPC_GPIO_T->B[0][5]
#define LCD_2   LPC_GPIO_T->B[3][6]
#define LCD_3   LPC_GPIO_T->B[0][7]
#define LCD_RS  LPC_GPIO_T->B[3][3]
#define LCD_E   LPC_GPIO_T->B[3][8]
#define LCD_BAK LPC_GPIO_T->B[3][13]
#define Write_LCD_0(value)(Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 16,(value))
#define Write_LCD_1(value)(Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 16,(value))
#define Write_LCD_2(value)(Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 16,(value))
#define Write_LCD_3(value)(Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 16,(value))
#define Write_LCD_RS(value)(Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 16,(value))
#define Write_LCD_E(value)(Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 16,(value))
#define Write_LCD_BAK(value)(Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 16,(value))

/** Señales de Control Buzzer **/
#define BUZZER LPC_GPIO_T->B[3][14]
#define Write_BUZZER(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 16,(value))

/** Señales de Control RS-232 **/
#define RS232_TX LPC_GPIO_T->B[5][3]
#define RS232_RX LPC_GPIO_T->B[5][4]
#define Write_RS232_TX(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 16,(value))
#define Write_RS232_R(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 16,(value))

/** Señales de Control Teclas **/
#define BACEPF LPC_GPIO_T->B[5][8]
#define BCANCF LPC_GPIO_T->B[5][9]
#define F1F    LPC_GPIO_T->B[5][12]
#define F2F    LPC_GPIO_T->B[5][13]
#define F3F    LPC_GPIO_T->B[5][14]
#define F4F    LPC_GPIO_T->B[5][15]
#define Write_BACEPF(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 16,(value))
#define Write_BCANCF(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 16,(value))
#define Write_F1F(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 16,(value))
#define Write_F2F(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 16,(value))
#define Write_F3F(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 16,(value))
#define Write_F4F(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 16,(value))

/** Señales de Control Led RGB **/
#define LED5R LPC_GPIO_T->B[0][0]
#define LED5G LPC_GPIO_T->B[0][0]
#define LED5B LPC_GPIO_T->B[0][0]
#define Write_LED5R(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 16,(value))
#define Write_LED5G(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 16,(value))
#define Write_LED5B(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 16,(value))

/** Señales de Control de Teclado Numérico **/
#define F_EN LPC_GPIO_T->B[3][15]
#define C1   LPC_GPIO_T->B[0][12]
#define C2   LPC_GPIO_T->B[0][13]
#define C3   LPC_GPIO_T->B[0][15]
#define Write_F_EN(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 16,(value))
#define Write_C1(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 16,(value))
#define Write_C2(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 16,(value))
#define Write_C3(value) (Chip_GPIO_SetPinState(LPC_GPIO_PORT, 5, 16,(value))

/*  Configura la liberia de display en modo 4 bits */
#define LCD_DATA_BITS            4

#define lcdWriteEnable(valor)    Chip_GPIO_SetPinState(LPC_GPIO_PORT, 2, 8, valor)
#define lcdRegisterSelect(valor) Chip_GPIO_SetPinState(LPC_GPIO_PORT, 3, 3, valor)
#define lcdWriteDataBits(valor)                                                                    \
    Chip_GPIO_ClearValue(LPC_GPIO_PORT, 3, 0xF0);                                                  \
    Chip_GPIO_SetValue(LPC_GPIO_PORT, 3, valor & 0xF0);

/* === Ciere de documentacion ================================================================== */
#ifdef __cplusplus
}
#endif

/** @} Final de la definición del modulo para doxygen */

#endif /* CONFIG_H */
