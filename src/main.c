#include <stdio.h>
#include "../include/contact.h"


int main() {
    Contact contacts[MAX_CONTACTS];
    int nb_contacts = charger_contacts(contacts);
    int choix;

    while (1) {
        printf("1. Ajouter un contact\n");
        printf("2. Afficher tous les contacts\n");
        printf("3. Rechercher un contact\n");
        printf("4. Supprimer un contact\n");
        printf("5. Quitter\n");
        scanf("%d", &choix);

        if (choix == 1) {
            if (nb_contacts >= MAX_CONTACTS) {
                printf("Repertoire plein !\n");
                continue;
            }
            Contact *c = &contacts[nb_contacts];
            printf("Nom : ");
            scanf("%49s", c->nom);
            printf("Prenom : ");
            scanf("%49s", c->prenom);
            printf("Telephone : ");
            scanf("%19s", c->telephone);
            printf("Email : ");
            scanf("%49s", c->email);
            nb_contacts++;
            printf("Contact ajoute !\n");

        } else if (choix == 2) {
            if (nb_contacts == 0) {
                printf("Aucun contact.\n");
                continue;
            }
            for (int i = 0; i < nb_contacts; i++) {
                printf("\n[%d] %s %s - %s\n", i+1, contacts[i].prenom, contacts[i].nom, contacts[i].telephone);
            }

        } else if (choix == 3) {
            break;
        } else if (choix == 3) {
    rechercher_contact(contacts, nb_contacts);

} else if (choix == 4) {
    nb_contacts = supprimer_contact(contacts, nb_contacts);

} else if (choix == 5) {
    break;
}
    }
sauvegarder_contacts(contacts, nb_contacts);
    return 0;
}