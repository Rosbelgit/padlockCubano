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

#include <gtk/gtk.h>
#include <string.h>

#include "cipher.h"

static GtkEntry *key_entry;
static GtkEntry *text_entry;
static GtkLabel *result_label;

static void set_result(const char *text)
{
    gtk_label_set_text(result_label, text);
}

static void on_encrypt(GtkButton *b, gpointer user_data)
{
    (void)b;
    (void)user_data;
    const char *key = gtk_entry_get_text(key_entry);
    const char *text = gtk_entry_get_text(text_entry);

    if (!padlock_valid_key(key))
    {
        set_result("Clave invalida: debe tener 26 letras del abecedario sin repetir.");
        return;
    }
    char *out = padlock_encrypt(text, key);
    if (out)
    {
        set_result(out);
        free(out);
    }
    else
    {
        set_result("Error al cifrar.");
    }
}

static void on_decrypt(GtkButton *b, gpointer user_data)
{
    (void)b;
    (void)user_data;
    const char *key = gtk_entry_get_text(key_entry);
    const char *text = gtk_entry_get_text(text_entry);

    if (!padlock_valid_key(key))
    {
        set_result("Clave invalida: debe tener 26 letras del abecedario sin repetir.");
        return;
    }
    char *out = padlock_decrypt(text, key);
    if (out)
    {
        set_result(out);
        free(out);
    }
    else
    {
        set_result("Error al descifrar.");
    }
}

static void on_clear(GtkButton *b, gpointer user_data)
{
    (void)b;
    (void)user_data;
    gtk_entry_set_text(key_entry, "");
    gtk_entry_set_text(text_entry, "");
    set_result("");
}

int main(int argc, char **argv)
{
    gtk_init(&argc, &argv);

    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(win), "Padlock Cubano - Cifrado por sustitucion");
    gtk_window_set_default_size(GTK_WINDOW(win), 700, 420);
    gtk_container_set_border_width(GTK_CONTAINER(win), 12);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(win), box);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 12);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 8);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(box), grid, FALSE, FALSE, 0);

    key_entry = GTK_ENTRY(gtk_entry_new());
    gtk_entry_set_placeholder_text(key_entry, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    gtk_entry_set_max_length(key_entry, 26);
    GtkWidget *l1 = gtk_label_new("Clave (26 letras):");
    gtk_misc_set_alignment(GTK_MISC(l1), 1, 0.5f);
    gtk_grid_attach(GTK_GRID(grid), l1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(key_entry), 1, 0, 1, 1);

    text_entry = GTK_ENTRY(gtk_entry_new());
    gtk_entry_set_placeholder_text(text_entry, "Escribe tu mensaje aqui...");
    GtkWidget *l2 = gtk_label_new("Texto:");
    gtk_misc_set_alignment(GTK_MISC(l2), 1, 0.5f);
    gtk_grid_attach(GTK_GRID(grid), l2, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(text_entry), 1, 1, 1, 1);

    GtkWidget *bbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
    GtkWidget *be = gtk_button_new_with_label("Cifrar");
    GtkWidget *bd = gtk_button_new_with_label("Descifrar");
    GtkWidget *bc = gtk_button_new_with_label("Limpiar");
    gtk_box_pack_start(GTK_BOX(bbox), be, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(bbox), bd, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(bbox), bc, TRUE, TRUE, 0);
    gtk_grid_attach(GTK_GRID(grid), bbox, 1, 2, 1, 1);

    g_signal_connect(be, "clicked", G_CALLBACK(on_encrypt), NULL);
    g_signal_connect(bd, "clicked", G_CALLBACK(on_decrypt), NULL);
    g_signal_connect(bc, "clicked", G_CALLBACK(on_clear), NULL);

    GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(box), scrolled, TRUE, TRUE, 0);

    result_label = GTK_LABEL(gtk_label_new(""));
    gtk_label_set_line_wrap(GTK_LABEL(result_label), TRUE);
    gtk_misc_set_alignment(GTK_MISC(result_label), 0, 0);
    gtk_container_add(GTK_CONTAINER(scrolled), GTK_WIDGET(result_label));

    gtk_widget_show_all(win);
    gtk_main();
    return 0;
}
