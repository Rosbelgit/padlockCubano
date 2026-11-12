/*
Nombre del programa: padlockCubano
Breve descripción: Cifrador/descifrador por sustitución simple con interfaz gráfica GTK+3.
Copyright (C) 2026  Jorge Rosbel Portal Rusindo

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef PADLOCK_CIPHER_H
#define PADLOCK_CIPHER_H

#include <stddef.h>

/* Valida que la clave tenga exactamente 26 letras del abecedario,
   sin repetir (ignora mayusculas/minusculas). Devuelve 1 si es valida, 0 si no. */
int padlock_valid_key(const char *key);

/* Cifra texto con cifrado por sustitucion usando la clave.
   Devuelve cadena reservada con malloc que el llamante libera con free(). */
char *padlock_encrypt(const char *text, const char *key);

/* Descifra texto cifrado con la misma clave. Cadena reservada con malloc. */
char *padlock_decrypt(const char *text, const char *key);

/* Genera una clave aleatoria de 26 letras sin repetir. Cadena reservada con malloc. */
char *padlock_generate_key(void);

#endif
