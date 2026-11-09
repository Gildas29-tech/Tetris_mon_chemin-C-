#pragma once
#include "Definitions.h"
#include "Tetromino.h"
#include <array>

class Grille {
public:
    Grille();

    bool estValide(const Tetromino& tetromino) const;
    void verrouiller(const Tetromino& tetromino);
    int supprimerLignesCompletes();
    bool estPleine(int x, int y) const;
    void reinitialiser();

    const std::array<std::array<sf::Color, LARGEUR_GRILLE>, HAUTEUR_GRILLE>& obtenirCellules() const;

private:
    std::array<std::array<sf::Color, LARGEUR_GRILLE>, HAUTEUR_GRILLE> cellules;
};