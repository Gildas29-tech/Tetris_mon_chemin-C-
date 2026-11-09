#include "Jeu.h"

Jeu::Jeu()
    : fenetre(sf::VideoMode(DECALAGE_X * 2 + LARGEUR_GRILLE * TAILLE_CASE + 200, DECALAGE_Y * 2 + HAUTEUR_GRILLE * TAILLE_CASE), "Tetris")
    , tetrominoActuel(Tetromino::creerAleatoire())
    , prochainTetromino(Tetromino::creerAleatoire())
    , etat(EtatJeu::MENU)
    , tempsAccumule(0)
    , premierePiece(true)
    , ancienNiveau(1) {
    fenetre.setFramerateLimit(60);
    rendu.initialiser(fenetre);
}

void Jeu::executer() {
    while (fenetre.isOpen()) {
        float deltaTemps = horloge.restart().asSeconds();

        traiterEntree();

        if (etat == EtatJeu::JEU) {
            tempsAccumule += deltaTemps;
            float intervalleChute = 1.0f / (score.obtenirVitesse() * 2.0f);
            if (tempsAccumule >= intervalleChute) {
                tempsAccumule = 0;
                mettreAJour();
            }
        }

        afficher();
    }
}

void Jeu::traiterEntree() {
    auto action = entrees.traiterEvenements(fenetre);

    switch (etat) {
        case EtatJeu::MENU:
            if (action == GestionnaireEntrees::Action::DEMARRER) {
                reinitialiserJeu();
                etat = EtatJeu::JEU;
            } else if (action == GestionnaireEntrees::Action::QUITTER) {
                fenetre.close();
            }
            break;

        case EtatJeu::JEU:
            if (action == GestionnaireEntrees::Action::QUITTER) {
                fenetre.close();
            } else if (action == GestionnaireEntrees::Action::PAUSE) {
                etat = EtatJeu::PAUSE;
            } else if (action == GestionnaireEntrees::Action::GAUCHE) {
                Tetromino test = tetrominoActuel;
                test.deplacer(-1, 0);
                if (grille.estValide(test)) {
                    tetrominoActuel.deplacer(-1, 0);
                    son.jouerDeplacement();
                }
            } else if (action == GestionnaireEntrees::Action::DROITE) {
                Tetromino test = tetrominoActuel;
                test.deplacer(1, 0);
                if (grille.estValide(test)) {
                    tetrominoActuel.deplacer(1, 0);
                    son.jouerDeplacement();
                }
            } else if (action == GestionnaireEntrees::Action::BAS) {
                Tetromino test = tetrominoActuel;
                test.deplacer(0, 1);
                if (grille.estValide(test)) {
                    tetrominoActuel.deplacer(0, 1);
                    score.ajouterScore(0);
                }
            } else if (action == GestionnaireEntrees::Action::ROTATION_HORAIRE) {
                if (tetrominoActuel.essayerRotationHoraire(grille.obtenirCellules())) {
                    son.jouerRotation();
                }
            } else if (action == GestionnaireEntrees::Action::ROTATION_ANTI_HORAIRE) {
                if (tetrominoActuel.essayerRotationAntiHoraire(grille.obtenirCellules())) {
                    son.jouerRotation();
                }
            } else if (action == GestionnaireEntrees::Action::CHUTE_IMMEDIATE) {
                while (true) {
                    Tetromino test = tetrominoActuel;
                    test.deplacer(0, 1);
                    if (!grille.estValide(test)) break;
                    tetrominoActuel.deplacer(0, 1);
                    score.ajouterScore(0);
                }
                mettreAJour();
            }
            break;

        case EtatJeu::PAUSE:
            if (action == GestionnaireEntrees::Action::PAUSE || action == GestionnaireEntrees::Action::DEMARRER) {
                etat = EtatJeu::JEU;
            } else if (action == GestionnaireEntrees::Action::QUITTER) {
                fenetre.close();
            }
            break;

        case EtatJeu::GAME_OVER:
            if (action == GestionnaireEntrees::Action::DEMARRER) {
                reinitialiserJeu();
                etat = EtatJeu::JEU;
            } else if (action == GestionnaireEntrees::Action::QUITTER) {
                fenetre.close();
            }
            break;
    }
}

void Jeu::mettreAJour() {
    Tetromino test = tetrominoActuel;
    test.deplacer(0, 1);

    if (grille.estValide(test)) {
        tetrominoActuel.deplacer(0, 1);
    } else {
        grille.verrouiller(tetrominoActuel);
        son.jouerVerrouillage();

        int lignes = grille.supprimerLignesCompletes();
        if (lignes > 0) {
            score.ajouterScore(lignes);
            son.jouerLigne(lignes);
        }

        if (score.obtenirNiveau() > ancienNiveau) {
            son.jouerNiveau();
            ancienNiveau = score.obtenirNiveau();
        }

        if (verifierGameOver()) {
            etat = EtatJeu::GAME_OVER;
            son.jouerGameOver();
        } else {
            genererNouveauTetromino();
        }
    }
}

void Jeu::genererNouveauTetromino() {
    tetrominoActuel = prochainTetromino;
    prochainTetromino = Tetromino::creerAleatoire();
    tetrominoActuel.definirPosition(4, 0);
}

bool Jeu::verifierGameOver() {
    return !grille.estValide(tetrominoActuel);
}

void Jeu::reinitialiserJeu() {
    grille.reinitialiser();
    score.reinitialiser();
    tetrominoActuel = Tetromino::creerAleatoire();
    prochainTetromino = Tetromino::creerAleatoire();
    tetrominoActuel.definirPosition(4, 0);
    tempsAccumule = 0;
    premierePiece = true;
    ancienNiveau = 1;
}

void Jeu::afficher() {
    rendu.effacer();

    switch (etat) {
        case EtatJeu::MENU:
            rendu.dessinerMenu();
            break;

        case EtatJeu::JEU:
        case EtatJeu::PAUSE:
            rendu.dessinerGrille(grille);
            rendu.dessinerTetromino(tetrominoActuel);
            rendu.dessinerProchainTetromino(prochainTetromino);
            rendu.dessinerScore(score);
            if (etat == EtatJeu::PAUSE) {
                rendu.dessinerPause();
            }
            break;

        case EtatJeu::GAME_OVER:
            rendu.dessinerGrille(grille);
            rendu.dessinerScore(score);
            rendu.dessinerGameOver(score.obtenirScore(), score.obtenirMeilleurScore());
            break;
    }

    rendu.afficher();
}