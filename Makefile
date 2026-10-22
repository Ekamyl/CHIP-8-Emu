CC      	:= clang
CFLAGS      := -pedantic-errors -Wno-gnu-label-as-value -Wall -Wextra -g -O0 -std=c23 -F/Library/Frameworks -I/Library/Frameworks/SDL3.framework/Headers
LDFLAGS 	:= -F/Library/Frameworks -Wl,-rpath,/Library/Frameworks
LIBFLAGS 	:= -framework SDL3

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
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

run: $(TARGET)
	./$(TARGET)
