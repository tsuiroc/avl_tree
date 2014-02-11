CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -fPIC -shared
AVL_SRC = $(shell pwd)/demo_avl.c
AVL_OBJ = $(patsubst %.c,%.o,$(AVL_SRC))
AVL_INC = $(shell pwd)/demo_avl.h
AVL_LIB = demo_avl

TEST_SRC = $(shell pwd)/test.c

.PHONY: all so
all: so
	$(CC) $(TEST_SRC) -L$(shell pwd) -I$(shell pwd) -l$(AVL_LIB)

so: $(AVL_SRC)
	$(CC) $(AVL_SRC) $(LDFLAGS) -o lib$(AVL_LIB).so
