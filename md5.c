#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <openssl/sha.h>
#include <glib.h>

#define SHA256_LONGUEUR 65

void sha256_hash_string(unsigned char hash[SHA256_DIGEST_LENGTH], char* chaine_retour)
{
    char* tampon = NULL;
    int i = 0;

    tampon = malloc(SHA256_LONGUEUR * sizeof(char));

    for(i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(tampon + (i * 2), "%02x", (unsigned char)hash[i]);
    }

    tampon[SHA256_LONGUEUR] = 0;

    g_snprintf(chaine_retour, 65, "%s", tampon);

    free(tampon);
}

char* sha256_fichier(char* chemin_fichier)
{
    FILE *fichier =  NULL;
    SHA256_CTX sha256;
    size_t BLOCK_SIZE = 32768;
    size_t bytesRead = 0;
    size_t longueur = 0;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned char *buffer = NULL;
	char *chaine = NULL;
    char tampon[1000];

    fichier = fopen(chemin_fichier, "rb");

    if(!fichier)
    {
        fprintf(stderr, "Ouverture du fichier impossible\n");
        chaine = NULL;
        return chaine;
    }

    buffer = malloc(BLOCK_SIZE);
    if(buffer == NULL)
    {
        fprintf(stderr, "Allocation memoire buffer impossible\n");
        chaine = NULL;
        return chaine;
    }

    SHA256_Init(&sha256);

    while((bytesRead = fread(buffer, 1, BLOCK_SIZE, fichier)))
    {
        SHA256_Update(&sha256, buffer, bytesRead);
    }

    SHA256_Final(hash, &sha256);
    sha256_hash_string(hash, tampon);

	longueur = strlen(tampon) + 1;
	if(!(chaine = malloc(longueur * sizeof(char))))
    {
        fprintf(stderr, "allocation memoire tampon impossible\n");
        chaine = NULL;
        return chaine;
    }

	memcpy(chaine, tampon, longueur);
    fclose(fichier);
    free(buffer);

    return chaine;
}

gboolean check_sha256sum(char* shasum_1, char* shasum_2)
{
    int i = 0;
    char str_1[SHA256_LONGUEUR];
    char str_2[SHA256_LONGUEUR];
    for(i = 0; i < SHA256_LONGUEUR; i++)
    {
        str_1[i] = toupper(shasum_1[i]);
        str_2[i] = toupper(shasum_2[i]);
    }
    if(strcmp(str_1, str_2) == 0)
        return TRUE;
    return FALSE;
}
