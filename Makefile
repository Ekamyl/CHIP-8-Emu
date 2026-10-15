CC      	:= gcc
CFLAGS  	:= -pedantic-errors -Wall -Wextra -g -O0 -std=c11
LDFLAGS 	:= -F/Library/Frameworks -Wl,-rpath,/Library/Frameworks
LIBFLAGS 	:= -framework SDL2

SRC_DIR   := src
BUILD_DIR := build
SRC       := $(wildcard $(SRC_DIR)/*.c)
OBJ       := $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
TARGET    := $(BUILD_DIR)/chip8

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS) $(LIBFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

run: $(TARGET)
	./$(TARGET)