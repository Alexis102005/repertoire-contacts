#include <stdio.h>
#include <string.h>
#include "../include/contact.h"

sqlite3* ouvrir_db() {
    sqlite3 *db;
    sqlite3_open("contacts.db", &db);
    sqlite3_exec(db,
        "CREATE TABLE IF NOT EXISTS contacts ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "nom TEXT, prenom TEXT, telephone TEXT,"
        "email TEXT, adresse TEXT);",
        NULL, NULL, NULL);
    return db;
}

void fermer_db(sqlite3 *db) {
    sqlite3_close(db);
}

void ajouter_contact(sqlite3 *db, Contact *c) {
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db,
        "INSERT INTO contacts (nom, prenom, telephone, email, adresse) VALUES (?,?,?,?,?);",
        -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, c->nom, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, c->prenom, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, c->telephone, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, c->email, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, c->adresse, -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    printf("Contact ajoute !\n");
}

int charger_contacts(sqlite3 *db, Contact *contacts) {
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "SELECT id, nom, prenom, telephone, email FROM contacts;", -1, &stmt, NULL);
    int nb = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW && nb < MAX_CONTACTS) {
        contacts[nb].id = sqlite3_column_int(stmt, 0);
        strncpy(contacts[nb].nom, (const char*)sqlite3_column_text(stmt, 1), 49);
        strncpy(contacts[nb].prenom, (const char*)sqlite3_column_text(stmt, 2), 49);
        strncpy(contacts[nb].telephone, (const char*)sqlite3_column_text(stmt, 3), 19);
        strncpy(contacts[nb].email, (const char*)sqlite3_column_text(stmt, 4), 49);
        nb++;
    }
    sqlite3_finalize(stmt);
    return nb;
}

void rechercher_contact(sqlite3 *db, const char *recherche) {
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db,
        "SELECT id, nom, prenom, telephone, email FROM contacts WHERE nom LIKE ? OR prenom LIKE ?;",
        -1, &stmt, NULL);
    char pattern[52];
    snprintf(pattern, sizeof(pattern), "%%%s%%", recherche);
    sqlite3_bind_text(stmt, 1, pattern, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, pattern, -1, SQLITE_STATIC);

    int trouve = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("\n[%d] %s %s - %s - %s\n",
            sqlite3_column_int(stmt, 0),
            sqlite3_column_text(stmt, 2),
            sqlite3_column_text(stmt, 1),
            sqlite3_column_text(stmt, 3),
            sqlite3_column_text(stmt, 4));
        trouve = 1;
    }
    if (!trouve) printf("Aucun contact trouve.\n");
    sqlite3_finalize(stmt);
}

void supprimer_contact(sqlite3 *db, int id) {
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "DELETE FROM contacts WHERE id = ?;", -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    printf("Contact supprime.\n");
}