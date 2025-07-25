##################################################################################################
# Copyright (c) 2022-2024, Laboratorio de Microprocesadores
# Facultad de Ciencias Exactas y Tecnología, Universidad Nacional de Tucumán
# https://www.microprocesadores.unt.edu.ar/
#
# Copyright (c) 2022-2024, Esteban Volentini <evolentini@herrera.unt.edu.ar>
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

CPU = nuclei-n200

# Variable with RV core module root foder
RV_CORE := external/base/arch/rv32/core

# Variable with SOC drivers module root foder
CPU_FOLDER := external/base/cpu/$(CPU)

# Variable with SOC drivers module root foder
SOC_FOLDER := external/base/soc/$(SOC)

# Variable with the list of folders containing source files for device support
DEVICE_SRC :=  $(RV_CORE)/src $(SOC_FOLDER)/device/src

# Variable with the list of folders containing header files for statup device
$(if $(findstring $(DEVICE_SRC),$(PROJECT_SRC)),,$(eval PROJECT_SRC += $(DEVICE_SRC)))

# Variable with module name
$(eval NAME = $(call module_name,board/$(BOARD)))

# Folder with device header to board module headers
$(eval $(NAME)_INC += $(RV_CORE)/inc $(CPU_FOLDER)/inc $(SOC_FOLDER)/device/inc)

# Folder with architeture source code to board module
$(eval $(NAME)_SRC += $(CPU_FOLDER)/src)

# Variable with the list of folders containing header and sourcefiles for the module
$(if $(findstring Y,$(call uc,$(USE_DRIVERS))), \
$(eval $(NAME)_INC += $(SOC_FOLDER)/drivers/inc) \
$(eval $(NAME)_SRC += $(SOC_FOLDER)/drivers/src) \
)

DAP ?= ftdi/um232h

# Command flags for gdb server
GDB_SERVER_FLAGS += $(if $(USB_LOCATION), -c "adapter usb location $(USB_LOCATION)")
GDB_SERVER_FLAGS += -f interface/$(DAP).cfg -f $(MUJU)/$(SOC_FOLDER)/openocd/gd32vf103.cfg

# Command flags for download target
FLASH_WRITER_FLAGS += $(if $(USB_LOCATION), -c "adapter usb location $(USB_LOCATION)")
FLASH_WRITER_FLAGS += -f interface/$(DAP).cfg -f $(MUJU)/$(SOC_FOLDER)/openocd/gd32vf103.cfg
