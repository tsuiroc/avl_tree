CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -fPIC -shared
AVL_SRC = $(shell pwd)/demo_avl.c
AVL_OBJ = $(patsubst %.c,%.o,$(AVL_SRC))
AVL_INC = $(shell pwd)/demo_avl.h
AVL_LIB = demo_avl

TEST_SRC = $(shell pwd)/test.c

.PHONY: all so clean
all: so
	@$(CC) -g $(TEST_SRC) -L$(shell pwd) -I$(shell pwd) -l$(AVL_LIB) -o avl_test

so: $(AVL_SRC)
	@$(CC) -g $(AVL_SRC) $(LDFLAGS) -o lib$(AVL_LIB).so
	@cp lib$(AVL_LIB).so /lib/

clean:
	@rm -rf /lib/lib$(AVL_LIB).so
	@rm -rf $(shell pwd)/lib$(AVL_LIB).so
	@rm -rf $(shell pwd)/avl_test
