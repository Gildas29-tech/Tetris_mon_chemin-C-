#pragma once
#include "Definitions.h"
#include "Grille.h"
#include "Tetromino.h"
#include "GestionnaireScore.h"
#include <SFML/Graphics.hpp>
#include <vector>

struct Particule {
    sf::Vector2f position;
    sf::Vector2f vitesse;
    sf::Color couleur;
    float vie;
    float vieMax;
};

class Rendu {
public:
    Rendu();
    ~Rendu();

    void initialiser(sf::RenderWindow& fenetre);
    void dessinerGrille(const Grille& grille);
    void dessinerTetromino(const Tetromino& tetromino);
    void dessinerProchainTetromino(const Tetromino& prochain);
    void dessinerProchainTetrominoIndex(const Tetromino& prochain, int index);
    void dessinerHoldTetromino(const Tetromino& hold);
    void dessinerScore(const GestionnaireScore& score);
    void dessinerMenu(const GestionnaireScore& score);
    void dessinerPause();
    void dessinerGameOver(int score, int meilleurScore);
    void effacer();
    void afficher();
    void ajouterParticulesLigne(int y, const std::array<sf::Color, LARGEUR_GRILLE>& ligne);
    void mettreAJourParticules(float dt);
    void dessinerParticules();

private:
    sf::RenderWindow* fenetre;
    sf::Font police;
    sf::RectangleShape caseForme;
    sf::RectangleShape ombreForme;
    sf::CircleShape particuleForme;
    bool policeChargee;
    std::vector<Particule> particules;
    std::vector<sf::RectangleShape> fondGrille;

    void dessinerBloc(int x, int y, sf::Color couleur, bool ombre = false);
    sf::Vector2f positionEcran(int x, int y) const;
};