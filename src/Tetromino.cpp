#include "Tetromino.h"
#include <random>
#include <array>

Tetromino::Tetromino(TypeTetromino t) : type(t), orientation(0), position{4, 0} {
    mettreAJourBlocs();
}

void Tetromino::deplacer(int dx, int dy) {
    position.x += dx;
    position.y += dy;
    mettreAJourBlocs();
}

void Tetromino::rotationHoraire() {
    orientation = (orientation + 1) % 4;
    mettreAJourBlocs();
}

void Tetromino::rotationAntiHoraire() {
    orientation = (orientation + 3) % 4;
    mettreAJourBlocs();
}

void Tetromino::definirPosition(int x, int y) {
    position.x = x;
    position.y = y;
    mettreAJourBlocs();
}

bool Tetromino::verifierPosition(const std::array<std::array<sf::Color, LARGEUR_GRILLE>, HAUTEUR_GRILLE>& grille, int dx, int dy, int nouvelleOrientation) const {
    const auto& forme = FORMES_TETROMINOS[static_cast<int>(type)];
    for (int i = 0; i < 4; ++i) {
        int x = forme[i].first;
        int y = forme[i].second;

        for (int r = 0; r < nouvelleOrientation; ++r) {
            int nx = -y;
            int ny = x;
            x = nx;
            y = ny;
        }

        int finalX = position.x + dx + x;
        int finalY = position.y + dy + y;

        if (finalX < 0 || finalX >= LARGEUR_GRILLE || finalY >= HAUTEUR_GRILLE) {
            return false;
        }
        if (finalY >= 0 && grille[finalY][finalX] != sf::Color::Transparent) {
            return false;
        }
    }
    return true;
}

bool Tetromino::essayerRotationHoraire(const std::array<std::array<sf::Color, LARGEUR_GRILLE>, HAUTEUR_GRILLE>& grille) {
    int nouvelleOrientation = (orientation + 1) % 4;

    static const std::array<std::pair<int, int>, 5> kicks = {{
        {0, 0}, {-1, 0}, {1, 0}, {-2, 0}, {2, 0}
    }};

    for (const auto& kick : kicks) {
        if (verifierPosition(grille, kick.first, kick.second, nouvelleOrientation)) {
            position.x += kick.first;
            position.y += kick.second;
            orientation = nouvelleOrientation;
            mettreAJourBlocs();
            return true;
        }
    }
    return false;
}

bool Tetromino::essayerRotationAntiHoraire(const std::array<std::array<sf::Color, LARGEUR_GRILLE>, HAUTEUR_GRILLE>& grille) {
    int nouvelleOrientation = (orientation + 3) % 4;

    static const std::array<std::pair<int, int>, 5> kicks = {{
        {0, 0}, {-1, 0}, {1, 0}, {-2, 0}, {2, 0}
    }};

    for (const auto& kick : kicks) {
        if (verifierPosition(grille, kick.first, kick.second, nouvelleOrientation)) {
            position.x += kick.first;
            position.y += kick.second;
            orientation = nouvelleOrientation;
            mettreAJourBlocs();
            return true;
        }
    }
    return false;
}

const std::array<Position, 4>& Tetromino::obtenirBlocs() const {
    return blocs;
}

TypeTetromino Tetromino::obtenirType() const {
    return type;
}

sf::Color Tetromino::obtenirCouleur() const {
    return COULEURS_TETROMINOS[static_cast<int>(type)];
}

Position Tetromino::obtenirPosition() const {
    return position;
}

int Tetromino::obtenirOrientation() const {
    return orientation;
}

TypeTetromino Tetromino::typeAleatoire() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 6);
    return static_cast<TypeTetromino>(dis(gen));
}

Tetromino Tetromino::creerAleatoire() {
    return Tetromino(typeAleatoire());
}

void Tetromino::mettreAJourBlocs() {
    const auto& forme = FORMES_TETROMINOS[static_cast<int>(type)];
    for (int i = 0; i < 4; ++i) {
        int x = forme[i].first;
        int y = forme[i].second;

        for (int r = 0; r < orientation; ++r) {
            int nx = -y;
            int ny = x;
            x = nx;
            y = ny;
        }

        blocs[i] = {position.x + x, position.y + y};
    }
}