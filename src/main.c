#include <stdio.h>
#include "../include/contact.h"

int main() {
    sqlite3 *db = ouvrir_db();
    Contact contacts[MAX_CONTACTS];
    int choix;

    while (1) {
        printf("\n=== Repertoire de Contacts ===\n");
        printf("1. Ajouter un contact\n");
        printf("2. Afficher tous les contacts\n");
        printf("3. Rechercher un contact\n");
        printf("4. Supprimer un contact\n");
        printf("5. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        if (choix == 1) {
            Contact c = {0};
            printf("Nom : "); scanf("%49s", c.nom);
            printf("Prenom : "); scanf("%49s", c.prenom);
            printf("Telephone : "); scanf("%19s", c.telephone);
            printf("Email : "); scanf("%49s", c.email);
            ajouter_contact(db, &c);

        } else if (choix == 2) {
            int nb = charger_contacts(db, contacts);
            if (nb == 0) { printf("Aucun contact.\n"); continue; }
            for (int i = 0; i < nb; i++) {
                printf("\n[%d] %s %s - %s - %s\n",
                    contacts[i].id, contacts[i].prenom,
                    contacts[i].nom, contacts[i].telephone,
                    contacts[i].email);
            }

        } else if (choix == 3) {
            char recherche[50];
            printf("Rechercher : "); scanf("%49s", recherche);
            rechercher_contact(db, recherche);

        } else if (choix == 4) {
            int id;
            printf("ID du contact a supprimer : ");
            scanf("%d", &id);
            supprimer_contact(db, id);

        } else if (choix == 5) {
            break;
        }
    }

    fermer_db(db);
    return 0;
}