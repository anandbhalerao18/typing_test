# Compiler and flags
CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -lncurses

# Directories
SRC = src
BUILD = build

# Source and object files
SRCS = $(SRC)/main.c $(SRC)/tui.c $(SRC)/logic.c $(SRC)/file_handler.c $(SRC)/utils.c
OBJS = $(SRCS:$(SRC)/%.c=$(BUILD)/%.o)

# Output binary
TARGET = $(BUILD)/typing_test

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile each .c file into build/ directory
$(BUILD)/%.o: $(SRC)/%.c
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD)/*.o $(TARGET)

# Run the program after building
run: all
	./$(TARGET)
