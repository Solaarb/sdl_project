# SDL Project - Jeu d'Évitement

Un jeu d'arcade 2D développé en C avec SDL2 où le joueur doit éviter des obstacles qui tombent du ciel.

## 📋 Description

Ce projet est un jeu d'évitement développé dans le cadre du cours d'Interface Graphique Simplifiée à Sorbonne Université (LEEA/LU2EE21). Le joueur contrôle un personnage qui doit esquiver des palmiers qui tombent du ciel et éviter les éléphants qui se déplacent aléatoirement sur l'écran.

### ✨ Caractéristiques

- **Gameplay d'évitement** : Esquivez les obstacles pour survivre le plus longtemps possible
- **Système de vies** : 5 cœurs de vie avec période d'invincibilité après collision
- **Obstacles multiples** :
  - Palmiers tombant du ciel à vitesse variable
  - Éléphants se déplaçant en diagonales sur l'écran
- **Interface utilisateur** :
  - Menu principal avec image de fond
  - Écran de game over
  - Affichage des vies restantes
- **Contrôles fluides** : Déplacement du joueur avec les flèches ou WASD
- **Graphismes** : Textures BMP pour tous les éléments du jeu

## 🎮 Gameplay

Le joueur contrôle un personnage qui peut se déplacer librement sur l'écran. Des palmiers tombent régulièrement du haut de l'écran et trois éléphants se déplacent de manière aléatoire. Chaque collision avec un obstacle fait perdre une vie et active une période d'invincibilité temporaire (2 secondes) pendant laquelle le joueur clignote en rouge.

Le jeu se termine quand toutes les vies sont épuisées.

## 🕹️ Contrôles

- **Déplacement** :
  - `↑` ou `Z` : Monter
  - `↓` ou `S` : Descendre  
  - `←` ou `Q` : Aller à gauche
  - `→` ou `D` : Aller à droite
- **Menu** :
  - `ESPACE` : Commencer la partie (depuis le menu) ou quitter (depuis game over)
  - `ÉCHAP` : Quitter le jeu

## 🛠️ Prérequis

- **Système d'exploitation** : Linux, macOS ou Windows
- **Compilateur** : GCC
- **Bibliothèques** :
  - SDL2 (développement)
  - pkg-config

### Installation des dépendances

#### Ubuntu/Debian
```bash
sudo apt update
sudo apt install libsdl2-dev pkg-config gcc make
```

#### macOS (avec Homebrew)
```bash
brew install sdl2 pkg-config
```

#### Windows
- Télécharger SDL2 Development Libraries depuis [libsdl.org](https://www.libsdl.org/download-2.0.php)
- Le fichier `SDL2.dll` est déjà inclus dans le projet

## 🚀 Installation et Compilation

1. **Cloner le projet** :
```bash
git clone https://github.com/Solaarb/sdl_project.git
cd sdl_project
```

2. **Compiler** :
```bash
make
```

3. **Nettoyer** (optionnel) :
```bash
make clean
```

4. **Lancer le jeu** :
```bash
./jeu.exe
```

## 📁 Structure du Projet

```
sdl_project/
├── src/                 # Code source
│   ├── main.c           # Point d'entrée du programme
│   ├── jeu.c            # Logique principale du jeu
│   ├── joueur.c         # Gestion du joueur
│   ├── palmier.c        # Gestion des palmiers
│   └── elephant.c       # Gestion des éléphants
├── includes/            # Fichiers d'en-tête
│   ├── jeu.h            # Déclarations principales
│   ├── struct.h         # Structures de données
│   ├── joueur.h         # Interface joueur
│   ├── palmier.h        # Interface palmiers
│   └── elephant.h       # Interface éléphants
├── img/                 # Resources graphiques
│   ├── joueur.bmp       # Sprite du joueur
│   ├── palmier.bmp      # Sprite des palmiers
│   ├── elephant.bmp     # Sprite des éléphants
│   ├── coeur.bmp        # Sprite des vies
│   ├── startMenu.bmp    # Image du menu
│   └── gameOver.bmp     # Image de fin de jeu
├── Makefile             # Script de compilation
├── SDL2.dll             # Bibliothèque SDL2 (Windows)
└── README.md            # Ce fichier
```

## 🎨 Ressources

- **SDL2** : Bibliothèque graphique multiplateforme
- **Lazy Foo' Productions** : [Tutoriels SDL](https://lazyfoo.net/tutorials/SDL)
- **SDL Textures** : [Guide Wikibooks](https://fr.wikibooks.org/wiki/Programmation_avec_la_SDL/Les_textures)

## 👥 Contributeurs

- **Xavier Clady** (xavier.clady@sorbonne-universite.fr) - Développeur principal
- Bibliothèque libgraphic de Bruno Gas

## 📝 Version

- **Version actuelle** : 1.1
- **Date de création** : Mars 2020

### Dernières modifications
- Utilisation des textures pour dessiner les différents objets du jeu
- Ajout du dessin d'ellipses pleines et vides
- Amélioration du système de rendu

## 🐛 Résolution des Problèmes

### Erreur de compilation SDL
Si vous obtenez une erreur `SDL.h: No such file or directory` :
```bash
sudo apt install libsdl2-dev pkg-config
```

### Problème d'affichage
Assurez-vous que tous les fichiers `.bmp` sont présents dans le dossier `img/`.

### Performance
Le jeu utilise la vsync pour limiter le framerate et assurer une expérience de jeu fluide.

## 📄 Licence

Ce projet est développé dans un cadre éducatif à Sorbonne Université.