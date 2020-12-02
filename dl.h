#ifndef DL_H_INCLUDED
#define DL_H_INCLUDED
#include <gtk/gtk.h>

#define adresse_serveur "ftp://novetat:02122013Ed!@192.168.1.2:666"
#define ip_serveur "ftp://192.168.1.2"

#define update_exe "C:/ProgramData/update/update.exe"
#define novetat_folder "C:/ProgramData/update/novetat.exe"
#define dl_folder "DL"
#define conf_folder "conf"

#define db_server_filename "db_server.db"
#define db_client "conf/db_client.db"
#define db_server "conf/db_server.db"
#define db_tmp "DL/db_server.db"

int download_null(char *fichier);

void* download_progessbar(gpointer data);
void* fonction_md5(gpointer data);
void* fonction_md5_novetat();
gboolean pulse_fonction(void* ptr);

#endif // DL_H_INCLUDED
