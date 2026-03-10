#ifndef CONTACT_H
#define CONTACT_H

#include <sqlite3.h>

#define MAX_CONTACTS 100

typedef struct {
    int id;
    char nom[50];
    char prenom[50];
    char telephone[20];
    char email[50];
    char adresse[100];
} Contact;

sqlite3* ouvrir_db();
void fermer_db(sqlite3 *db);
void ajouter_contact(sqlite3 *db, Contact *c);
int charger_contacts(sqlite3 *db, Contact *contacts);
void rechercher_contact(sqlite3 *db, const char *recherche);
void supprimer_contact(sqlite3 *db, int id);

#endif