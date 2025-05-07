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

#ifndef DISPLAY_H
#define DISPLAY_H

/** \brief Manejo de pantallas alfanumericas
 **
 ** Manejo de pantallas alfanumericas de texto basadas en el controlador HD44780. La libreria
 ** soporta el manejo del display con 4 u 8 lineas de datos y sin la linea READ.
 **
 ** \addtogroup lcd Pantalla LCD
 ** \brief Manejo de pantallas LCD alfanumericas
 ** @{ */

/* === Inclusiones de archivos externos ======================================================== */
#include "stdint.h"
#include "config.h"

/* === Cabecera C++ ============================================================================ */
#ifdef __cplusplus
extern "C" {
#endif

/* === Definicion y Macros ===================================================================== */
//! Configuracion del modo de trabajo en 4 u 8 bits
#ifndef LCD_DATA_BITS
#define LCD_DATA_BITS 8
#else
#if (LCD_DATA_BITS != 4) && (LCD_DATA_BITS != 8)
#error Only 4 or 8 are valid values to LCD_DATA_BITS macro
#endif
#endif

/* == Declaraciones de tipos de datos ========================================================== */

//! Registros internos del control de la pantalla lcd
typedef enum lcd_register_e {
    LCD_CMD_REG = 0,  //!< Registro de comandos (Linea RS igual a 0)
    LCD_DATA_REG = 1, //!< Registro de datos (Linea RS igual a 1)
} lcd_register_t;

/* === Declaraciones de variables externas ===================================================== */

/* === Declaraciones de funciones externas ===================================================== */
/*!
 * @brief Escribe un byte en el registro de comandos o de datos del LCD
 * @param[in]  command   Indica si se escribe en el registro de comandos o el de datos
 * @param[in]  data      Dato a escribir en el registro
 */
void lcdWriteData(lcd_register_t command, uint8_t data);

/*!
 * Inicializa el puerto y el display enviando los comandos adecuados
 */
void lcdInit(void);

/*!
 * @brief Lleva el cursor a una posicion especifica de la pantalla
 * @param[in]  row      Numero de fila en la que se fija el cursor
 * @param[in]  col      Numero de columna en la que se fija el cursor
 */
void lcdAtPos(uint8_t row, uint8_t col);

//! Borra la pantalla y lleva el cursor la posicion inicial
void lcdClear(void);

/*!
 * @brief Escribe una cadena de texto a partir de la posicion actual del cursor
 * @param[in]  text     Cadena de texto a escribir terminada con caracter null
 */
void lcdWriteString(char * text);

/* === Ciere de documentacion ================================================================== */
#ifdef __cplusplus
}
#endif

/** @} Final de la definición del modulo para doxygen */

#endif /* DISPLAY_H */
