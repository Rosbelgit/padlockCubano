CC      ?= gcc
CFLAGS  ?= -O2 -Wall -Wextra -std=c11
PKG     ?= pkg-config

GTK_CFLAGS  := $(shell $(PKG) --cflags gtk+-3.0 2>/dev/null)
GTK_LIBS    := $(shell $(PKG) --libs   gtk+-3.0 2>/dev/null)

SRCS = src/cipher.c src/main.c
BIN  = padlockCubano
TEST = tests/test_cipher

.PHONY: all clean test

all: $(BIN) $(TEST)

$(BIN): $(SRCS)
ifeq ($(GTK_LIBS),)
	@echo "ERROR: GTK+3 devel no encontrado (pkg-config gtk+-3.0 fallo)."
	@echo "Instala libgtk-3-dev o usa build-windows.sh para generar padlockCubano.exe"
	@exit 1
endif
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $(SRCS) -o $(BIN) $(GTK_LIBS)

$(TEST): src/cipher.c tests/test_cipher.c
	$(CC) $(CFLAGS) -I src src/cipher.c tests/test_cipher.c -o $(TEST)

test: $(TEST)
	./$(TEST)

clean:
	rm -f $(BIN) $(TEST) padlockCubano.exe
