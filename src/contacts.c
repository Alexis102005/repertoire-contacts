#include <stdio.h>
#include <string.h>
#include "../include/contact.h"

void sauvegarder_contacts(Contact *contacts, int nb) {
    FILE *f = fopen(FICHIER, "wb");
    if (f == NULL) {
        printf("Erreur sauvegarde\n");
        return;
    }
    fwrite(&nb, sizeof(int), 1, f);
    fwrite(contacts, sizeof(Contact), nb, f);
    fclose(f);
}

int charger_contacts(Contact *contacts) {
    FILE *f = fopen(FICHIER, "rb");
    if (f == NULL) return 0;
    int nb = 0;
    fread(&nb, sizeof(int), 1, f);
    fread(contacts, sizeof(Contact), nb, f);
    fclose(f);
    return nb;
}void rechercher_contact(Contact *contacts, int nb) {
    char recherche[50];
    printf("Nom a rechercher : ");
    scanf("%49s", recherche);

    int trouve = 0;
    for (int i = 0; i < nb; i++) {
        if (strcmp(contacts[i].nom, recherche) == 0 ||
            strcmp(contacts[i].prenom, recherche) == 0) {
            printf("\n[%d] %s %s - %s - %s\n", i+1,
                contacts[i].prenom, contacts[i].nom,
                contacts[i].telephone, contacts[i].email);
            trouve = 1;
        }
    }
    if (!trouve) printf("Aucun contact trouve.\n");
}

int supprimer_contact(Contact *contacts, int nb) {
    int index;
    printf("Numero du contact a supprimer : ");
    scanf("%d", &index);
    index--;

    if (index < 0 || index >= nb) {
        printf("Numero invalide.\n");
        return nb;
    }
    for (int i = index; i < nb - 1; i++) {
        contacts[i] = contacts[i + 1];
    }
    printf("Contact supprime.\n");
    return nb - 1;
}