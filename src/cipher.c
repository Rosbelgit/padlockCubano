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

#include "cipher.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int build_maps(const char *key, char enc[26], char dec[26])
{
    int seen[26] = {0};
    int n = 0;
    while (key[n] && n < 26)
        n++;
    if (n != 26 || key[n] != '\0')
        return -1;

    for (int i = 0; i < 26; i++)
    {
        char c = key[i];
        if (!isalpha((unsigned char)c))
            return -1;
        int idx = toupper((unsigned char)c) - 'A';
        if (seen[idx])
            return -1;
        seen[idx] = 1;
        enc[i] = c;                 /* letra del abecedario en posicion i -> clave[i] */
        dec[idx] = (char)('A' + i); /* clave[i]      -> letra del abecedario en posicion i */
    }
    return 0;
}

static char *transform(const char *text, const char *key, int mode)
{
    /* mode 0 = cifrar, mode 1 = descifrar */
    char enc[26], dec[26];
    if (build_maps(key, enc, dec) != 0)
        return NULL;

    size_t len = strlen(text);
    char *out = malloc(len + 1);
    if (!out)
        return NULL;

    for (size_t i = 0; i < len; i++)
    {
        char c = text[i];
        if (!isalpha((unsigned char)c))
        {
            out[i] = c;
            continue;
        }
        int upper = isupper((unsigned char)c);
        int idx = toupper((unsigned char)c) - 'A';
        char r = (mode == 0) ? enc[idx] : dec[idx];
        out[i] = upper ? (char)toupper((unsigned char)r)
                       : (char)tolower((unsigned char)r);
    }
    out[len] = '\0';
    return out;
}

int padlock_valid_key(const char *key)
{
    char enc[26], dec[26];
    return build_maps(key, enc, dec) == 0;
}

char *padlock_encrypt(const char *text, const char *key)
{
    return transform(text, key, 0);
}

char *padlock_decrypt(const char *text, const char *key)
{
    return transform(text, key, 1);
}

char *padlock_generate_key(void)
{
    static int seeded = 0;
    if (!seeded)
    {
        srand((unsigned)time(NULL));
        seeded = 1;
    }

    char letters[26];
    for (int i = 0; i < 26; i++)
        letters[i] = (char)('A' + i);

    /* Mezcla Fisher-Yates */
    for (int i = 25; i > 0; i--)
    {
        int j = rand() % (i + 1);
        char tmp = letters[i];
        letters[i] = letters[j];
        letters[j] = tmp;
    }

    char *key = malloc(27);
    if (!key)
        return NULL;
    memcpy(key, letters, 26);
    key[26] = '\0';
    return key;
}
