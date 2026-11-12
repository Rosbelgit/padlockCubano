#!/usr/bin/env python3
"""Extrae paquetes .pkg.tar.zst de MSYS2 en un prefijo local.

Uso: extract_msys2.py <dir_paquetes> <raiz_destino>
Los paquetes contienen rutas tipo mingw64/bin/..., por lo que la raiz destino
debe ser el directorio que contiene a mingw64.
"""
import os
import sys
import tarfile
import zstandard


def extract_pkg(path, dest):
    with open(path, "rb") as fh:
        reader = zstandard.ZstdDecompressor().stream_reader(fh)
        with tarfile.open(fileobj=reader, mode="r|") as tar:
            for m in tar:
                target = os.path.join(dest, m.name)
                parent = os.path.dirname(target)
                if parent:
                    os.makedirs(parent, exist_ok=True)
                if m.isdir():
                    os.makedirs(target, exist_ok=True)
                    continue
                if os.path.lexists(target):
                    os.remove(target)
                if m.issym():
                    os.symlink(m.linkname, target)
                elif m.islnk():
                    os.link(os.path.join(dest, m.linkname), target)
                elif m.isfile():
                    src = tar.extractfile(m)
                    with open(target, "wb") as out:
                        while True:
                            b = src.read(1 << 20)
                            if not b:
                                break
                            out.write(b)
                    os.chmod(target, m.mode)


def main():
    pkg_dir, dest = sys.argv[1], sys.argv[2]
    os.makedirs(dest, exist_ok=True)
    files = sorted(f for f in os.listdir(pkg_dir) if f.endswith(".pkg.tar.zst"))
    for i, name in enumerate(files, 1):
        print(f"[{i}/{len(files)}] {name}", flush=True)
        extract_pkg(os.path.join(pkg_dir, name), dest)
    print("Extraccion completa:", dest)


if __name__ == "__main__":
    main()
