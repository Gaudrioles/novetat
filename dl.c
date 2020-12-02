#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <math.h>
#include <gtk/gtk.h>

#include "version.h"
#include "md5.h"
#include "log.h"
#include "app.h"
#include "dl.h"
#include "gui_fonction.h"
#include "sql.h"
#include "win32.h"
#include "label.h"

static GCond g_condition[nombre_element];
static GMutex g_mutex[nombre_element];
static GMutex g_mutex_pbar[nombre_element];

gboolean pulse_fonction(void* ptr)
{
    WorkerData* wd = ptr;

    g_mutex_lock(&g_mutex_pbar[wd->id]);

    if(wd->valeur > 0)
    {
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(wd->progress_bar), wd->valeur);
    }

    g_mutex_unlock(&g_mutex_pbar[wd->id]);

    if(wd->valeur == 1)
    {
        return FALSE;
    }

    return TRUE;
}

struct FtpFile
{
    const char *filename;
    FILE *stream;
};

static size_t my_fwrite(void *buffer, size_t size, size_t nmemb, void *stream)
{
    struct FtpFile *out = (struct FtpFile *)stream;
	char emplacement[TAILLE_MAX];
    if(out && !out->stream)
    {
        sprintf(emplacement, "%s/%s",dl_folder,out->filename);
        out->stream = fopen(emplacement, "wb");
        if(!out->stream)
        {
            gchar* error = NULL;

            error = g_strdup_printf("Novetat : %s impossible ecrire my_fwrite", APP_VERSION);
            creation_fichier_log(error);
            g_free(error);
            return -1;
        }
    }
    return fwrite(buffer, size, nmemb, out->stream);
}

int fonction_progression(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded)
{
    WorkerData* wd = ptr;

    g_mutex_lock(&g_mutex_pbar[wd->id]);
    wd->valeur =  NowDownloaded / TotalToDownload;
    g_mutex_unlock(&g_mutex_pbar[wd->id]);

    return 0;
}

int download_null(char *fichier)
{
    CURL* curl;
    CURLcode res;
    gchar* ip = NULL;

    ip = g_strdup_printf("%s/%s",adresse_serveur, fichier);

    struct FtpFile ftpfile = {fichier, NULL};

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();

    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL,ip);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, FALSE);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
        curl_easy_setopt(curl, CURLOPT_FTP_RESPONSE_TIMEOUT, 1L);

        res = curl_easy_perform(curl);

        curl_easy_cleanup(curl);

        if(CURLE_OK != res)
        {
            gchar* erreur = NULL;

            erreur = g_strdup_printf("Novetat : %s Téléchargement impossible -> dl.c :: %s download_null curl_code:%d",APP_VERSION, fichier, res);
            creation_fichier_log(erreur);
            g_free(erreur);

            curl_global_cleanup();
            g_free(ip);
            return -1;
        }
    }

    if(ftpfile.stream)
        fclose(ftpfile.stream);

    curl_global_cleanup();
    g_free(ip);

    return 0;
}

void* download_progessbar(gpointer data)
{
    CURL* curl;

    gchar* ip = NULL;

    WorkerData* wd = data;

    struct FtpFile ftpfile = {exe_id[wd->id], NULL};

    ip = g_strdup_printf("%s/%s",adresse_serveur , exe_id[wd->id]);

    curl = curl_easy_init();
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL,ip);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, FALSE);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
        curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, fonction_progression);
        curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, data);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
        curl_easy_setopt(curl, CURLOPT_FTP_RESPONSE_TIMEOUT, 1L);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    if(ftpfile.stream)
        fclose(ftpfile.stream);

    curl_global_cleanup();
    g_free(ip);

    g_usleep(1000000);

    g_mutex_lock(&g_mutex[wd->id]);
    g_cond_signal(&g_condition[wd->id]);
    g_mutex_unlock(&g_mutex[wd->id]);

    return NULL;
}

void* fonction_md5(gpointer data)
{
    gchar* chemin_executable = NULL;
    gchar* tampon = NULL;
    gchar* executable_type = NULL;
    gchar* server_sha = NULL;
    char* sha = NULL;

    WorkerData* wd = data;

    g_mutex_lock(&g_mutex[wd->id]);
    g_cond_wait(&g_condition[wd->id], &g_mutex[wd->id]);
    g_mutex_unlock(&g_mutex[wd->id]);

    sha = sha256_fichier(dl_id[wd->id]);
    executable_type = lecture_db_server_exe(wd->id);
    server_sha = lecture_db_server_sha(wd->id);

    if(sha == NULL || executable_type == NULL || server_sha == NULL)
    {
        g_free(wd);
        return NULL;
    }

    if(check_sha256sum(sha, server_sha) == TRUE)
    {
        chemin_executable = get_chemin_complet(dl_id[wd->id]);

        if(strcmp(executable_type, "MSI") == 0)
        {
            execution_msi(chemin_executable);
        }
        else
        {
            execution_exe(chemin_executable);
        }

        if(controle_installation(wd->id) == TRUE)
        {
            tampon = lecture_chemin_registre(wd->id,db_server);
            update_db_client_registre(wd->id, tampon);
            g_free(tampon);
            tampon = lecture_db_server_version(wd->id);
            update_db_client_version(wd->id, tampon);
            mise_en_forme_label_version(wd->label_version_item, tampon, wd->id);
            g_free(tampon);
            update_disponible(wd->label_update_item , 0);
            gtk_widget_set_state_flags(wd->bouton_item_install, GTK_STATE_FLAG_INSENSITIVE, TRUE);
        }
    }
    else
    {
        gchar* error;
        error = g_strdup_printf("Novetat : %s gui_fonction.c::fonction_md5 %s -> erreur sha256sum",APP_VERSION, tableau_id[wd->id]);
        creation_fichier_log(error);
        g_free(error);
        gtk_widget_unset_state_flags(wd->bouton_update, GTK_STATE_FLAG_INSENSITIVE);
    }

    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(wd->progress_bar), 0.0);

    g_free(chemin_executable);
    g_free(server_sha);
    free(sha);
    g_free(wd);

    return NULL;
}

void* fonction_md5_novetat(gpointer data)
{
    char* sha = NULL;
    gchar* server_sha = NULL;
    gchar* server_version = NULL;
    gchar* server_registre = NULL;

    WorkerData *wd = data;

    g_mutex_lock(&g_mutex[wd->id]);
    g_cond_wait(&g_condition[wd->id], &g_mutex[wd->id]);
    g_mutex_unlock(&g_mutex[wd->id]);

    sha = sha256_fichier(dl_id[wd->id]);
    server_sha = lecture_db_server_sha(wd->id);
    server_version = lecture_db_server_version(wd->id);
    server_registre = lecture_chemin_registre(wd->id, db_server);

    if(server_sha == NULL || sha == NULL || server_version == NULL || server_registre == NULL)
    {
        g_free(wd);
        return NULL;
    }

    if(check_sha256sum(sha, server_sha) == TRUE)
    {
        update_db_client_version(0, server_version);
        server_registre = lecture_chemin_registre(wd->id,db_server);
        update_db_client_registre(wd->id, server_registre);

        remove(novetat_folder);

        rename(dl_id[wd->id], novetat_folder);

        Sleep(10);

        if(fichier_existe(novetat_folder) != TRUE)
        {
            return NULL;
        }

        system(update_exe);
        free(sha);
        g_free(server_sha);
        g_free(server_version);
        g_free(server_registre);
        g_free(wd);

        gtk_main_quit();

        return NULL;
    }
    else
    {
        gchar* error;

        error = g_strdup_printf("Novetat : %s gui_fonction.c::fonction_md5 %s -> erreur sha256sum",APP_VERSION, tableau_id[0]);
        creation_fichier_log(error);

        g_free(error);
        free(sha);
        g_free(server_sha);
        g_free(server_version);
        g_free(server_registre);
        g_free(wd);

        return NULL;
    }

    return NULL;
}
