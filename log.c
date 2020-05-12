#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <dirent.h>
#include <glib.h>

#include "log.h"

gboolean fichier_existe(char *fichier_nom)
{
    FILE *fichier = NULL;

    fichier = fopen(fichier_nom, "r");
    if(fichier == NULL)
        return FALSE;

    fclose(fichier);
    return TRUE;
}

gboolean repertoire_existe(char *repertoire_nom)
{
    DIR *repertoire = NULL;

    repertoire = opendir(repertoire_nom);
    if(repertoire == NULL)
        return FALSE;
    
    closedir(repertoire);

    return TRUE;
}


void creation_fichier_log(char *texte)
{
    char format[128];
    time_t temps;
    struct tm date;
    FILE *fichier = NULL;

    time(&temps);
    date=*localtime(&temps);
    
    strftime(format, 128, "%c", &date);

    if(repertoire_existe(log_folder) != TRUE)
        g_mkdir_with_parents(log_folder, 0777);
    
    if(fichier_existe(log_file) != TRUE)
    {
        fichier = fopen(log_file, "w+");
    
        if(fichier != NULL)
        {
            fprintf(fichier, "---------------------------------------------\n-----        Système de Log File        -----\n-----             Version %s           -----\n---------------------------------------------\n\n", LOG_VERSION);
            fprintf(fichier, "*********************************************\n\n");
            fprintf(fichier, "Date ->\t\t%s\n\n", format);
            fprintf(fichier, "Message ->\t%s\n\n", texte);
            fclose(fichier);
            return;
        }
        else
        {
            return;
        }
    }
    else
    {
        fichier = fopen(log_file, "a+");
        if (fichier != NULL)
        {
            fprintf(fichier,"*********************************************\n\n");
            fprintf(fichier, "Date ->\t\t%s\n\n", format);
            fprintf(fichier, "Message ->\t%s\n\n", texte);
            fclose(fichier);
            return;
        }
        else
        {
            return;
        }        
    }

    return;
}
