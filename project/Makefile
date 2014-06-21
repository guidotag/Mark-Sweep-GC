CC=gcc

CFLAGS=-O2 -Wall -std=c99 -pedantic #-Werror

BIN_DIR=bin/
SRC_DIR=src/
SRC_TEST_DIR=tests/src/

BIN=gc
OBJ_MAIN=main.o
OBJS=gc.o list.o cell.o trie.o utils.o stack.o

BIN_TEST=tests
OBJ_MAIN_TEST=main.o
OBJS_TEST=test_gc.o test_list.o test_trie.o

OBJ_MAIN_W_DIR=$(SRC_DIR)$(OBJ_MAIN)
OBJS_W_DIR=$(addprefix $(SRC_DIR), $(OBJS))

OBJ_MAIN_TEST_W_DIR=$(SRC_TEST_DIR)$(OBJ_MAIN_TEST)
OBJS_TEST_W_DIR=$(addprefix $(SRC_TEST_DIR), $(OBJS_TEST))

BIN_W_DIR=$(BIN_DIR)$(BIN)
BIN_TEST_W_DIR=$(BIN_DIR)$(BIN_TEST)

.PHONY: all clean gc tests

all: gc tests

gc: $(OBJ_MAIN_W_DIR) $(OBJS_W_DIR)
	$(CC) $(CFLAGS) $^ -o $(BIN_W_DIR)
	
tests: $(OBJS_W_DIR) $(OBJ_MAIN_TEST_W_DIR) $(OBJS_TEST_W_DIR)
	$(CC) $(CFLAGS) $^ -o $(BIN_TEST_W_DIR)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -f $(OBJ_MAIN_W_DIR)
	rm -f $(OBJS_W_DIR)
	rm -f $(BIN_W_DIR)
	rm -f $(OBJS_TEST_W_DIR)
	rm -f $(OBJ_MAIN_TEST_W_DIR)
	rm -f $(BIN_TEST_W_DIR)
	
