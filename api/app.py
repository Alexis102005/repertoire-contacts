from flask import Flask, jsonify, request
from flask_cors import CORS
import sqlite3

app = Flask(__name__)
CORS(app)
DB_PATH = "contacts.db"

def get_db():
    conn = sqlite3.connect(DB_PATH)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/contacts', methods=['GET'])
def get_contacts():
    db = get_db()
    contacts = db.execute("SELECT * FROM contacts").fetchall()
    db.close()
    return jsonify([dict(c) for c in contacts])

@app.route('/contacts', methods=['POST'])
def add_contact():
    data = request.json
    db = get_db()
    db.execute(
        "INSERT INTO contacts (nom, prenom, telephone, email, adresse) VALUES (?,?,?,?,?)",
        (data['nom'], data['prenom'], data['telephone'], data['email'], data.get('adresse', ''))
    )
    db.commit()
    db.close()
    return jsonify({"message": "Contact ajouté"}), 201

@app.route('/contacts/<int:id>', methods=['DELETE'])
def delete_contact(id):
    db = get_db()
    db.execute("DELETE FROM contacts WHERE id = ?", (id,))
    db.commit()
    db.close()
    return jsonify({"message": "Contact supprimé"})

@app.route('/contacts/<int:id>', methods=['GET'])
def get_contact(id):
    db = get_db()
    contact = db.execute("SELECT * FROM contacts WHERE id = ?", (id,)).fetchone()
    db.close()
    if contact is None:
        return jsonify({"message": "Contact introuvable"}), 404
    return jsonify(dict(contact))

@app.route('/contacts/search', methods=['GET'])
def search_contacts():
    nom = request.args.get('nom', '')
    db = get_db()
    contacts = db.execute(
        "SELECT * FROM contacts WHERE nom LIKE ? OR prenom LIKE ?",
        (f'%{nom}%', f'%{nom}%')
    ).fetchall()
    db.close()
    return jsonify([dict(c) for c in contacts])

if __name__ == '__main__':
    app.run(debug=True)