#pragma once
#include "Definitions.h"
#include "Grille.h"
#include "Tetromino.h"
#include "GestionnaireScore.h"
#include "GestionnaireEntrees.h"
#include "GestionnaireSon.h"
#include "Rendu.h"
#include <SFML/System.hpp>

class Jeu {
public:
    Jeu();
    void executer();

private:
    void traiterEntree();
    void mettreAJour();
    void afficher();
    void reinitialiserJeu();
    void genererNouveauTetromino();
    void echangerHold();
    bool verifierGameOver();

    sf::RenderWindow fenetre;
    Grille grille;
    Tetromino tetrominoActuel;
    Tetromino prochainTetromino;
    Tetromino holdTetromino;
    GestionnaireScore score;
    GestionnaireEntrees entrees;
    GestionnaireSon son;
    Rendu rendu;

    EtatJeu etat;
    sf::Clock horloge;
    float tempsAccumule;
    bool premierePiece;
    int ancienNiveau;
    bool holdUtilise;
    bool holdVide;
};