#include <stdio.h>
#include "../include/contact.h"
int main() {
    Contact c;

    printf("=== Répertoire de Contacts ===\n\n");

    printf("Nom : ");
    scanf("%49s", c.nom);

    printf("Prénom : ");
    scanf("%49s", c.prenom);

    printf("Téléphone : ");
    scanf("%19s", c.telephone);

    printf("Email : ");
    scanf("%49s", c.email);

    printf("\n--- Contact enregistré ---\n");
    printf("Nom     : %s %s\n", c.prenom, c.nom);
    printf("Tel     : %s\n", c.telephone);
    printf("Email   : %s\n", c.email);

    return 0;
}