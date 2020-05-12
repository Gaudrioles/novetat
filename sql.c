#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "app.h"
#include "resource.h"

int creation_db_server()
{
    sqlite3* db;
    char* err_msg = 0;
    gchar* sql = NULL;

    int rc = sqlite3_open(db_server, &db);

    if (rc != SQLITE_OK)
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("%s Ouverture database impossible: %s",APP_VERSION, sqlite3_errmsg(db));

        creation_fichier_log(err_message);
        sqlite3_close(db);
        g_free(err_message);
        return -1;
    }

    sql = g_strdup( "DROP TABLE IF EXISTS APPS;"\
                    "CREATE TABLE APPS(ID INT, NAME TEXT, VERS TEXT, SHA TEXT, REG TEXT, EXE TEXT);");

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    sqlite3_free(err_msg);
    sqlite3_close(db);

    g_free(sql);

    return 0;
}

int initialisation_db_server(int id)
{
    sqlite3* db;
    char* err_msg = 0;
    gchar* sql = NULL;

    int rc = sqlite3_open(db_server, &db);

    if (rc != SQLITE_OK)
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("%s Ouverture database impossible: %s",APP_VERSION, sqlite3_errmsg(db));

        creation_fichier_log(err_message);
        sqlite3_close(db);
        g_free(err_message);
        return -1;
    }

    sql = g_strdup_printf("INSERT INTO APPS VALUES(%d, '%s', '%s','%s', '%s', '%s');", id, tableau_id[id],"VERSION", "SHA_256", "REG", "EXE");

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    sqlite3_free(err_msg);
    sqlite3_close(db);

    g_free(sql);

    return 0;
}


int creation_db_client()
{
    sqlite3* db;
    char* err_msg = NULL;
    gchar* sql = NULL;

    int rc = sqlite3_open(db_client, &db);

    if (rc != SQLITE_OK)
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("%s Ouverture database impossible: %s",APP_VERSION, sqlite3_errmsg(db));

        creation_fichier_log(err_message);
        sqlite3_close(db);
        g_free(err_message);
        return -1;
    }

    sql = g_strdup( "DROP TABLE IF EXISTS APPS;"\
                    "CREATE TABLE APPS(ID INT, NAME TEXT, VERS TEXT, REG TEXT);");

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK )
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("%s SQL error: %s",APP_VERSION, err_msg);

        creation_fichier_log(err_message);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        g_free(err_message);
        g_free(sql);
        return -1;
    }

    g_free(sql);

    sqlite3_free(err_msg);
    sqlite3_close(db);

    return 0;
}

int initialisation_db_client(int id)
{
    sqlite3* db;
    char* err_msg = 0;
    gchar* sql = NULL;

    int rc = sqlite3_open(db_client, &db);

    if (rc != SQLITE_OK)
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("%s Ouverture database impossible: %s",APP_VERSION, sqlite3_errmsg(db));

        creation_fichier_log(err_message);
        sqlite3_close(db);
        g_free(err_message);
        return -1;
    }

    sql = g_strdup_printf("INSERT INTO APPS VALUES(%d, '%s', '%s','%s');", id, tableau_id[id],"Not Installed", "REG");

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    sqlite3_free(err_msg);
    sqlite3_close(db);

    g_free(sql);

    return 0;
}

int update_db_client_version(int id, char* version)
{
    sqlite3* db;
    gchar* sql = NULL;
    char* err_msg = NULL;

    int rc = sqlite3_open(db_client, &db);

    if (rc != SQLITE_OK)
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("%s Ouverture database impossible: %s", APP_VERSION, sqlite3_errmsg(db));

        creation_fichier_log(err_message);
        sqlite3_close(db);
        g_free(err_message);
        return -1;
    }

    sql = g_strdup_printf("UPDATE APPS SET VERS = '%s' WHERE ID = %d;",version, id);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK )
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("%s SQL error: %s", APP_VERSION, err_msg);

        creation_fichier_log(err_message);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        g_free(err_message);
        g_free(sql);
        return -1;
    }

    sqlite3_close(db);
    g_free(sql);
    return 0;
}

int update_db_client_registre(int id, char* registre)
{
    sqlite3* db;
    gchar* sql = NULL;
    char* err_msg = NULL;

    int rc = sqlite3_open(db_client, &db);

    if (rc != SQLITE_OK)
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("%s Ouverture database impossible: %s", APP_VERSION, sqlite3_errmsg(db));

        creation_fichier_log(err_message);
        sqlite3_close(db);
        g_free(err_message);
        return -1;
    }

    sql = g_strdup_printf("UPDATE APPS SET REG = '%s' WHERE ID = %d;",registre, id);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK )
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("%s SQL error: %s", APP_VERSION, err_msg);

        creation_fichier_log(err_message);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        g_free(err_message);
        g_free(sql);
        return -1;
    }

    sqlite3_close(db);
    g_free(sql);
    return 0;
}

gchar* lecture_db_client_version(int id)
{
    gchar* sql = NULL;
    gchar* chaine;
    gchar* tampon = NULL;
    gsize longueur = 0;
    char* err_msg = NULL;
    sqlite3* db;
    sqlite3_stmt* res;

    int rc = sqlite3_open(db_client, &db);

    if (rc != SQLITE_OK)
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("%s Ouverture database impossible: %s", APP_VERSION, sqlite3_errmsg(db));

        creation_fichier_log(err_message);
        sqlite3_close(db);
        g_free(err_message);
        chaine = NULL;
        return chaine;
    }

    sql = g_strdup_printf("SELECT VERS FROM APPS WHERE ID = %d;", id);

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

  	if (rc != SQLITE_OK )
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("%s SQL error: %s", APP_VERSION, err_msg);

        creation_fichier_log(err_message);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        g_free(err_message);
        g_free(sql);
        chaine = NULL;
        return chaine;
    }

    int step = sqlite3_step(res);

    if (step == SQLITE_ROW)
    {
        tampon = g_strdup_printf("%s", sqlite3_column_text(res, 0));
    }

    if(tampon == NULL)
    {
        chaine = NULL;
        return chaine;
    }

    longueur = strlen(tampon) + 1;
    chaine = g_new(char, longueur);
    memcpy(chaine, tampon, longueur);

    sqlite3_finalize(res);
    sqlite3_close(db);
    g_free(sql);
    g_free(tampon);

    return chaine;
}

int update_db_server_version(int id, char* version)
{
    sqlite3* db;
    gchar* sql = NULL;
    char* err_msg = 0;

    int rc = sqlite3_open(db_server, &db);

    if (rc != SQLITE_OK)
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("%s Ouverture database impossible: %s", APP_VERSION, sqlite3_errmsg(db));

        creation_fichier_log(err_message);
        sqlite3_close(db);
        g_free(err_message);
        return -1;
    }

    sql = g_strdup_printf("UPDATE APPS SET VERS = '%s' WHERE ID = %d;",version, id);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK )
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("%s SQL error: %s", APP_VERSION, err_msg);

        creation_fichier_log(err_message);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        g_free(err_message);
        g_free(sql);
        return -1;
    }

    sqlite3_close(db);
    g_free(sql);
    return 0;
}

int update_db_server_sha(int id, char* shasum)
{

    sqlite3* db;
    gchar* sql = NULL;
    char* err_msg = 0;

    int rc = sqlite3_open(db_server, &db);

    if (rc != SQLITE_OK)
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("%s Ouverture database impossible: %s", APP_VERSION, sqlite3_errmsg(db));

        creation_fichier_log(err_message);
        sqlite3_close(db);
        g_free(err_message);
        return -1;
    }

    sql = g_strdup_printf("UPDATE APPS SET SHA = '%s' WHERE ID = %d;",shasum, id);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK )
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("%s SQL error: %s", APP_VERSION, err_msg);

        creation_fichier_log(err_message);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        g_free(err_message);
        g_free(sql);
        return -1;
    }

    sqlite3_close(db);
    g_free(sql);
    return 0;
}

int update_db_server_reg(int id, char* registre_key)
{

    sqlite3* db;
    gchar* sql = NULL;
    char* err_msg = 0;

    int rc = sqlite3_open(db_server, &db);

    if (rc != SQLITE_OK)
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("%s Ouverture database impossible: %s", APP_VERSION, sqlite3_errmsg(db));

        creation_fichier_log(err_message);
        sqlite3_close(db);
        g_free(err_message);
        return -1;
    }

    sql = g_strdup_printf("UPDATE APPS SET REG = '%s' WHERE ID = %d;", registre_key, id);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK )
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("%s SQL error: %s", APP_VERSION, err_msg);

        creation_fichier_log(err_message);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        g_free(err_message);
        g_free(sql);
        return -1;
    }

    sqlite3_close(db);
    g_free(sql);
    return 0;
}

int update_db_server_exe(int id, char* exe_type)
{

    sqlite3* db;
    gchar* sql = NULL;
    char* err_msg = 0;

    int rc = sqlite3_open(db_server, &db);

    if (rc != SQLITE_OK)
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("%s Ouverture database impossible: %s", APP_VERSION, sqlite3_errmsg(db));

        creation_fichier_log(err_message);
        sqlite3_close(db);
        g_free(err_message);
        return -1;
    }

    sql = g_strdup_printf("UPDATE APPS SET EXE = '%s' WHERE ID = %d;", exe_type, id);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK )
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("%s SQL error: %s", APP_VERSION, err_msg);

        creation_fichier_log(err_message);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        g_free(err_message);
        g_free(sql);
        return -1;
    }

    sqlite3_close(db);
    g_free(sql);
    return 0;
}

gchar* lecture_db_server_version(int id)
{
    sqlite3* db;
    sqlite3_stmt* res;
    char* err_msg = NULL;
    gchar* sql = NULL;
    gchar* tampon = NULL;
    gchar* chaine;
    gsize longueur = 0;

    int rc = sqlite3_open(db_server, &db);

    if (rc != SQLITE_OK)
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("Ouverture database impossible: %s", sqlite3_errmsg(db));

        creation_fichier_log(err_message);
        sqlite3_close(db);
        g_free(err_message);
        chaine = NULL;
        return chaine;
    }

    sql = g_strdup_printf("SELECT VERS FROM APPS WHERE ID = %d;", id);

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

  	if (rc != SQLITE_OK )
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("SQL error: %s", err_msg);

        creation_fichier_log(err_message);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        g_free(err_message);
        g_free(sql);
        chaine = NULL;
        return chaine;
    }

    int step = sqlite3_step(res);

    if (step == SQLITE_ROW)
    {
       tampon = g_strdup_printf("%s", sqlite3_column_text(res, 0));
    }
    if(tampon == NULL)
    {
        chaine = NULL;
        return chaine;
    }

    longueur = strlen(tampon) + 1;
    chaine = g_new(char, longueur);
    memcpy(chaine, tampon, longueur);

    sqlite3_finalize(res);
    sqlite3_close(db);
    g_free(sql);
    g_free(tampon);

    return chaine;
}

gchar* lecture_db_server_sha(int id)
{

    sqlite3* db;
    sqlite3_stmt* res;
    char* err_msg = NULL;
    gchar* sql = NULL;
    gchar* tampon = NULL;
    gchar* chaine;
    gsize longueur = 0;

    int rc = sqlite3_open(db_server, &db);

    if (rc != SQLITE_OK)
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("Ouverture database impossible: %s", sqlite3_errmsg(db));

        creation_fichier_log(err_message);
        sqlite3_close(db);
        g_free(err_message);
        chaine = NULL;
        return chaine;
    }

    sql = g_strdup_printf("SELECT SHA FROM APPS WHERE ID = %d;", id);

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

  	if (rc != SQLITE_OK )
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("SQL error: %s", err_msg);

        creation_fichier_log(err_message);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        g_free(err_message);
        g_free(sql);
        chaine = NULL;
        return chaine;
    }

    int step = sqlite3_step(res);

    if (step == SQLITE_ROW)
    {
       tampon =  g_strdup_printf("%s", sqlite3_column_text(res, 0));
    }

    if(tampon == NULL)
    {
        chaine = NULL;
        return chaine;
    }

    longueur = strlen(tampon) + 1;
    chaine = g_new(char, longueur);
    memcpy(chaine, tampon, longueur);

    sqlite3_finalize(res);
    sqlite3_close(db);
    g_free(sql);
    g_free(tampon);

    return chaine;
}

gchar* lecture_db_server_exe(int id)
{

    sqlite3* db;
    sqlite3_stmt* res;
    char* err_msg = NULL;
    gchar* sql = NULL;
    gchar* tampon = NULL;
    gchar* chaine;
    gsize longueur = 0;

    int rc = sqlite3_open(db_server, &db);

    if (rc != SQLITE_OK)
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("Ouverture database impossible: %s", sqlite3_errmsg(db));

        creation_fichier_log(err_message);
        sqlite3_close(db);
        g_free(err_message);
        chaine = NULL;
        return chaine;
    }

    sql = g_strdup_printf("SELECT EXE FROM APPS WHERE ID = %d;", id);

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

  	if (rc != SQLITE_OK )
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("SQL error: %s", err_msg);

        creation_fichier_log(err_message);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        g_free(err_message);
        g_free(sql);
        chaine = NULL;
        return chaine;
    }

    int step = sqlite3_step(res);

    if (step == SQLITE_ROW)
    {
       tampon =  g_strdup_printf("%s", sqlite3_column_text(res, 0));
    }

    if(tampon == NULL)
    {
        chaine = NULL;
        return chaine;
    }

    longueur = strlen(tampon) + 1;
    chaine = g_new(char, longueur);
    memcpy(chaine, tampon, longueur);

    sqlite3_finalize(res);
    sqlite3_close(db);
    g_free(sql);
    g_free(tampon);

    return chaine;
}


gchar* lecture_chemin_registre(int id, char* db_sqlite)
{

    sqlite3* db;
    sqlite3_stmt* res;
    char* err_msg = NULL;
    gchar* sql = NULL;
    gchar* tampon = NULL;
    gchar* chaine;
    gsize longueur = 0;


    int rc = sqlite3_open(db_sqlite, &db);

    if (rc != SQLITE_OK)
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("%s Ouverture database impossible: %s", APP_VERSION, sqlite3_errmsg(db));

        creation_fichier_log(err_message);
        sqlite3_close(db);
        g_free(err_message);
        chaine = NULL;
        return chaine;
    }

    sql = g_strdup_printf("SELECT REG FROM APPS WHERE ID = %d;", id);

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

  	if (rc != SQLITE_OK )
    {
        gchar* err_message = NULL;

        err_message = g_strdup_printf("%s SQL error: %s", APP_VERSION, err_msg);

        creation_fichier_log(err_message);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        g_free(err_message);
        g_free(sql);
        chaine = NULL;
        return chaine;
    }

    int step = sqlite3_step(res);

    if (step == SQLITE_ROW)
    {
        tampon = g_strdup_printf("%s", sqlite3_column_text(res, 0));
    }

    if(tampon == NULL)
    {
        chaine = NULL;
        return chaine;
    }

    longueur = strlen(tampon) + 1;
    chaine = g_new(char, longueur);
    memcpy(chaine, tampon, longueur);


    sqlite3_finalize(res);
    sqlite3_close(db);
    g_free(sql);
    g_free(tampon);

    return chaine;
}
