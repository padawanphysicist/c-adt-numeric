SRC_DIR ?= src
INC_DIR ?= include rep
TESTS_DIR:=tests

CC = gcc
INCFLAGS=$(foreach d, $(INC_DIR), -I$d)
CFLAGS = -std=c89 -Wall -Wextra -O2 -g
LDFLAGS = -lm

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:%.c=%.o) $(SRC_TARGETS:%.c=%.o)

%.o: %.c
	$(CC) $(INCFLAGS) -c $^ -o $@

all: $(TESTS_DIR)/tests.exe

.PHONY: update-tests
create-tests:
	cd $(TESTS_DIR) && guile -e main -s create_test -i tests.json -o tests.c

.PHONY: test
test: $(TESTS_DIR)/tests.exe
	@cd $(TESTS_DIR) && (./tests.exe || echo "Passed $$? from $$(cat tests.json | jq '. | length')" )
$(TESTS_DIR)/tests.o: $(TESTS_DIR)/tests.c
	$(CC) $(INCFLAGS) -c $^ -o $@
$(TESTS_DIR)/tests.exe: $(OBJS) $(TESTS_DIR)/tests.o
	$(CC) $^ -o $@ $(LDFLAGS)

.PHONY: doc
doc: Doxyfile
	mkdir -p doc/
	doxygen

.PHONY: clean clean-all
clean:
	find . -iname "*.o" -type f -delete
clean-all: clean
	find . -iname "*.exe" -type f -delete
	rm -rf tests/tests.c
