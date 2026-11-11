# Tetris en C++ avec SFML

Jeu Tetris 2D développé en C++17 avec la bibliothèque SFML.

## Prérequis

- Compilateur C++17 (GCC, Clang, MSVC)
- CMake 3.16+
- SFML 2.6.x (graphics, window, system, audio; SFML 3.x n'est pas compatible avec les API utilisées)

## Installation de SFML

### Windows (avec vcpkg)

Installez **Visual Studio Build Tools** avec la charge de travail **Développement Desktop en C++** (MSVC et SDK Windows). L'IDE Visual Studio complet n'est pas nécessaire. Dans VS Code, installez aussi les extensions **C/C++** et **CMake Tools**.

Dans PowerShell, placez-vous dans le dossier du projet (celui qui contient `vcpkg.json`), puis installez SFML :

```powershell
$env:VCPKG_ROOT = "$env:USERPROFILE\vcpkg"
Set-Location 'C:\Users\royal\Desktop\Nouveau dossier (2)\Tetris_mon_chemin-C-'
& "$env:VCPKG_ROOT\vcpkg.exe" install --triplet x64-windows
```

Dans VS Code, exécutez **CMake: Select a Kit**, choisissez le kit MSVC x64, puis **CMake: Delete Cache and Reconfigure** et **CMake: Build**.

### Linux (Ubuntu/Debian)
```bash
sudo apt-get install libsfml-dev
```

### macOS (Homebrew)
```bash
brew install sfml
```

## Compilation

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Lancement

```bash
# Depuis la racine du projet
./build/Tetris
# ou sur Windows
.\build\Tetris.exe
```

## Commandes

| Touche | Action |
|--------|--------|
| Flèche Gauche/Droite | Déplacer la pièce |
| Flèche Haut / X | Rotation horaire |
| Z | Rotation antihoraire |
| Flèche Bas | Accélérer la chute |
| Espace | Chute immédiate |
| P | Pause / Reprise |
| Entrée | Démarrer / Recommencer |
| Échap | Quitter |

## Règles

- Grille : 10 colonnes × 20 lignes
- 7 tétrominos classiques (I, J, L, O, S, T, Z)
- Score : 1 ligne = 100 pts, 2 lignes = 300 pts, 3 lignes = 500 pts, 4 lignes = 800 pts (× niveau)
- Niveau augmente toutes les 10 lignes
- Meilleur score sauvegardé automatiquement

## Architecture

```
src/
├── main.cpp                 # Point d'entrée
├── Definitions.h            # Constantes et types communs
├── Jeu.h/.cpp               # Boucle principale et états
├── Grille.h/.cpp            # Grille de jeu et suppression lignes
├── Tetromino.h/.cpp         # Pièces, rotation, déplacement
├── GestionnaireEntrees.h/.cpp # Gestion clavier
├── Rendu.h/.cpp             # Affichage SFML
└── GestionnaireScore.h/.cpp # Score, niveaux, persistance
```

## Fonctionnalités

- Écran d'accueil avec commandes
- Grille de jeu avec bordures
- Génération aléatoire des 7 tétrominos
- Déplacement gauche/droite
- Rotation horaire (Haut/X) et antihoraire (Z)
- Chute automatique avec accélération (Bas)
- Chute immédiate (Espace)
- Verrouillage et suppression des lignes complètes
- Système de score et niveaux progressifs
- Affichage de la prochaine pièce
- Ombre de position d'atterrissage
- Pause / Reprise
- Game Over avec score final
- Sauvegarde du meilleur score
- Thème de couleurs par type de pièce