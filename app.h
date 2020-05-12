#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include <gtk/gtk.h>

#include "dl.h"
#include "resource.h"

#define nombre_element 11

#define TAILLE_MAX 1000

/*
    0 - novetat
    1 - Update
    2 - vlc
    3 - zip
    4 - notepad++
    5 - gimp
	6 - libreoffice
	7 - FileZilla
	8 - OpenShot
	9 - InnoSetup
   10 - Git
*/

typedef struct
{
  int id;
  GtkWidget* progress_bar;
  GtkWidget* bouton_update;
  GtkWidget* bouton_item_install;
} WorkerData;

typedef struct
{
    GtkWidget* window;
    GtkWidget* scrolled_window;

    GtkWidget* box_principale;
    GtkWidget* box_items;
    GtkWidget* box_bouton_quitter;

    GtkWidget* box_principale_item[nombre_element];
    GtkWidget* box_item_info[nombre_element];
    GtkWidget* box_item_install[nombre_element];

    GtkWidget* logo_item[nombre_element];
    GtkWidget* logo_install_item[nombre_element];

    GtkWidget* label_version_item[nombre_element];
    GtkWidget* label_update_item[nombre_element];

    GtkWidget* bouton_update;
    GtkWidget* bouton_quitter;

    GtkWidget* bouton_item_install[nombre_element];

    GtkWidget* progress_bar_item[nombre_element];

    gdouble progression;
}app;

static char tableau_id[nombre_element][TAILLE_MAX] = {"Novetat","Update","VLC","7zip", "Notepad++", "Gimp", "LibreOffice", "FileZilla", "OpenShot", "InnoSetup", "Git"};
static char icon_id[nombre_element][TAILLE_MAX] = {"Image/novetat.png","Image/update.png","Image/vlc.png", "Image/zip.png", "Image/note.png", "Image/gimp.png", "Image/libreoffice.png", "Image/filezilla.png", "Image/openshot.png", "Image/innosetup.png", "Image/git.png"};
static char exe_id[nombre_element][TAILLE_MAX] = {"novetat.exe","update.exe", "vlc_x64.exe", "zip_x64.exe", "note_x64.exe", "gimp_x64.exe", "libreoffice_x64.msi", "filezilla_x64.exe", "openshot_x64.exe", "innosetup_x64.exe", "git_x64.exe"};
static char dl_id[nombre_element][TAILLE_MAX] = {"DL/novetat.exe","DL/update.exe", "DL/vlc_x64.exe", "DL/zip_x64.exe", "DL/note_x64.exe", "DL/gimp_x64.exe", "DL/libreoffice_x64.msi", "DL/filezilla_x64.exe", "DL/openshot_x64.exe", "DL/innosetup_x64.exe", "DL/git_x64.exe"};

#endif // GUI_H_INCLUDED
