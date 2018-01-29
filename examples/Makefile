# change to y to enable debugging support
DEBUG=n

CFLAGS=-Wall -Wextra
LDFLAGS=
LDLIBS=

CC=gcc

ifeq ($(DEBUG), y)
	CFLAGS += -g 
else
	CFLAGS += -O2
endif

.PHONY: all clean 

SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:src/%.c=obj/%.o)
TARGETS=$(SRCS:src/%.c=bin/%)

all: $(TARGETS)

bin/%: obj/%.o
	$(CC) $(CFLAGS) $< -o $@

obj/%.o: src/%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) *~ obj/*.o obj/*.d bin/*

