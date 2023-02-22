##################################################################################################
# Copyright (c) 2022-2023, Laboratorio de Microprocesadores
# Facultad de Ciencias Exactas y Tecnología, Universidad Nacional de Tucumán
# https://www.microprocesadores.unt.edu.ar/
#
# Copyright (c) 2022-2023, Esteban Volentini <evolentini@herrera.unt.edu.ar>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
# associated documentation files (the "Software"), to deal in the Software without restriction,
# including without limitation the rights to use, copy, modify, merge, publish, distribute,
# sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all copies or substantial
# portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
# NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
# OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
# SPDX-License-Identifier: MIT
##################################################################################################

SOC = stm32f1xx

DEFINES += STM32F103xB

LINKSCRIPT = external/base/mcu/$(MCU)/linker/stm32f103c8tx_flash.ld

# Command flags for gdb server
GDB_SERVER_FLAGS += $(if $(USB_LOCATION), -c "adapter usb location $(USB_LOCATION)")
GDB_SERVER_FLAGS +=-f $(MUJU)/external/base/mcu/$(MCU)/openocd/openocd.cfg

# Command flags for download target
FLASH_WRITER_FLAGS += $(if $(USB_LOCATION), -c "adapter usb location $(USB_LOCATION)")
FLASH_WRITER_FLAGS += -f $(MUJU)/external/base/mcu/$(MCU)/openocd/openocd.cfg

# Flash base address for OpenOCD download target
FLASH_BASE_ADDRESS := 0x08000000
