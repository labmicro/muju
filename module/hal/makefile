# Variable with module root foder
FOLDER := module/hal

# Variable with module name
$(eval NAME = $(call module_name,$(FOLDER)))

# Variable with the list of folders containing header files for the module
$(NAME)_INC := $(FOLDER)/inc $(FOLDER)/soc/$(SOC)/inc

# Variable with the list of folders containing source files for the module
$(NAME)_SRC := $(FOLDER)/src $(FOLDER)/soc/$(SOC)/src

PROJECT_INC += module/hal/inc module/hal/soc/$(SOC)/inc
