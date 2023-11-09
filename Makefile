CC = gcc
CFLAGS:= -std=c99 \
	-Wall \
	-Wextra \
	-pedantic

# For Unity
UNITY_CFLAGS = -DUNITY_INCLUDE_DOUBLE
UNITY_SRCS=./modules/Unity/src/unity.c
UNITY_INCDIR=./modules/Unity/src/

# For numeric
NUMERIC_CFLAGS =
NUMERIC_SRCS=$(shell find ./src/ -type f -name '*.c')
NUMERIC_INCDIR=./src/ ./include/
NUMERIC_LDFLAGS = -lm -larb -lflint -ggdb3

INCDIR = $(UNITY_INCDIR) $(NUMERIC_INCDIR) 
INCFLAGS=$(foreach d,$(INCDIR),-I$d)
CFLAGS+=$(UNITY_CFLAGS) $(NUMERIC_CFLAGS)
LDFLAGS+=$(NUMERIC_LDFLAGS)

all: test.out

SRCS := $(UNITY_SRCS) $(NUMERIC_SRCS) ./test/test.c
OBJS := $(SRCS:%.c=%.o)

.PHONY: test
test: test.out
	@valgrind \
	--leak-check=full \
	--show-leak-kinds=all \
    --track-origins=yes \
    --verbose          \
    --log-file=valgrind-out.txt \
    ./test.out

test.out: $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(INCFLAGS) $(CFLAGS) -c $^ -o $@

.PHONY: doc
doc: Doxyfile
	mkdir -p doc/
	doxygen

.PHONY: clean
clean:
	find . -iname "*.o" -type f -delete
clean-all: clean
	find . -iname "*.out" -type f -delete
