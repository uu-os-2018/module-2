DEBUG=y

CC=gcc
CFLAGS=-std=gnu99 -Werror -Wall
LDFLAGS=

ifeq ($DEBUG), y)
	CFLAGS += -DDEBUG -g
else
	CFLAGS += -O2
endif

.PHONY: all clean

all: bin/shell

bin/shell: obj/shell.o obj/parser.o
	$(CC) $^ -o $@

obj/%.o: src/%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) *~ src/*~ src/#* obj/*.o bin/*
