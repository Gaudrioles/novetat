#ifndef MD5_H_INCLUDED
#define MD5_H_INCLUDED
#include <glib.h>

char* sha256_fichier(char* chemin_fichier);
gboolean check_sha256sum(char* shasum_1, char* shasum_2);

#endif // MD5_H_INCLUDED
