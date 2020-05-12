#include <windows.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "version.h"
#include "dl.h"
#include "sql.h"
#include "log.h"

#define BUFFER 8192

gboolean controle_installation(int id)
{
    gchar* registre_cle = NULL;
    gchar* version = NULL;
    gchar* version_server = NULL;

    registre_cle = lecture_chemin_registre(id, db_server);
    version_server = lecture_db_server_version(id);

    if(registre_cle == NULL ||version_server== NULL)
    {
        return FALSE;
    }

    version = lecture_registre_wow64(registre_cle);

    if(version != NULL)
    {
        if(strcmp(version, version_server) == 0)
        {
            g_free(registre_cle);
            g_free(version);
            g_free(version_server);
            return TRUE;
        }
        else
        {
            g_free(registre_cle);
            g_free(version);
            g_free(version_server);
            return FALSE;
        }

    }

    version = lecture_registre_classique(registre_cle);

    if(version != NULL)
    {
        if(strcmp(version, version_server) == 0)
        {
            g_free(registre_cle);
            g_free(version);
            g_free(version_server);
            return TRUE;
        }
        else
        {
            g_free(registre_cle);
            g_free(version);
            g_free(version_server);
            return FALSE;
        }

    }

    g_free(registre_cle);
    g_free(version);
    g_free(version_server);
    return FALSE;
}

gchar* get_chemin_complet(char* fichier_nom)
{
    gchar* chaine;
    gsize longueur = 0;
    char tampon[TAILLE_MAX] = {0};

    if(GetFullPathNameA(fichier_nom, TAILLE_MAX, tampon, NULL) != 0)
    {
        longueur = strlen(tampon) + 1;
        chaine = g_new(char, longueur);
        memcpy(chaine, tampon, longueur);

        return chaine;
    }

    chaine = NULL;
    return chaine;
}

gchar* lecture_registre_wow64(char* cle_registre)
{
    gchar* registre_adresse = NULL;
    gchar* chaine;
    gsize longueur = 0;
    char tampon[TAILLE_MAX];
    DWORD buffer = BUFFER;

    registre_adresse = g_strdup_printf("SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\%s", cle_registre);

    if((RegGetValue(HKEY_LOCAL_MACHINE,registre_adresse,"DisplayVersion",RRF_RT_ANY, NULL, (PVOID)tampon, &buffer)) == 0)
    {
        g_free(registre_adresse);
        longueur = strlen(tampon) + 1;
        chaine = g_new(char, longueur);
        memcpy(chaine, tampon, longueur);

        return chaine;
    }

    g_free(registre_adresse);
    chaine = NULL;
    return chaine;
}

gchar* lecture_registre_classique(char* cle_registre)
{
    gchar* registre_adresse = NULL;
    gchar* chaine;
    gsize longueur = 0;
    char tampon[TAILLE_MAX];
    DWORD buffer = BUFFER;

    registre_adresse = g_strdup_printf("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\%s", cle_registre);

    if((RegGetValue(HKEY_LOCAL_MACHINE,registre_adresse,"DisplayVersion",RRF_RT_ANY, NULL, (PVOID)tampon, &buffer)) == 0)
    {
        g_free(registre_adresse);
        longueur = strlen(tampon) + 1;
        chaine = g_new(char, longueur);
        memcpy(chaine, tampon, longueur);

        return chaine;
    }

    g_free(registre_adresse);
    chaine = NULL;
    return chaine;
}

gchar* lecture_version_client(int id)
{
    gchar* tampon = NULL;
    gchar* registre_cle = NULL;
    gchar* chaine;
    gsize longueur = 0;

    registre_cle = lecture_chemin_registre(id, db_client);

    tampon = lecture_registre_wow64(registre_cle);

    if(tampon != NULL)
    {
        longueur = strlen(tampon) + 1;
        chaine = g_new(char, longueur);
        memcpy(chaine, tampon, longueur);

        g_free(registre_cle);
        g_free(tampon);

        return chaine;
    }

    tampon = lecture_registre_classique(registre_cle);

    if(tampon != NULL)
    {
        longueur = strlen(tampon) + 1;
        chaine = g_new(char, longueur);
        memcpy(chaine, tampon, longueur);

        g_free(registre_cle);
        g_free(tampon);

        return chaine;
    }

    tampon = lecture_db_client_version(id);

    if(tampon != NULL)
    {
        longueur = strlen(tampon) + 1;
        chaine = g_new(char, longueur);
        memcpy(chaine, tampon, longueur);

        g_free(registre_cle);
        g_free(tampon);

        gchar* error = NULL;
        error = g_strdup_printf("Novetat: %s Lecture Registre impossible %s",APP_VERSION, tableau_id[id]);
        creation_fichier_log(error);
        g_free(error);

        return chaine;
    }

    tampon = g_strdup("Error");

    longueur = strlen(tampon) + 1;
    chaine = g_new(char, longueur);
    memcpy(chaine, tampon, longueur);

    g_free(registre_cle);
    g_free(tampon);

    return chaine;
}
