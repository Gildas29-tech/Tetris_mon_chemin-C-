#pragma once
#include "Definitions.h"

class Tetromino {
public:
    Tetromino(TypeTetromino type = TypeTetromino::I);

    void deplacer(int dx, int dy);
    void rotationHoraire();
    void rotationAntiHoraire();
    void definirPosition(int x, int y);

    const std::array<Position, 4>& obtenirBlocs() const;
    TypeTetromino obtenirType() const;
    sf::Color obtenirCouleur() const;
    Position obtenirPosition() const;

    static TypeTetromino typeAleatoire();
    static Tetromino creerAleatoire();

private:
    void mettreAJourBlocs();

    TypeTetromino type;
    int orientation;
    Position position;
    std::array<Position, 4> blocs;
};