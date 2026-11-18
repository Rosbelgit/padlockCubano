# padlockCubano

Cifrador/descifrador por **sustitución simple** (monoalfabeto) con interfaz gráfica en **GTK+3**. Proyecto orientado a Windows (`.exe`).

## Origen

Backend inspirado en (CS50): lee una clave de 26 letras y reemplaza cada letra del mensaje por la letra de la clave en la misma posición del abecedario. Los caracteres que no son letras (espacios, números, signos) se dejan igual.

## Estructura

- `src/cipher.h` / `src/cipher.c` — motor de cifrado: validar clave, cifrar, descifrar y generar clave aleatoria.
- `src/main.c` — ventana GTK+3 (clave, texto, botones Cifrar / Descifrar / Limpiar y resultado).
- `tests/test_cipher.c` — pruebas automáticas del motor.
- `Makefile` — compilación nativa Linux.
- `build_windows.sh` — compilación cruzada para Windows (`.exe`) con MinGW-w64 + GTK de MSYS2.
- `tools/extract_msys2.py` — extrae paquetes `.pkg.tar.zst` de MSYS2 en un prefijo local.
- `LICENSE.md` — texto completo de la GNU GPL v3.
- `dist/` — `padlockCubano.exe` ya construido junto con las DLL de GTK+3 (no se sube al repositorio).

## Requisitos

### Linux (compilación nativa)
- `build-essential` (gcc, make)
- GTK+3 devel: `libgtk-3-dev` (debe funcionar `pkg-config --libs gtk+-3.0`)

### Windows (`.exe`)
- Compilador cruzado: `x86_64-w64-mingw32-gcc` (paquete `gcc-mingw-w64-x86-64`)
- Sysroot con GTK+3 para Windows (paquetes `mingw-w64-x86_64-gtk3` y dependencias de [repo.msys2.org](https://repo.msys2.org/mingw/mingw64/)), extraídos en `$HOME/.local/opt/padlock/mingw64` (o `PADLOCK_PREFIX`). Usa `tools/extract_msys2.py`.

## Compilar

### Linux
```bash
make
./padlockCubano
```

### Windows (.exe)
```bash
./build_windows.sh
```
Genera `dist/padlockCubano.exe`. Para ejecutarlo en Windows, copia también las DLL de GTK (`dist/*.dll`) junto al `.exe` (ya vienen incluidas en `dist/`).

## Uso

1. Escribe una clave de exactamente 26 letras del abecedario **sin repetir** (mayúsculas o minúsculas).
2. Escribe el mensaje.
3. Pulsa **Cifrar** o **Descifrar**.

## Advertencia (Windows)

El `.exe` no está firmado digitalmente, por lo que Windows puede mostrar una advertencia de seguridad al abrirlo. Pulsa "Más información" → "Ejecutar de todas formas", o en Propiedades del archivo marca **Desbloquear**.

## Licencia

Este proyecto está licenciado bajo la **GNU General Public License v3.0** (o cualquier versión posterior).
Copyright (C) 2026 Jorge Rosbel Portal Rusindo.

Puedes ver el texto completo de la licencia en el archivo [LICENSE.md](LICENSE.md) o en <https://www.gnu.org/licenses/gpl-3.0.html>.
