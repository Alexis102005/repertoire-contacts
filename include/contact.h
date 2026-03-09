#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100
#define FICHIER "contacts.dat"

typedef struct {
    char nom[50];
    char prenom[50];
    char telephone[20];
    char email[50];
    char adresse[100];
} Contact;

void sauvegarder_contacts(Contact *contacts, int nb);
int charger_contacts(Contact *contacts);
void rechercher_contact(Contact *contacts, int nb);
int supprimer_contact(Contact *contacts, int nb);
#endif