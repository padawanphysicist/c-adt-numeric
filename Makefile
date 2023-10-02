EXAMPLES_DIR ?= examples
SRC_DIR ?= src
INC_DIR ?= include rep

CC = gcc
INCFLAGS=$(foreach d, $(INC_DIR), -I$d)
CFLAGS = -std=c89 -Wall -Wextra -O2 -g
LDFLAGS = -lm

SRCS := $(wildcard $(SRC_DIR)/*.c)
SRC_TARGETS := $(wildcard $(EXAMPLES_DIR)/*.c)
OBJS := $(SRCS:%.c=%.o) $(SRC_TARGETS:%.c=%.o)

TARGETS := $(SRC_TARGETS:%.c=%.exe)

all: $(TARGETS)

$(TARGETS): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(INCFLAGS) -c $^ -o $@

.PHONY: doc
doc: Doxyfile
	mkdir -p doc/
	doxygen

.PHONY: clean clean-all
clean:
	find . -iname "*.o" -type f -delete
clean-all: clean
	find . -iname "*.exe" -type f -delete
