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

static const std::pair<int, int> KICKS_JLSTZ[8][5] = {
    {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}},
    {{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}},
    {{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}},
    {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}},
    {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},
    {{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}},
    {{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}},
    {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}}
};

static const std::pair<int, int> KICKS_I[8][5] = {
    {{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}},
    {{0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2}},
    {{0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1}},
    {{0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1}},
    {{0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2}},
    {{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}},
    {{0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1}},
    {{0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1}}
};

int Tetromino::obtenirIndexKick(int fromOrient, int toOrient, bool horaire) const {
    if (horaire) {
        if (fromOrient == 0 && toOrient == 1) return 0;
        if (fromOrient == 1 && toOrient == 0) return 1;
        if (fromOrient == 1 && toOrient == 2) return 2;
        if (fromOrient == 2 && toOrient == 1) return 3;
        if (fromOrient == 2 && toOrient == 3) return 4;
        if (fromOrient == 3 && toOrient == 2) return 5;
        if (fromOrient == 3 && toOrient == 0) return 6;
        if (fromOrient == 0 && toOrient == 3) return 7;
    } else {
        if (fromOrient == 0 && toOrient == 3) return 0;
        if (fromOrient == 3 && toOrient == 0) return 1;
        if (fromOrient == 3 && toOrient == 2) return 2;
        if (fromOrient == 2 && toOrient == 3) return 3;
        if (fromOrient == 2 && toOrient == 1) return 4;
        if (fromOrient == 1 && toOrient == 2) return 5;
        if (fromOrient == 1 && toOrient == 0) return 6;
        if (fromOrient == 0 && toOrient == 1) return 7;
    }
    return 0;
}

bool Tetromino::essayerRotationHoraire(const std::array<std::array<sf::Color, LARGEUR_GRILLE>, HAUTEUR_GRILLE>& grille) {
    int nouvelleOrientation = (orientation + 1) % 4;
    int kickIndex = obtenirIndexKick(orientation, nouvelleOrientation, true);

    const auto& kicks = (type == TypeTetromino::I) ? KICKS_I[kickIndex] : KICKS_JLSTZ[kickIndex];

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
    if (type == TypeTetromino::O) return false;

    int nouvelleOrientation = (orientation + 3) % 4;
    int kickIndex = obtenirIndexKick(orientation, nouvelleOrientation, false);

    const auto& kicks = (type == TypeTetromino::I) ? KICKS_I[kickIndex] : KICKS_JLSTZ[kickIndex];

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