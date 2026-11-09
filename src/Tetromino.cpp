#include "Tetromino.h"
#include <random>

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