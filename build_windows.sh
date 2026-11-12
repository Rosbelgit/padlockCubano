#!/usr/bin/env bash
# Compila padlockCubano.exe para Windows (x86_64) usando un prefijo MinGW-w64/GTK3.
#
# Funciona con:
#   - Un gcc de Linux con target Windows (x86_64-w64-mingw32-gcc).
#   - MSYS2 en Windows.
#   - MSYS2 ejecutado desde WSL mediante interoperabilidad (gcc.exe).
set -euo pipefail

ROOT="$(cd "$(dirname "$0")" && pwd)"
PREFIX="${MINGW_PREFIX:-$HOME/.local/opt/padlock/msys/mingw64}"
DIST="$ROOT/dist"

if [[ -x "$PREFIX/bin/gcc.exe" ]]; then
    BASE_CC="$PREFIX/bin/gcc.exe"
    WINDOWS_EXE=1
elif [[ -x "$PREFIX/bin/gcc" ]]; then
    BASE_CC="$PREFIX/bin/gcc"
    WINDOWS_EXE=0
else
    echo "ERROR: no se encontro el compilador en $PREFIX/bin" >&2
    echo "Instala MSYS2 + mingw-w64-x86_64-gtk3 o define MINGW_PREFIX." >&2
    exit 1
fi

mkdir -p "$DIST"

INCLUDES=(
    "-I$ROOT/src"
    "-I$PREFIX/include"
    "-I$PREFIX/include/gtk-3.0"
    "-I$PREFIX/include/glib-2.0"
    "-I$PREFIX/lib/glib-2.0/include"
    "-I$PREFIX/include/pango-1.0"
    "-I$PREFIX/include/cairo"
    "-I$PREFIX/include/gdk-pixbuf-2.0"
    "-I$PREFIX/include/atk-1.0"
    "-I$PREFIX/include/harfbuzz"
    "-I$PREFIX/include/freetype2"
    "-I$PREFIX/include/libpng16"
    "-I$PREFIX/include/pixman-1"
    "-I$PREFIX/include/fontconfig"
    "-I$PREFIX/include/fribidi"
    "-I$PREFIX/include/libxml2"
)

LIBS=(
    "-L$PREFIX/lib"
    -lgtk-3 -lgdk-3 -lgdk_pixbuf-2.0
    -lpangocairo-1.0 -lpango-1.0
    -lcairo-gobject -lcairo
    -latk-1.0 -lharfbuzz
    -lgobject-2.0 -lglib-2.0
    -lintl
)

FLAGS=(-O2 -std=c11 -Wall -Wextra -mwindows)

if [[ "$WINDOWS_EXE" == 1 ]]; then
    # gcc.exe es un binario de Windows. Si se invoca como "gcc.exe", Windows
    # puede resolver otro gcc del PATH (por ejemplo el de ucrt64). Se usa una
    # copia con nombre propio y se ejecuta desde su propio directorio para que
    # gcc calcule bien su prefijo.
    CC_COPY="$PREFIX/bin/padlock-gcc.exe"
    cp -f "$BASE_CC" "$CC_COPY"
    echo "Compilando con $CC_COPY (interoperabilidad Windows/WSL)"
    (
        cd "$PREFIX/bin"
        ./padlock-gcc.exe "${FLAGS[@]}" "${INCLUDES[@]}" \
            "$ROOT/src/main.c" "$ROOT/src/cipher.c" \
            -o "$DIST/padlockCubano.exe" \
            "${LIBS[@]}"
    )
else
    echo "Compilando con $BASE_CC"
    "$BASE_CC" "${FLAGS[@]}" "${INCLUDES[@]}" \
        "$ROOT/src/main.c" "$ROOT/src/cipher.c" \
        -o "$DIST/padlockCubano.exe" \
        "${LIBS[@]}"
fi

echo "Copiando DLLs y recursos de GTK..."
cp -f "$PREFIX"/bin/*.dll "$DIST"/ 2>/dev/null || true
mkdir -p "$DIST/share/glib-2.0/schemas"
cp -f "$PREFIX"/share/glib-2.0/schemas/* "$DIST/share/glib-2.0/schemas/" 2>/dev/null || true
cp -rf "$PREFIX"/share/icons "$DIST/share/" 2>/dev/null || true
mkdir -p "$DIST/lib"
cp -rf "$PREFIX"/lib/gdk-pixbuf-2.0 "$DIST/lib/" 2>/dev/null || true

if [[ -x "$PREFIX/bin/glib-compile-schemas.exe" ]]; then
    "$PREFIX/bin/glib-compile-schemas.exe" "$DIST/share/glib-2.0/schemas" 2>/dev/null || true
elif [[ -x "$PREFIX/bin/glib-compile-schemas" ]]; then
    "$PREFIX/bin/glib-compile-schemas" "$DIST/share/glib-2.0/schemas" 2>/dev/null || true
fi

chmod +x "$DIST/padlockCubano.exe" 2>/dev/null || true

echo "Listo: $DIST/padlockCubano.exe"
