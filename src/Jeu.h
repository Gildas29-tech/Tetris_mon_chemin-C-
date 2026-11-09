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
    bool verifierGameOver();

    sf::RenderWindow fenetre;
    Grille grille;
    Tetromino tetrominoActuel;
    Tetromino prochainTetromino;
    GestionnaireScore score;
    GestionnaireEntrees entrees;
    GestionnaireSon son;
    Rendu rendu;

    EtatJeu etat;
    sf::Clock horloge;
    float tempsAccumule;
    bool premierePiece;
    int ancienNiveau;
};