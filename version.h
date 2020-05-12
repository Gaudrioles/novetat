#ifndef VERSION_H_INCLUDED
#define VERSION_H_INCLUDED

#include "app.h"

#define TAILLE_TEXTE 11

gchar* lecture_registre_wow64(char* cle_registre);
gchar* lecture_registre_classique(char* cle_registre);
gchar* get_chemin_complet(char* fichier_nom);
gchar* lecture_version_client(int id);

gboolean controle_installation(int id);

#endif // VERSION_H_INCLUDED
