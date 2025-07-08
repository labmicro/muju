/* Copyright 2016, Laboratorio de Microprocesadores
 * Facultad de Ciencias Exactas y Tecnología
 * Universidad Nacional de Tucuman
 * http://www.microprocesadores.unt.edu.ar/
 * Copyright 2016, Esteban Volentini <evolentini@gmail.com>
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

/** \brief Manejo de pantallas alfanumericas
 **
 ** Manejo de pantallas alfanumericas de texto basadas en el controlador HD44780. La libreria
 ** soporta el manejo del display con 4 u 8 lineas de datos y sin la linea READ.
 **
 ** \addtogroup lcd Pantalla LCD
 ** \brief Manejo de pantallas LCD alfanumericas
 ** @{ */

/* === Inclusiones de cabeceras ================================================================ */
#include "display.h"
#define DELAY_TW  1
#define DELAY_CMD 5
/* === Definicion y Macros ===================================================================== */
//! Macro para reemplazar a la funcion de delay
// #define usDelay(value)

//! Macro para reemplazar a la funcion de delay
#define msDelay(value)

/* === Declaraciones de tipos de datos internos ================================================ */

/* === Declaraciones de funciones internas ===================================================== */

/* === Definiciones de variables externas ====================================================== */

/* === Definiciones de funciones internas =====================================================- */
void delay(int value) {
    int index;
    for (index = 1; index < value; index++)
        ;
}

void usDelay(int value) {
    int index;
    for (index = 1; index < value; index++) {
        delay(1000);
    }
}

/* === Definiciones de funciones externas ====================================================== */
void lcdWriteData(lcd_register_t destination, uint8_t data) {

    lcdRegisterSelect(destination);
    lcdWriteEnable(1);

#if (LCD_DATA_BITS == 4)
    lcdWriteDataBits(data & 0xF0);

    delay(DELAY_TW);
    lcdWriteEnable(0);
    delay(DELAY_TW);

    lcdWriteEnable(1);
    lcdWriteDataBits(data << 4);
#else
    lcdWriteDataBits(data);
#endif
    delay(DELAY_TW);
    lcdWriteEnable(0);
    delay(DELAY_TW);
    /*
    if (destination == LCD_CMD_REG) usDelay(1);
    */
    usDelay(DELAY_CMD);
}

void lcdInit(void) {

    // #if (LCD_DATA_BITS == 4)
    // lcdRW = 0;
    // lcdRS = 0;

    // lcdDataPortDir |= lcdDataMask;      // Configuro los pines de Salida

    // lcdDataPort &= lcdPortMask;         // Pongo a cero los bit de datos
    // lcdDataPort |= (0x20 >> (4 - lcdDataPins));
    lcdRegisterSelect(LCD_CMD_REG);
    lcdWriteEnable(1);
    lcdWriteDataBits(0x20);
    delay(DELAY_TW);
    lcdWriteEnable(0);
    delay(DELAY_TW);

    usDelay(DELAY_CMD);

    lcdWriteData(LCD_CMD_REG, 0x22); // 4 Bits de Datos, 2 Lineas, Caracteres de 5x7

    lcdWriteData(LCD_CMD_REG, 0x28); // 4 Bits de Datos, 2 Lineas, Caracteres de 5x7

    /*
       lcdWriteData(LCD_CMD_REG, 0x28);     // 4 Bits de Datos, 2 Lineas, Caracteres de 5x7
    #else
       lcdWriteData(LCD_CMD_REG, 0x38);     // 8 Bits de Datos, 2 Lineas, Caracteres de 5x7
    #endif
    */
    lcdWriteData(LCD_CMD_REG, 0x0C); // Mostrar Display, Ocultar Cursor, Sin Intermitente
    lcdWriteData(LCD_CMD_REG, 0x06); // Incrementar Direccion, Desplazar Cursor
    lcdClear();
    lcdWriteData(LCD_DATA_REG, 'A');
}

void lcdAtPos(uint8_t row, uint8_t col) {
    const static uint8_t firstCol[4] = {0x80, 0xC0, 0x94, 0xD4};
    lcdWriteData(LCD_CMD_REG, firstCol[row] + col);
    usDelay(2);
}

void lcdClear(void) {
    // Borrar Pantalla
    lcdWriteData(LCD_CMD_REG, 0x01);
    usDelay(500);
}

void lcdWriteString(char * text) {
    while (*text != 0) {
        lcdWriteData(LCD_DATA_REG, *text);
        text++;
    }
}
/* === Ciere de documentacion ================================================================== */

/** @} Final de la definición del modulo para doxygen */
