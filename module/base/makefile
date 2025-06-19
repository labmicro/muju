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

MUJU := $(abspath $(dir $(lastword $(MAKEFILE_LIST)))../..)
include $(MUJU)/external/gmsl/gmsl

##################################################################################################
# Defintion of project name based on project paths if it was not defined in
# project makefile, used to define binary file and default target
ifneq ($(PROJECT), )
    -include $(PROJECT)/makefile
    PROJECT_NAME ?= $(lastword $(subst /, , $(PROJECT)))
    PROJECT_DIR = $(abspath $(PROJECT))
else
    PROJECT = .
    PROJECT_NAME ?= $(lastword $(subst /, , $(CURDIR)))
    PROJECT_DIR = $(PROJECT)
endif

##################################################################################################
# Function to generate the full path of directory
define full_path
$(strip \
    $(if $(wildcard $(abspath $1)), $(abspath $1), \
        $(if $(wildcard $(PROJECT_DIR)/$1),$(PROJECT_DIR)/$1,$(MUJU)/$1) \
    )
)
endef

##################################################################################################
# Function to generate varaible prefix name for a module
define module_name
$(strip \
    $(if $2,$2,$(call uc,$(subst /,_,$1)))
)
endef

##################################################################################################
# Function to generate the short path of directory
define short_path
$(strip \
    $(subst $(abspath $(MUJU))/,,$(subst $(abspath $(PROJECT_DIR))/,,$(abspath $1)))
)
endef

##################################################################################################
# Function to display info messages when dynamic rules are generated
define show_message
$(if $(findstring Y,$(call uc,$(VERBOSE))),$(info $1))
endef

##################################################################################################
# Function to display info messages when rules are executed
define show_action
$(strip \
    $(if $(findstring Y,$(call uc,$(VERBOSE))),\
        @echo $(DIVISION_LINE), \
        @echo $1 \
    )
)
endef

##################################################################################################
# Variable to separate every comand when execution rules are show
DIVISION_LINE = ===============================================================================

##################################################################################################
# Variable to show or hide command lines when rules are executed
ifeq ($(call uc,$(VERBOSE)),Y)
    QUIET =
else
    QUIET = @
endif

##################################################################################################
# Function to generate the compilation parameters with the list of include paths
define include_directories
$(strip \
    $(foreach path,$(sort $1 $(PROJECT_INC)),-I $(call full_path,$(path)))
)
endef

##################################################################################################
# Function to generate the compilation parameters with the list of include paths
define defines_list
$(strip \
    $(foreach define,$(DEFINES),-D $(define))
)
endef

##################################################################################################
# Function to generate defines from make variable
define convert_defines
$(strip \
    $(foreach word,$1,$(subst -,_,$(call uc,$(word))))
)
endef

##################################################################################################
# Function to obtain the last directory of a path
define lastdir
$(strip \
    $(strip $(lastword $(subst /, ,$1)))
)
endef

##################################################################################################
# Function to generate the list of object files from a path list
define objects_list
$(strip \
    $(foreach path,$1,
        $(eval SOURCE_DIR = $(call full_path,$(path))) \
        $(eval OBJECT_DIR = $(OBJ_DIR)/$(call short_path,$(path))) \
        $(patsubst $(SOURCE_DIR)/%.$2,$(OBJECT_DIR)/%.o,$(wildcard $(SOURCE_DIR)/*.$2)) \
    )
)
endef

##################################################################################################
# Dynamic rule to compile single folder with c source files
define c_compiler_rule
    $(call show_message,Definiendo regla de compilacion para $1/*.c en $3)
$3/%.o: $(call full_path,$1)/%.c
	$$(call show_action,Compiling $$(call short_path,$$<))
	-@mkdir -p $$(@D)
	$$(QUIET) $$(CC) $$(strip $$(CFLAGS) $$(call defines_list) $$(call include_directories,$2)) -MMD -c $$< -o $$@
endef

##################################################################################################
# Dynamic rule to compile single folder with s source files
define assembler_rule
    $(call show_message,Definiendo regla de compilacion para $1/*.s en $3)
$3/%.o: $(call full_path,$1)/%.s
	$$(call show_action,Compiling $$(call short_path,$$<))
	-@mkdir -p $$(@D)
	$$(QUIET) $$(CC) $$(strip $$(AFLAGS) $$(call defines_list) $$(call include_directories,$2)) -MMD -c $$< -o $$@
endef

##################################################################################################
# Dynamic rule to link static library file from module with source code
define library_link_rule
    $(call show_message,Definiendo regla de enlazar $(LIB_DIR)/$1.a)
PROJECT_LIB += $(LIB_DIR)/$1.a
$(LIB_DIR)/$1.a: $$($2_OBJ)
	$$(call show_action,Building $$(call short_path,$$<))
	-@mkdir -p $$(@D)
	$$(QUIET) $$(AR) rcs $$@ $$^
endef

##################################################################################################
# Procedure to create dynamic rules for a list of folders with source files
define define_compilation_rules
    $(foreach path, $($1_SRC),$(eval $(call c_compiler_rule,$(path),$($1_INC),$(OBJ_DIR)/$(call short_path,$(path)))))
    $(foreach path, $($1_SRC),$(eval $(call assembler_rule,$(path),$($1_INC),$(OBJ_DIR)/$(call short_path,$(path)))))
endef

##################################################################################################
# Function to analize a path and include the module makefile if it exists
define analize_path
    $(eval path = $(call full_path,$1)) \
    $(call show_message,$(DIVISION_LINE)) \
    $(call show_message,Analizando la carpeta $(path)) \
    $(if $(wildcard $(path)/makefile), \
        $(call show_message,Incluyendo el makefile de la carpeta $(path)) \
        $(eval include $(path)/makefile) \
    , \
        $(if $(wildcard $(path)/inc),$(eval $2_INC += $(path)/inc)) \
        $(if $(wildcard $(path)/src), \
            $(call show_message,Usando el codigo fuente $(path)/src) \
            $(eval $2_SRC += $(path)/src) \
            $(foreach path,$(wildcard $(path)/*),$(eval $(call analize_path,$(path),$2))) \
        ) \
    )
endef

##################################################################################################
# Procedure to create dynamic rules to build a static library from module with source code
define define_library_rules
    $(eval NAME = $(call module_name,$1,$2))
    $(if $($(NAME)_SRC),,$(eval $(call analize_path,$1,$(NAME))))
    $(if $($(NAME)_SRC), \
        $(eval $(NAME)_OBJ += $$(call objects_list,$$($(NAME)_SRC),c,$1)) \
        $(eval PROJECT_INC += $$($(NAME)_INC)) \
        $(eval $(call define_compilation_rules,$(NAME))) \
        $(eval $(call library_link_rule,$1,$(NAME))) \
        $(eval -include $(patsubst %.o,%.d,$($(NAME)_OBJ))) \
    )
endef

##################################################################################################
# Definition of directories variables
# out dir
# BUILD_DIR = $(PROJECT_DIR)/build
BUILD_DIR ?= build
# object dir
OBJ_DIR = $(BUILD_DIR)/obj
# lib dir
LIB_DIR = $(BUILD_DIR)/lib
# bin dir
BIN_DIR = $(BUILD_DIR)/bin
# rtos gen dir
GEN_DIR = $(BUILD_DIR)/gen
# etc dir (configuration dir)
ETC_DIR = $(BUILD_DIR)/etc

##################################################################################################
#
ifneq ($(wildcard $(PROJECT_DIR)/src), )
    PROJECT_SRC ?= $(PROJECT_DIR)/src
else
    PROJECT_SRC ?= $(PROJECT_DIR)
endif

ifneq ($(wildcard $(PROJECT_DIR)/inc), )
    PROJECT_INC ?= $(PROJECT_DIR)/inc
else
    PROJECT_INC ?= $(PROJECT_DIR)
endif

##################################################################################################
#

include $(call full_path,board/makefile)
include $(call full_path,module/base/mcu/makefile)
include $(call full_path,module/base/soc/makefile)
include $(call full_path,module/base/cpu/makefile)
include $(call full_path,module/base/arch/makefile)

MODULES += board/$(BOARD)
$(foreach module,$(MODULES),$(eval $(call define_library_rules,$(module))))

##################################################################################################
#
RTOS ?= BAREMETAL

export BOARD
export CPU
export SOC
export MCU
export RTOS

DEFINES += BOARD=$(BOARD)  MCU=$(MCU) SOC=$(SOC) CPU=$(CPU) ARCH=$(ARCH) RTOS=$(RTOS)
DEFINES += $(call convert_defines, $(BOARD) $(SOC) $(MCU) $(CPU) $(ARCH) $(RTOS))

##################################################################################################
#
TARGET_NAME ?= $(BIN_DIR)/$(PROJECT_NAME)
TARGET_ELF = $(TARGET_NAME).$(LD_EXTENSION)

##################################################################################################
#
PROJECT_OBJ += $(call objects_list,$(PROJECT_SRC),c)
$(foreach path,$(PROJECT_SRC),$(eval $(call c_compiler_rule,$(path),$($1_INC),$(OBJ_DIR)/$(call short_path,$(path)))))

PROJECT_OBJ += $(call objects_list,$(PROJECT_SRC),s)
$(foreach path,$(PROJECT_SRC),$(eval $(call assembler_rule,$(path),$($1_INC),$(OBJ_DIR)/$(call short_path,$(path)))))

# Load project compile dependencies if present (must be placed after PROJECT_OBJ is completely defined)
-include $(patsubst %.o,%.d,$(PROJECT_OBJ))

##################################################################################################
$(TARGET_ELF): $(PROJECT_LIB) $(PROJECT_OBJ)
	$(call show_action,Linking $(call short_path,$(TARGET_ELF)))
	-@mkdir -p $(BIN_DIR)
	$(QUIET) $(CC) $(strip $(LFLAGS) $(PROJECT_OBJ) $(LFLAGS_BEGIN_LIBS) $(PROJECT_LIB) $(LFLAGS_END_LIBS)) -o $(TARGET_ELF)
	-@cp -f $(TARGET_ELF) $(BIN_DIR)/project.$(LD_EXTENSION)
	$(QUIET) $(OD) $(TARGET_ELF) -xS > $(TARGET_NAME).s

.DEFAULT_GOAL := all

all: $(TARGET_ELF) $(POST_BUILD_TARGET)

##################################################################################################
#
clean:
	-@rm -r $(BUILD_DIR)

gdbserver:
ifeq ($(GDB_SERVER),)
	$(error Flash write operation is not available for the board $(BOARD))
else
	$(QUIET) $(GDB_SERVER) $(GDB_SERVER_FLAGS)
endif

download: $(TARGET_ELF)
ifeq ($(FLASH_WRITER),)
	$(error Flash write operation is not available for the board $(BOARD))
else
	$(FLASH_WRITER) $(FLASH_WRITER_FLAGS) $(FLASH_WRITER_COMMANDS)
endif

##################################################################################################
#
CPP_SUPPRESS ?= unmatchedSuppression missingInclude missingIncludeSystem unusedFunction
CPP_FLAGS ?= --force --enable=all --inconclusive --std=c89 --xml --xml-version=2
CPP_FLAGS += $(foreach SUPRESS,$(CPP_SUPPRESS),--suppress=$(SUPRESS)) $(call include_directories)

ifeq ($(call uc,$(VERBOSE)),Y)
    CPP_OUTPUT = 2> $(BUILD_DIR)/artifacts/cppcheck.xml
else
    CPP_OUTPUT = 1> /dev/null 2> $(BUILD_DIR)/artifacts/cppcheck.xml
endif

check:
	$(call show_action,Performing static analize with CppCheck)
	-@mkdir -p $(BUILD_DIR)/artifacts
	$(QUIET) cppcheck $(CPP_FLAGS) $(PROJECT_SRC) $(CPP_OUTPUT)

##################################################################################################
#
info:
	@echo $(DIVISION_LINE)
	@echo Nombre del proyecto: $(PROJECT_NAME)
	@echo Ruta definida para el proyecto: $(PROJECT)
	@echo Ruta absoluta del Proyecto: $(PROJECT_DIR)
	@echo Binario final: $(TARGET_ELF)
	@echo -------------------------------------------------------------------------------
	@echo Modulos: $(MODULES)
	@echo Board: $(BOARD), Arch: $(ARCH), Cpu: $(CPU), Soc: $(SOC), Mcu: $(MCU)
	@echo -------------------------------------------------------------------------------
	@echo Fuentes: $(PROJECT_SRC)
	@echo Cabeceras: $(PROJECT_INC)
	@echo Objetos: $(PROJECT_OBJ)
	@echo -------------------------------------------------------------------------------
	@echo Definciones: $(DEFINES)

##################################################################################################
#
define NEWLINE


endef
COMMA := ,
EMPTY :=
SPACE := $(EMPTY) $(EMPTY)
TAB := $(SPACE)$(SPACE)$(SPACE)$(SPACE)
INDENT := $(COMMA)$(NEWLINE)$(TAB)$(TAB)$(TAB)$(TAB)

define json_list
$(subst $(SPACE),$(INDENT),$(strip $(foreach w,$1,"$w")))
endef

VSCODE_INCLUDES = $(strip $(foreach p,$(PROJECT_INC),$(subst $(abspath $(PROJECT_DIR)),$(PROJECT_DIR),$(call full_path,$(p)))))

define vscode_c_config
{
    "configurations": [
        {
            "name": "MUJU",
            "includePath": [$(call json_list,$(VSCODE_INCLUDES))],
            "defines": [$(call json_list,$(DEFINES))],
            "cStandard": "c99",
            "intelliSenseMode": "$${default}",
            "compilerPath":"$(subst \,\\,$(shell $(CC) -v 2>&1 | awk '/COLLECT_GCC=/ {sub(/[^=]+=/,"");print}'))"
        }
    ],
	"version": 4
}
endef

VSCODE_DIR=$(PROJECT_DIR)/.vscode
VSCODE_CFG=$(VSCODE_DIR)/c_cpp_properties.json


vscode: |$(VSCODE_DIR)
	@echo "Creating or replacing $(VSCODE_CFG)"
	@echo '$(subst $(NEWLINE),>>>>,$(subst ','\'',${vscode_c_config}))' | awk 'gsub(/>>>>/,"\n")' > $(VSCODE_CFG)

$(VSCODE_DIR):
	-@mkdir -p $(VSCODE_DIR)

CLANGD_CONFIG_FILE = $(PROJECT_DIR)/compile_flags.txt

CLANGD_CONFIG_CONTENT = $(patsubst %,-I%,$(VSCODE_INCLUDES)) $(patsubst %,-D%,$(DEFINES)) -Wall -Wextra -Wpedantic -std=c99

clangd:
	@echo "Creating or replacing $(CLANGD_CONFIG_FILE)"
	@echo $(CLANGD_CONFIG_CONTENT) | tr ' ' '\n' >$(CLANGD_CONFIG_FILE)
