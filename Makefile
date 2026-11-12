CC      ?= gcc
CFLAGS  ?= -O2 -Wall -Wextra -std=c11
PKG     ?= pkg-config

GTK_CFLAGS  := $(shell $(PKG) --cflags gtk+-3.0 2>/dev/null)
GTK_LIBS    := $(shell $(PKG) --libs   gtk+-3.0 2>/dev/null)

SRCS = src/cipher.c src/main.c
BIN  = padlockCubano

.PHONY: all clean

all: $(BIN)

$(BIN): $(SRCS)
ifeq ($(GTK_LIBS),)
	@echo "ERROR: GTK+3 devel no encontrado (pkg-config gtk+-3.0 fallo)."
	@echo "Instala libgtk-3-dev o usa build-windows.sh para generar padlockCubano.exe"
	@exit 1
endif
	$(CC) $(CFLAGS) $(GTK_CFLAGS) $(SRCS) -o $(BIN) $(GTK_LIBS)

clean:
	rm -f $(BIN) padlockCubano.exe
