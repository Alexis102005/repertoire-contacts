import { useState, useEffect } from 'react';
import { View, Text, TextInput, TouchableOpacity, FlatList, StyleSheet, Alert } from 'react-native';

const API = 'http://127.0.0.1:5000';

export default function App() {
  const [contacts, setContacts] = useState([]);
  const [nom, setNom] = useState('');
  const [prenom, setPrenom] = useState('');
  const [telephone, setTelephone] = useState('');
  const [email, setEmail] = useState('');
  const [recherche, setRecherche] = useState('');

  useEffect(() => {
    chargerContacts();
  }, []);

  async function chargerContacts() {
    const res = await fetch(`${API}/contacts`);
    const data = await res.json();
    setContacts(data);
  }

  async function ajouterContact() {
    if (!nom || !prenom) return Alert.alert('Erreur', 'Nom et prenom requis');
    await fetch(`${API}/contacts`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ nom, prenom, telephone, email, adresse: '' })
    });
    setNom(''); setPrenom(''); setTelephone(''); setEmail('');
    chargerContacts();
  }

  async function supprimerContact(id: number) {
    await fetch(`${API}/contacts/${id}`, { method: 'DELETE' });
    chargerContacts();
  }

  async function rechercherContact() {
    const res = await fetch(`${API}/contacts/search?nom=${recherche}`);
    const data = await res.json();
    setContacts(data);
  }

  return (
    <View style={styles.container}>
      <Text style={styles.titre}>Repertoire de Contacts</Text>

      <TextInput style={styles.input} placeholder="Nom" value={nom} onChangeText={setNom} />
      <TextInput style={styles.input} placeholder="Prenom" value={prenom} onChangeText={setPrenom} />
      <TextInput style={styles.input} placeholder="Telephone" value={telephone} onChangeText={setTelephone} />
      <TextInput style={styles.input} placeholder="Email" value={email} onChangeText={setEmail} />
      <TouchableOpacity style={styles.bouton} onPress={ajouterContact}>
        <Text style={styles.boutonTexte}>Ajouter</Text>
      </TouchableOpacity>

      <TextInput style={styles.input} placeholder="Rechercher..." value={recherche} onChangeText={setRecherche} />
      <TouchableOpacity style={[styles.bouton, {backgroundColor: '#2196F3'}]} onPress={rechercherContact}>
        <Text style={styles.boutonTexte}>Rechercher</Text>
      </TouchableOpacity>

      <FlatList
        data={contacts}
        keyExtractor={(item: any) => item.id.toString()}
        renderItem={({ item }: any) => (
          <View style={styles.contact}>
            <Text style={styles.contactNom}>{item.prenom} {item.nom}</Text>
            <Text>{item.telephone} - {item.email}</Text>
            <TouchableOpacity onPress={() => supprimerContact(item.id)}>
              <Text style={styles.supprimer}>Supprimer</Text>
            </TouchableOpacity>
          </View>
        )}
      />
    </View>
  );
}

const styles = StyleSheet.create({
  container: { flex: 1, padding: 20, backgroundColor: '#fff', paddingTop: 50 },
  titre: { fontSize: 24, fontWeight: 'bold', marginBottom: 20 },
  input: { borderWidth: 1, borderColor: '#ccc', padding: 10, marginBottom: 10, borderRadius: 6 },
  bouton: { backgroundColor: '#4CAF50', padding: 12, borderRadius: 6, alignItems: 'center', marginBottom: 10 },
  boutonTexte: { color: 'white', fontWeight: 'bold' },
  contact: { borderWidth: 1, borderColor: '#ddd', padding: 10, marginBottom: 8, borderRadius: 6 },
  contactNom: { fontWeight: 'bold', fontSize: 16 },
  supprimer: { color: 'red', marginTop: 5 }
});