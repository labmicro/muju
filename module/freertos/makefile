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

# Variable with module root foder
FOLDER := external/freertos

RTOS := FREERTOS

# Variable with module name
$(eval NAME = $(call uc,$(subst /,_,$(FOLDER))))

ifeq ($(BOARD),posix)
    PORT := $(FOLDER)/portable/ThirdParty/GCC/Posix $(FOLDER)/portable/ThirdParty/GCC/Posix/utils
    $(NAME)_OBJ += $(OBJ_DIR)/$(FOLDER)/portable/MemMang/heap_3.o
else
    PORT = $(FOLDER)/portable/GCC/$(call uc,$(subst cortex-,arm_c,$(CPU)))
    $(NAME)_OBJ += $(OBJ_DIR)/$(FOLDER)/portable/MemMang/heap_4.o
endif

# Variable with the list of folders containing header files for the module
$(NAME)_INC := $(FOLDER)/include $(PORT) $(PROJECT_INC) boards/$(BOARD)/inc

# Variable with the list of folders containing source files for the module
$(NAME)_SRC := $(FOLDER) $(PORT)

$(eval $(call c_compiler_rule,$(FOLDER)/portable/MemMang,$(NAME)_INC))
