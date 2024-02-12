
# Contrôle LED ESP32 avec Django

Ce projet Django permet de contrôler une LED sur un ESP32 via le port série, en utilisant une interface web simple.

## 1. Prérequis

- Python 3.6 ou supérieur
- Django
- PySerial

## 2. Installation

### Environnement Virtuel

Il est recommandé de créer un environnement virtuel pour isoler les dépendances du projet :

\`\`\`bash
python -m venv myenv
source myenv/bin/activate  # Sur Linux/Mac
myenv\Scripts\activate  # Sur Windows
\`\`\`

### Dépendances

Installer Django et PySerial :

\`\`\`bash
pip install django pyserial
\`\`\`

## 3. Démarrage du Projet

### Créer un Projet Django

\`\`\`bash
django-admin startproject monprojet
cd monprojet
\`\`\`

### Ajouter une Application Django

\`\`\`bash
python manage.py startapp controle_led
\`\`\`

## 4. Configuration du Projet

### Modèles

Définir les modèles dans \`controle_led/models.py\` si nécessaire.

### URLs

Configurer les URLs dans \`controle_led/urls.py\` et \`monprojet/urls.py\`.

### Vues

Créer les fonctions de vue dans \`controle_led/views.py\` pour gérer les requêtes.

### Templates

Ajouter les templates HTML dans le dossier \`controle_led/templates\`.

## 5. Communication avec l'ESP32

Utiliser PySerial dans les vues pour communiquer avec l'ESP32 via le port série.

### Code de l'ESP32

Le code pour l'ESP32 doit écouter les commandes sur le port série pour contrôler la LED.

## 6. Tester l'Application

Lancer le serveur de développement et accéder à l'interface utilisateur via un navigateur web.

## 7. Déploiement

Préparer l'application pour le déploiement en collectant les fichiers statiques, configurant la base de données de production, et ajustant les paramètres de sécurité.

## 8. Notes de Débogage

En cas de problème, vérifier les logs du serveur Django et les messages sur le port série de l'ESP32.

---

Ce README fournit un guide de base pour démarrer avec le projet de contrôle d'une LED sur un ESP32 à l'aide de Django. Les étapes spécifiques et la configuration peuvent varier en fonction des besoins précis du projet.
