# CORE (needed to compile)

ifndef CC
$(warning C compiler not detected. Setting default compiler to GCC...)
	CC :=	gcc
endif

# CORE OPTIONAL (compiler flags)

ifndef BUILD_TYPE
	BUILD_TYPE := Debug
endif

ifndef CFLAGS
	ifeq ($(BUILD_STATIC), 1)
		LDFLAGS += -static
	endif

	ifeq ($(CC), tcc)
		CFLAGS := -std=c89
	else
		CFLAGS := --std=c89
	endif

	ifeq ($(BUILD_TYPE), Release)
		ifneq ($(CC), tcc)
			CFLAGS += -O2
		endif
	else ifeq ($(BUILD_TYPE), Debug)
		ifneq ($(CC), tcc)
			CFLAGS += -O0
		endif
		CFLAGS += -g3 -ggdb -Wall
	endif
endif

ifndef __STDC_VERSION__
	__STDC_VERSION__ := 199002L
endif

ifndef INSTALL_PREFIX
	INSTALL_PREFIX := ./build/usr/
endif

ESCAPE        := \033
GREEN         := $(ESCAPE)[32m
BOLD_GREEN    := $(ESCAPE)[1;32m
BLUE          := $(ESCAPE)[34m
BOLD_BLUE     := $(ESCAPE)[1;34m
RESET_COLOUR  := $(ESCAPE)[0m

PWD           := $(shell pwd | sed 's/ /\\ /g')
OBJ_DIR       := $(PWD)/.obj
SRC_DIR       := $(PWD)/src
BIN_DIR       := $(PWD)/bin
DIRS          := bin .obj
HEADERS       := -I./src/
LIBRARIES     :=

_TARGETS      := runit-service
_SOURCES      := $(shell find $(SRC_DIR) -name "*.c")
_SOURCES      := $(patsubst $(SRC_DIR)/%,%,$(_SOURCES))
_OBJECTS      := $(patsubst %.c,%.o,$(_SOURCES))

TARGETS       := $(addprefix $(BIN_DIR)/, $(_TARGETS))
SOURCES       := $(addprefix $(SRC_DIR)/, $(_SOURCES))
OBJECTS       := $(addprefix $(OBJ_DIR)/, $(_OBJECTS))

.PHONY: all

all: directories $(TARGETS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@printf "[CC] ""$(GREEN)""Building object '$<'""$(RESET_COLOUR)""\n"
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(TARGETS): $(OBJECTS)
	@printf "[LD] ""$(BOLD_GREEN)""Linking binary '$@'""$(RESET_COLOUR)""\n"
	@$(CC) $^ $(LIBRARIES) $(HEADERS) $(LDFLAGS) -o $@

directories: $(DIRS)

$(DIRS):
	@printf "[DIR] ""$(BLUE)""Directory ""$(BOLD_BLUE)""'$@'""$(RESET_COLOUR)$(BLUE)"" created""$(RESET_COLOUR).""\n"
	@mkdir -p $(PWD)/$@

install:
	@mkdir -p $(INSTALL_PREFIX)/bin/
	@mkdir -p $(INSTALL_PREFIX)/../etc/runit/sv/runit-journal/supervise
	@install -m 755 bin/runit-service $(INSTALL_PREFIX)/bin/
	@install -m 755 service/runit-journal/run $(INSTALL_PREFIX)/../etc/runit/sv/runit-journal/
	@chmod 700 $(INSTALL_PREFIX)/../etc/runit/sv/runit-journal/supervise

clean:
	@rm -rv $(BIN_DIR) 2>/dev/null || true
	@rm -rv $(OBJ_DIR) 2>/dev/null || true
	@rm -rv build/ 2>/dev/null || true

