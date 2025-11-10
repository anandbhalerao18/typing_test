
CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -lncurses
SRC = src
BUILD = build
SRCS = $(SRC)/main.c $(SRC)/tui.c $(SRC)/logic.c $(SRC)/file_handler.c $(SRC)/utils.c
OBJS = $(SRCS:.c=.o)
TARGET = $(BUILD)/typing_test
all: $(TARGET)
$(TARGET): $(OBJS)
	mkdir -p $(BUILD)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD)/*.o $(TARGET)
