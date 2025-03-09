# Compiler to use
CC = gcc

# Directories
SRC_DIR = src
LIB_DIR = src/lib
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/objects

# Compiler flags
CFLAGS = -Wall -Wextra -I$(SRC_DIR) -I$(LIB_DIR)

# Sources and objects
SRC_FILES := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(LIB_DIR)/*.c)
OBJ_FILES := $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SRC_FILES)))

# Output executable
OUTPUT = $(BUILD_DIR)/main

# Default target
all: $(OBJ_DIR) $(OUTPUT)

# Create necessary directories if they don't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Build target for executable
$(OUTPUT): $(OBJ_DIR) $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(OBJ_FILES)

# Build target for object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(LIB_DIR)/%.c $(LIB_DIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -rf $(OBJ_DIR)/*.o $(OUTPUT)

.PHONY: all clean