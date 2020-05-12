#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED
#include <glib.h>

#define LOG_VERSION "2.0"
#define log_folder "logs"
#define log_file "logs/Erreur.log"

gboolean fichier_existe(char *fichier_nom);
gboolean repertoire_existe(char *repertoire_nom);

void creation_fichier_log(char *texte);

#endif // LOG_H_INCLUDED
