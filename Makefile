CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lncurses  # ncurses-Bibliothek hinzufügen

SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj

SRC_FILES = $(SRC_DIR)/main.c $(SRC_DIR)/board.c
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

EXEC = $(BIN_DIR)/gol

all: $(EXEC)

$(EXEC): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LDFLAGS) -o $(EXEC)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(EXEC)

.PHONY: all clean
