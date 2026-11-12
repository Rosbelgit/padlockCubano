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

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cipher.h"

static void expect_eq(const char *actual, const char *expected, const char *what)
{
    if (actual == NULL || strcmp(actual, expected) != 0)
    {
        fprintf(stderr, "FALLO: %s\n  esperado: %s\n  obtenido: %s\n", what, expected,
                actual != NULL ? actual : "(null)");
        exit(1);
    }
}

int main(void)
{
    const char *key = "NQXPOMAFTRHLZGECYJIUWSKDVB";

    assert(padlock_valid_key(key));
    assert(!padlock_valid_key("NQXPOMAFTRHLZGECYJIUWSKDV"));
    assert(!padlock_valid_key("NQXPOMAFTRHLZGECYJIUWSKDVBB"));
    assert(!padlock_valid_key("NQXPOMAFTRHLZGECYJIUWSKD1B"));
    assert(!padlock_valid_key("AAAAAAAAAAAAAAAAAAAAAAAAAA"));

    char *cipher = padlock_encrypt("ABC xyz! 123", key);
    expect_eq(cipher, "NQX dvb! 123", "cifrado con mayusculas/minusculas y simbolos");

    char *plain = padlock_decrypt(cipher, key);
    expect_eq(plain, "ABC xyz! 123", "descifrado del mensaje anterior");

    char *again = padlock_encrypt(plain, key);
    expect_eq(again, cipher, "cifrado idempotente");

    char *random_key = padlock_generate_key();
    assert(random_key != NULL);
    assert(padlock_valid_key(random_key));

    char *round_trip = padlock_decrypt(padlock_encrypt("Hola, mundo cubano!", random_key), random_key);
    expect_eq(round_trip, "Hola, mundo cubano!", "ida y vuelta con clave aleatoria");

    printf("Todas las pruebas pasaron.\n");
    printf("Clave de ejemplo: %s\n", key);
    printf("Clave aleatoria:  %s\n", random_key);

    free(cipher);
    free(plain);
    free(again);
    free(random_key);
    free(round_trip);
    return 0;
}
