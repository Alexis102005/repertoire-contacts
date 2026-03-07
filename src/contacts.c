#include <stdio.h>
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
}