# padlockCubano

Cifrador/descifrador por **sustitución simple** (monoalfabeto) con interfaz gráfica en **GTK+3**. Proyecto enfocado a **Windows** (`.exe`), compilable desde Linux con MinGW-w64.

## Origen
Backend adaptado de `substitution.c` (CS50): lee una clave de 26 letras y reemplaza cada letra del mensaje por la letra de la clave en la misma posición del abecedario.

## Estructura
- `src/cipher.h` / `src/cipher.c` : motor de cifrado (cifrar/descifrar/validar clave/generar clave aleatoria).
- `src/main.c` : ventana GTK+3 (clave, texto, botones Cifrar/Descifrar/Limpiar y resultado).
- `Makefile` : compilación nativa Linux (necesita `libgtk-3-dev`).
- `build_windows.sh` : compilación cruzada para Windows (`.exe`) con MinGW-w64 + GTK para Windows (sysroot de MSYS2).
- `tests/test_cipher.c` : pruebas unitarias del motor de cifrado.
- `tools/extract_msys2.py` : extrae paquetes `.pkg.tar.zst` de MSYS2 en un prefijo local.

## Requisitos
- **Linux (nativo):** GTK+3 devel (`pkg-config --libs gtk+-3.0` debe funcionar) y `gcc`.
- **Windows (`.exe`):** compilador cruzado `x86_64-w64-mingw32-gcc` y un sysroot con GTK+3 para Windows (paquete `mingw-w64-x86_64-gtk3` y dependencias de `repo.msys2.org`), en `$HOME/.local/opt/padlock/msys/mingw64` (o variable `MINGW_PREFIX`).

## Compilar en Linux
```bash
make
./padlockCubano
```

## Compilar para Windows (.exe)
```bash
./build_windows.sh
```
Genera `dist/padlockCubano.exe`. Copia también las DLL de GTK (`dist/*.dll`) junto al `.exe` para que funcione en Windows.

> **Advertencia:** el `.exe` no está firmado digitalmente. Al darle doble clic en Windows puede aparecer una advertencia de seguridad ("Abrir archivo" / SmartScreen). Usa "Más información → Ejecutar de todos modos", o en Propiedades del archivo marca "Desbloquear".

## Uso
1. Escribe una clave de exactamente 26 letras del abecedario sin repetir (mayúsculas o minúsculas).
2. Escribe el mensaje.
3. Pulsa **Cifrar** o **Descifrar**. Los caracteres que no son letras se dejan igual.

## Ejecutar pruebas
```bash
gcc -O2 -Wall -Wextra -std=c11 -I src src/cipher.c tests/test_cipher.c -o tests/test_cipher
./tests/test_cipher
```

## Licencia

Este proyecto está licenciado bajo la **GNU General Public License v3.0**.
Copyright (C) 2026 Jorge Rosbel Portal Rusindo.

Puedes ver el texto completo de la licencia en el archivo [LICENSE.md](LICENSE.md) o en <https://www.gnu.org/licenses/gpl-3.0.html>.
