#pragma once
#include "Definitions.h"
#include "Grille.h"
#include "Tetromino.h"
#include "GestionnaireScore.h"
#include <SFML/Graphics.hpp>

class Rendu {
public:
    Rendu();
    ~Rendu();

    void initialiser(sf::RenderWindow& fenetre);
    void dessinerGrille(const Grille& grille);
    void dessinerTetromino(const Tetromino& tetromino);
    void dessinerProchainTetromino(const Tetromino& prochain);
    void dessinerHoldTetromino(const Tetromino& hold);
    void dessinerScore(const GestionnaireScore& score);
    void dessinerMenu();
    void dessinerPause();
    void dessinerGameOver(int score, int meilleurScore);
    void effacer();
    void afficher();

private:
    sf::RenderWindow* fenetre;
    sf::Font police;
    sf::RectangleShape caseForme;
    sf::RectangleShape ombreForme;
    bool policeChargee;

    void dessinerBloc(int x, int y, sf::Color couleur, bool ombre = false);
    sf::Vector2f positionEcran(int x, int y) const;
};