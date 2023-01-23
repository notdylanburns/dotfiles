DOTTOOLS := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
BIN_DIR := $(DOTTOOLS)/bin
SRC_DIR := $(DOTTOOLS)/src

CC ?= gcc
CFLAGS +=
LDFLAGS +=

.PHONY: all
all: dirs dropdown_menu


#dirs

.PHONY: dirs
dirs:
	mkdir -p $(BIN_DIR)


# dropdown_menu

.PHONY: dropdown_menu
dropdown_menu: $(BIN_DIR)/dropdown_menu

$(BIN_DIR)/dropdown_menu: $(SRC_DIR)/dropdown_menu.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -lncurses
