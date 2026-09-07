CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -O2
LDLIBS ?= -lm
TARGET := engineering-calculator

.PHONY: all clean check

all: $(TARGET)

$(TARGET): Finalcopy.c
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

check:
	$(CC) -std=c11 -Wall -Wextra -Wpedantic -fsyntax-only Finalcopy.c

clean:
	$(RM) $(TARGET)
