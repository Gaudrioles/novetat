#include <gtk/gtk.h>

#include "app.h"

void mise_en_forme_label_version(GtkWidget* label, char* version, int id)
{
    gchar* tampon_label = NULL;

    tampon_label = g_strdup_printf("<span font=\"8\" font_family=\"Verdana\"><b>%s\n%s</b></span>",tableau_id[id], version);

    gtk_label_set_markup(GTK_LABEL(label), tampon_label);
    g_free(tampon_label);

    return;
}

void update_disponible(GtkWidget* label, int id)
{
    if(id == 0)
    {
        gchar* tampon = g_strdup_printf("<span font_family=\"Verdana\" font=\"8\" color=\"green\"><b>Version à jour</b></span>");
        gtk_label_set_markup(GTK_LABEL(label), tampon);
        g_free(tampon);
    }
    else
    {
        gchar* tampon = g_strdup_printf("<span font_family=\"Verdana\" font=\"8\" color=\"red\"><b>Mise à jour disponible</b></span>");
        gtk_label_set_markup(GTK_LABEL(label), tampon);
        g_free(tampon);
    }
    return;
}

void cleaner_fonction(gpointer data)
{
    int compteur = 0;

    app* application = data;

    for(compteur = 0; compteur < nombre_element; compteur++)
    {
        gtk_label_set_text(GTK_LABEL(application->label_update_item[compteur]), "");
    }
    return;
}
