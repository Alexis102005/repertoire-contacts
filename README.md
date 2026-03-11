# Répertoire de Contacts

Projet personnel développé entièrement par moi, de A à Z.
Un gestionnaire de contacts construit en 4 technologies différentes autour d'une même base de données SQLite.

## Ce que j'ai construit

- Un programme en **C** qui tourne dans le terminal
- Une **API REST** en Python/Flask
- Une **interface web** en HTML/CSS/JavaScript
- Une **app mobile** en React Native

## Lancer le projet

API :
```bash
python api/app.py
```

App mobile :
```bash
cd mobile && npx expo start
```

Programme C :
```bash
gcc src/main.c src/contacts.c -o repertoire -lsqlite3 && ./repertoire
```