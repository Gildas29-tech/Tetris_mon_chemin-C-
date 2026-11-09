#pragma once
#include "Definitions.h"
#include <array>

class Tetromino {
public:
    Tetromino(TypeTetromino type = TypeTetromino::I);

    void deplacer(int dx, int dy);
    void rotationHoraire();
    void rotationAntiHoraire();
    void definirPosition(int x, int y);

    bool essayerRotationHoraire(const std::array<std::array<sf::Color, LARGEUR_GRILLE>, HAUTEUR_GRILLE>& grille);
    bool essayerRotationAntiHoraire(const std::array<std::array<sf::Color, LARGEUR_GRILLE>, HAUTEUR_GRILLE>& grille);

    const std::array<Position, 4>& obtenirBlocs() const;
    TypeTetromino obtenirType() const;
    sf::Color obtenirCouleur() const;
    Position obtenirPosition() const;
    int obtenirOrientation() const;

    static TypeTetromino typeAleatoire();
    static Tetromino creerAleatoire();

private:
    void mettreAJourBlocs();
    bool verifierPosition(const std::array<std::array<sf::Color, LARGEUR_GRILLE>, HAUTEUR_GRILLE>& grille, int dx, int dy, int nouvelleOrientation) const;

    TypeTetromino type;
    int orientation;
    Position position;
    std::array<Position, 4> blocs;
};