#ifndef GUI_FONCTION_H_INCLUDED
#define GUI_FONCTION_H_INCLUDED

#include "version.h"

void install_fonction(GtkWidget* bouton, gpointer data);
void update_fonction(GtkWidget* bouton, gpointer data);
void start_thread_download(int id, gpointer data);
void start_thread_install(int id, gpointer data);

#endif // GUI_FONCTION_H_INCLUDED
