#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>

#include "md5.h"
#include "app.h"
#include "dl.h"
#include "log.h"
#include "version.h"
#include "gui_fonction.h"
#include "sql.h"
#include "label.h"

gboolean fonction_initialisation()
{
    gchar* erreur = NULL;

    if(repertoire_existe(dl_folder) != TRUE)
    {
        if(g_mkdir_with_parents(dl_folder, 0777) != 0)
        {
            erreur = g_strdup_printf("%s gui_fonction.c -> fonction_initialisation -> creation dl_folder impossible", APP_VERSION);
            creation_fichier_log(erreur);
            g_free(erreur);
            return FALSE;
        }
    }

    if(repertoire_existe(conf_folder) != TRUE)
    {
        if(g_mkdir_with_parents(conf_folder, 0777) != 0)
        {
            erreur = g_strdup_printf("%s gui_fonction.c -> fonction_initialisation -> creation conf_folder impossible", APP_VERSION);
            creation_fichier_log(erreur);
            g_free(erreur);
            return FALSE;
        }
    }

    if(fichier_existe(db_client) != TRUE)
    {
        if(creation_db_client() != 0)
        {
            erreur = g_strdup_printf("%s gui_fonction.c -> fonction_initialisation -> creation db_client impossible", APP_VERSION);
            creation_fichier_log(erreur);
            g_free(erreur);
            return FALSE;
        }
        else
        {
            int compteur = 0;

            for(compteur = 0; compteur < nombre_element; compteur++)
            {
                if(initialisation_db_client(compteur) != 0)
                {
                    erreur = g_strdup_printf("%s gui_fonction.c -> fonction_initialisation -> initialisation db_client impossible", APP_VERSION);
                    creation_fichier_log(erreur);
                    g_free(erreur);
                    return FALSE;
                }
            }
        }

    }

    return TRUE;
}

int get_id_from_name(char* nom)
{
    int compteur = 0;

    for(compteur = 0; compteur < nombre_element; compteur++)
    {
        if(strcmp(tableau_id[compteur], nom) == 0)
        {
            return compteur;
        }
    }
    return -1;
}

int download_db_fonction()
{
    if(download_null(db_server_filename) == 0)
    {
        if(remove(db_server) == 0)
        {
            if(rename(db_tmp, db_server) == -1)
            {
                gchar* error = NULL;

                error = g_strdup_printf("Novetat: %s Erreur download_db_fonction::rename -> gui_fonction.c", APP_VERSION);
                creation_fichier_log(error);
                g_free(error);
            }
        }
        else
        {
            if(rename(db_tmp, db_server) == -1)
            {
                gchar* error = NULL;

                error = g_strdup_printf("Novetat: %s Erreur download_db_fonction::rename -> gui_fonction.c", APP_VERSION);
                creation_fichier_log(error);
                g_free(error);
            }
        }
    }
    else
        return -1;

    return 0;
}

void update_fonction(GtkWidget* bouton, gpointer data)
{
    int compteur = 0;

    app* application =  data;

    cleaner_fonction(data);

    if(fonction_initialisation() != TRUE)
    {
        return;
    }

    if(download_db_fonction() == 0)
    {
        gchar* tampon_version_client = NULL;
        gchar* tampon_version_server = NULL;

        for(compteur = 0 ; compteur < nombre_element ; compteur++)
        {
            tampon_version_client = lecture_version_client(compteur);
            if(tampon_version_client == NULL)
                return;

            mise_en_forme_label_version(application->label_version_item[compteur], tampon_version_client, compteur);
            g_free(tampon_version_client);
        }

        for(compteur = 0 ; compteur < nombre_element ; compteur++)
        {
            tampon_version_client = lecture_version_client(compteur);
            tampon_version_server = lecture_db_server_version(compteur);

            if(tampon_version_client == NULL || tampon_version_server == NULL)
                return;

            if(strcmp(tampon_version_client, tampon_version_server) == 0)
            {
                update_disponible(application->label_update_item[compteur], 0);
                gtk_widget_set_state_flags(application->bouton_item_install[compteur], GTK_STATE_FLAG_INSENSITIVE, TRUE);
            }
            else
            {
                update_disponible(application->label_update_item[compteur], 1);
                gtk_widget_unset_state_flags(application->bouton_item_install[compteur], GTK_STATE_FLAG_INSENSITIVE);
            }

            g_free(tampon_version_client);
            g_free(tampon_version_server);
        }

    }
    else
    {
        gchar* tampon = g_strdup_printf("<span font_family=\"Verdana\" font=\"8\" color=\"red\"><b>Connexion impossible</b></span>");

        for(compteur = 0 ; compteur < nombre_element ; compteur++)
        {
            gtk_label_set_markup(GTK_LABEL(application->label_update_item[compteur]), tampon);
        }

        g_free(tampon);
    }
}

void install_fonction(GtkWidget* bouton, gpointer data)
{
    int id = 0;
    const gchar* tampon = NULL;
    WorkerData* wd;
    app * application = data;

    wd = g_malloc(sizeof *wd);

    curl_global_init(CURL_GLOBAL_DEFAULT);

    tampon = gtk_widget_get_name(bouton);
    id = get_id_from_name((char*)tampon);
    if(id == -1)
        return;

    wd->id = id;
    wd->progress_bar = application->progress_bar_item[id];
    wd->bouton_update = application->bouton_update;
    wd->bouton_item_install = application->bouton_item_install[id];
    wd->label_update_item = application->label_update_item[id];
    wd->label_version_item = application->label_version_item[id];
    wd->valeur = 0.0;

    gtk_widget_set_state_flags(application->bouton_update, GTK_STATE_FLAG_INSENSITIVE, TRUE);

    g_timeout_add(50, pulse_fonction, wd);
    start_thread_install(id, wd);
    start_thread_download(id, wd);

    gtk_widget_unset_state_flags(application->bouton_update, GTK_STATE_FLAG_INSENSITIVE);

    return;
}

void start_thread_download(int id, gpointer data)
{
    GThread* thread;

    WorkerData* wd = data;

    remove(dl_id[id]);

    gtk_widget_set_state_flags(wd->bouton_item_install, GTK_STATE_FLAG_INSENSITIVE, TRUE);

    thread = g_thread_new("Thread_d",download_progessbar, data);

    g_thread_unref(thread);

    return ;
}

void start_thread_install(int id, gpointer data)
{
    GThread* thread;

    WorkerData* wd = data;

    if(id != 0)
    {
        thread = g_thread_new("Thread_m",fonction_md5, wd);
    }
    else
    {
        thread = g_thread_new("Thread_m",fonction_md5_novetat, wd);
    }

    g_thread_unref(thread);

    return;
}
