cat << 'EOF' > README.md
# 🖥️ P4nic API

**P4nic API** est une API web ultra-légère, écrite entièrement en C, conçue pour surveiller les ressources système de mon Raspberry Pi 4. Elle fonctionne en arrière-plan et fournit des statistiques en temps réel via des requêtes HTTP.

---

## ✨ Fonctionnalités

L'API expose actuellement trois routes qui renvoient des données système :

* **`/ram`** : Renvoie l'utilisation de la mémoire RAM (Totale et Disponible) au format JSON.
* **`/cpu`** : Renvoie la charge moyenne du processeur (1 min, 5 min, 15 min) au format JSON.
* **`/process`** : Renvoie le top 5 des processus les plus gourmands en CPU au format texte.

---

## 📂 Architecture du Projet

Le projet suit une architecture C modulaire :

    P4nic/
    ├── build/       # Fichiers compilés (.o) et l'exécutable (p4nic_api)
    ├── include/     # Fichiers d'en-tête (.h) définissant les menus
    ├── src/         # Fichiers source (.c) contenant la logique
    └── Makefile     # Script d'automatisation de la compilation

---

## 🛠️ Installation et Démarrage

### 1. Prérequis
Assurez-vous d'avoir un compilateur C (`gcc`) et `make` installés sur votre système.

### 2. Compilation
Placez-vous à la racine du projet et utilisez le Makefile fourni :
    
    make

*(Pour tout recompiler depuis zéro, utilisez `make rebuild`)*

### 3. Lancement du serveur
Démarrez l'API (elle écoutera par défaut sur le port 8080) :
    
    ./build/p4nic_api

---

## 🌐 Intégration Web (Frontend)

L'API est configurée avec les en-têtes **CORS** (`Access-Control-Allow-Origin: *`), ce qui permet de l'interroger directement depuis n'importe quelle page Web utilisant du JavaScript.

### Exemple avec fetch() en JavaScript

    const API_URL = "http://localhost:8080";

    // Exemple : Récupérer la RAM
    fetch(`${API_URL}/ram`)
        .then(response => response.json())
        .then(data => {
            console.log("RAM Totale (Kb):", data.totalRamKb);
        });
