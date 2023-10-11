CC = gcc
CFLAGS:= -std=c99 \
	-Wall \
	-Wextra \
	-pedantic \
	-DM_PI=3.14159265358979323846 \
	-D_TOLERANCE=1e-7
LOGFLAGS = -DLOG_USE_COLOR
LDFLAGS = -lm
UNITYFLAGS = -DUNITY_INCLUDE_DOUBLE

INCDIR =  ./unity/src $(shell find ./ -type f -name '*.h' -and -not -wholename './unity/*' -exec dirname {} \; | sort | uniq)
INCFLAGS=$(foreach d,$(INCDIR),-I$d)

all: test.out

UNITYSRCS=$(shell find ./unity/src -type f -name '*.c')
SRCS := $(shell find ./ -type f -name '*.c' -and -not -wholename './unity*') $(UNITYSRCS)
OBJS := $(SRCS:%.c=%.o)

#all: $(TESTS_DIR)/tests.exe
.PHONY: test
test: test.out
	./test.out
test.out: $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(INCFLAGS) $(CFLAGS) $(LOGFLAGS) $(UNITYFLAGS) -c $^ -o $@

.PHONY: doc
doc: Doxyfile
	mkdir -p doc/
	doxygen

.PHONY: clean
clean:
	find . -iname "*.o" -type f -delete
clean-all: clean
	find . -iname "*.out" -type f -delete
