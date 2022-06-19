# TODO: learn how to actually use make

OBJ_DIR := ./bin/obj
BIN_DIR := ./bin
SRC_DIR := ./src

CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic -std=c99 -O2 -I$(SRC_DIR) -fdiagnostics-color
LDFLAGS := -lpthread -lm

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:%=$(OBJ_DIR)/%.o)

$(BUILD_DIR)/rayleigh: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@