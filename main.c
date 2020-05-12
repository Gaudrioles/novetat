#include <stdio.h>
#include <stdlib.h>
#include "log.h"
#include "app.h"
#include "gui_fonction.h"
#include "dl.h"

#define icon_install  "Image/install.png"

int main(int argc, char *argv[])
{
    int compteur = 0;

    /* Initialisation de la librairie GTK. */
    gtk_init(&argc, &argv);

    /* Window  */
    application.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(application.window), "Novetat");
    gtk_window_set_position(GTK_WINDOW(application.window), GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request(application.window, 310, 400);
    gtk_window_set_resizable (GTK_WINDOW(application.window), FALSE);
    gtk_container_set_border_width(GTK_CONTAINER(application.window), 10);
    g_object_set(gtk_settings_get_default(),"gtk-application-prefer-dark-theme", TRUE, NULL);

    /* Box  */
    application.box_principale = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    application.box_items = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    application.box_bouton_quitter = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

    for(compteur = 0 ; compteur < nombre_element ; compteur++)
    {
        application.box_principale_item[compteur] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
        application.box_item_info[compteur] = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
        application.box_item_install[compteur] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    }

    gtk_box_set_homogeneous(GTK_BOX(application.box_principale), FALSE);
    gtk_box_set_homogeneous(GTK_BOX(application.box_items), FALSE);
    gtk_box_set_homogeneous(GTK_BOX(application.box_bouton_quitter), TRUE);


    for(compteur = 0 ; compteur < nombre_element ; compteur++)
    {
        gtk_box_set_homogeneous(GTK_BOX(application.box_principale_item[compteur]), FALSE);
    }

    /* Logo */
    for(compteur = 0 ; compteur < nombre_element ; compteur++)
    {
        application.logo_item[compteur] = gtk_image_new_from_file(icon_id[compteur]);
        application.logo_install_item[compteur] = gtk_image_new_from_file(icon_install);
    }


    /* Label */
    for(compteur = 0 ; compteur < nombre_element ; compteur++)
    {
        application.label_version_item[compteur] = gtk_label_new("");
        application.label_update_item[compteur] = gtk_label_new("");
        gtk_label_set_justify(GTK_LABEL(application.label_version_item[compteur]), GTK_JUSTIFY_CENTER);
        gtk_label_set_justify(GTK_LABEL(application.label_update_item[compteur]), GTK_JUSTIFY_CENTER);
    }

    /* Bouton  */
    application.bouton_update = gtk_button_new_with_label("Update");
    application.bouton_quitter = gtk_button_new_with_label("Quitter");

    for(compteur = 0 ; compteur < nombre_element ; compteur++)
    {
        application.bouton_item_install[compteur] = gtk_button_new_from_icon_name(NULL,GTK_ICON_SIZE_DND);
        gtk_button_set_image(GTK_BUTTON(application.bouton_item_install[compteur]), application.logo_install_item[compteur]);
        gtk_button_set_relief(GTK_BUTTON(application.bouton_item_install[compteur]),  GTK_RELIEF_NONE);
        gtk_widget_set_name(application.bouton_item_install[compteur], tableau_id[compteur]);
    }

    /* Scrolled windows */
    application.scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(application.scrolled_window),
                                  GTK_POLICY_NEVER,
                                  GTK_POLICY_ALWAYS);

    /* Progress_bar  */

    for(compteur = 0 ; compteur < nombre_element ; compteur++)
    {
        application.progress_bar_item[compteur]   = gtk_progress_bar_new();
    }

    /* Label markup */

    for(compteur = 0 ; compteur < nombre_element ; compteur++)
    {
        gtk_label_set_markup(GTK_LABEL(application.label_version_item[compteur]), "");
        gtk_label_set_markup(GTK_LABEL(application.label_update_item[compteur]), "");
    }

    /* FLAGS */

    for(compteur = 0 ; compteur < nombre_element ; compteur++)
    {
        gtk_widget_set_state_flags(application.bouton_item_install[compteur], GTK_STATE_FLAG_INSENSITIVE, TRUE);
    }

    /* Box_pack  */
    gtk_container_add(GTK_CONTAINER(application.window), application.box_principale);
    gtk_container_add(GTK_CONTAINER(application.scrolled_window), application.box_items);

    gtk_box_pack_start(GTK_BOX(application.box_principale), application.scrolled_window, TRUE, TRUE, 5);
    gtk_box_pack_end(GTK_BOX(application.box_principale), application.box_bouton_quitter, FALSE, FALSE, 5);

    for(compteur = 0 ; compteur < nombre_element ; compteur++)
    {
        gtk_box_pack_start(GTK_BOX(application.box_items), application.box_principale_item[compteur], FALSE, FALSE, 5);
    }

    gtk_box_pack_start(GTK_BOX(application.box_bouton_quitter), application.bouton_quitter, FALSE, FALSE, 5);
    gtk_box_pack_end(GTK_BOX(application.box_bouton_quitter), application.bouton_update, FALSE, FALSE, 5);

    /* Items */

    for(compteur = 0 ; compteur < nombre_element ; compteur++)
    {
        gtk_box_pack_start(GTK_BOX(application.box_principale_item[compteur]), application.logo_item[compteur], FALSE, FALSE, 5);
        gtk_box_pack_start(GTK_BOX(application.box_principale_item[compteur]), application.box_item_info[compteur], FALSE, FALSE, 5);
        gtk_box_pack_start(GTK_BOX(application.box_principale_item[compteur]), application.box_item_install[compteur], FALSE, FALSE, 5);

        gtk_box_pack_start(GTK_BOX(application.box_item_install[compteur]), application.bouton_item_install[compteur], FALSE, FALSE, 5);

        gtk_box_pack_start(GTK_BOX(application.box_item_info[compteur]), application.label_version_item[compteur], FALSE, FALSE, 5);
        gtk_box_pack_start(GTK_BOX(application.box_item_info[compteur]), application.label_update_item[compteur], FALSE, FALSE, 5);
        gtk_box_pack_start(GTK_BOX(application.box_item_info[compteur]), application.progress_bar_item[compteur], FALSE, FALSE, 5);
    }

    /* Signaux  */
    g_signal_connect(application.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(application.bouton_quitter, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(application.bouton_update, "clicked", G_CALLBACK(update_fonction), NULL);

    for(compteur = 0 ; compteur < nombre_element ; compteur++)
    {
        g_signal_connect(application.bouton_item_install[compteur], "clicked", G_CALLBACK(install_fonction), NULL);
    }

    gtk_widget_show_all(application.window);

    gtk_main();

    return 0;
}
