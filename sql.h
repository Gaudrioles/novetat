#ifndef SQL_H_INCLUDED
#define SQL_H_INCLUDED

int creation_db_client();
int creation_db_server();

int initialisation_db_server(int id);
int initialisation_db_client(int id);

int update_db_client_version(int id, char* version);
int update_db_client_registre(int id, char* registre);
int update_db_server_version(int id, char* version);
int update_db_server_sha(int id, char* shasum);
int update_db_server_reg(int id, char* registre_key);
int update_db_server_reg(int id, char* registre_key);

gchar* lecture_db_client_version(int id);
gchar* lecture_db_server_version(int id);
gchar* lecture_db_server_sha(int id);
gchar* lecture_db_server_exe(int id);
gchar* lecture_chemin_registre(int id, char* db_sqlite);

#endif // SQL_H_INCLUDED
