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

CPU = cortex-m4f

# Flash commandfor OpenOCD download target
FLASH_WRITER_COMMANDS = -c "init" -c "halt 0" -c "flash write_image erase $(BIN_TARGET) $(FLASH_BASE_ADDRESS) bin" -c "reset run" -c "shutdown"

# Variable with LPC Open drivers module root foder
LPC_OPEN := external/base/soc/$(SOC)/lpc_open

# Variable with ARM CMSIS core module root foder
CMSIS_CORE := external/base/arch/arm/cmsis_core

# Variable with the list of folders containing header files for LPC Open drivers module
LPC_OPEN_INC := $(CMSIS_CORE) $(LPC_OPEN)/inc $(LPC_OPEN)/inc/config_43xx

# Variable with the list of folders containing header files for LPC Open drivers module
LPC_OPEN_SRC := $(LPC_OPEN)/src

# Variable with module name
$(eval NAME = $(call module_name,board/$(BOARD)))

# Variable with the list of folders containing header and sourcefiles for the module
$(if $(findstring Y,$(call uc,$(USE_DRIVERS))), \
$(eval $(NAME)_INC += $(LPC_OPEN_INC)) \
$(eval $(NAME)_SRC += $(LPC_OPEN_SRC)) \
)

STARTUP := external/base/soc/$(SOC)/startup
$(if $(findstring $(STARTUP),$(PROJECT_SRC)),,$(eval PROJECT_SRC += $(STARTUP)))
