CC = clang
CFLAGS = -Wall -Wextra -std=c99 -pedantic -I$(INC_DIR)
LDFLAGS = 

# Directory structure
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
TARGET = $(BIN_DIR)/main

.PHONY: all clean directories

all: directories $(TARGET)

directories:
	mkdir -p $(SRC_DIR) $(INC_DIR) $(OBJ_DIR) $(BIN_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/*

