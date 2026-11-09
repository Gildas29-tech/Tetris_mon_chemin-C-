#include "Rendu.h"
#include <random>
#include <cmath>

Rendu::Rendu() : fenetre(nullptr), policeChargee(false) {
    caseForme.setSize(sf::Vector2f(TAILLE_CASE - 2, TAILLE_CASE - 2));
    caseForme.setOutlineThickness(1);
    caseForme.setOutlineColor(sf::Color(100, 100, 100));

    ombreForme.setSize(sf::Vector2f(TAILLE_CASE - 2, TAILLE_CASE - 2));
    ombreForme.setFillColor(sf::Color(255, 255, 255, 100));
    ombreForme.setOutlineThickness(1);
    ombreForme.setOutlineColor(sf::Color(200, 200, 200, 150));

    particuleForme.setRadius(3.0f);
    particuleForme.setOrigin(3.0f, 3.0f);
}

Rendu::~Rendu() {}

void Rendu::initialiser(sf::RenderWindow& f) {
    fenetre = &f;
    if (police.loadFromFile("assets/arial.ttf")) {
        policeChargee = true;
    }
}

sf::Vector2f Rendu::positionEcran(int x, int y) const {
    return sf::Vector2f(DECALAGE_X + x * TAILLE_CASE + 1, DECALAGE_Y + y * TAILLE_CASE + 1);
}

void Rendu::dessinerBloc(int x, int y, sf::Color couleur, bool ombre) {
    if (!fenetre) return;
    sf::Vector2f pos = positionEcran(x, y);
    if (ombre) {
        ombreForme.setPosition(pos);
        fenetre->draw(ombreForme);
    } else {
        caseForme.setPosition(pos);
        caseForme.setFillColor(couleur);
        fenetre->draw(caseForme);
    }
}

void Rendu::dessinerGrille(const Grille& grille) {
    if (!fenetre) return;

    for (int y = 0; y < HAUTEUR_GRILLE; ++y) {
        for (int x = 0; x < LARGEUR_GRILLE; ++x) {
            sf::Color couleur = grille.obtenirCellules()[y][x];
            if (couleur != sf::Color::Transparent) {
                dessinerBloc(x, y, couleur);
            } else {
                sf::Vector2f pos = positionEcran(x, y);
                caseForme.setPosition(pos);
                caseForme.setFillColor(sf::Color(30, 30, 30));
                fenetre->draw(caseForme);
            }
        }
    }

    sf::RectangleShape bordure(sf::Vector2f(LARGEUR_GRILLE * TAILLE_CASE + 2, HAUTEUR_GRILLE * TAILLE_CASE + 2));
    bordure.setPosition(DECALAGE_X - 1, DECALAGE_Y - 1);
    bordure.setFillColor(sf::Color::Transparent);
    bordure.setOutlineThickness(2);
    bordure.setOutlineColor(sf::Color::White);
    fenetre->draw(bordure);
}

void Rendu::dessinerTetromino(const Tetromino& tetromino) {
    if (!fenetre) return;

    int ombreY = 0;
    const auto& blocs = tetromino.obtenirBlocs();
    for (const auto& bloc : blocs) {
        int testY = bloc.y;
        while (testY + 1 < HAUTEUR_GRILLE) {
            bool collision = false;
            for (const auto& b : blocs) {
                if (b.x == bloc.x && b.y == testY + 1) {
                    collision = true;
                    break;
                }
            }
            if (collision) break;
            ++testY;
        }
        ombreY = std::max(ombreY, testY - bloc.y);
    }

    for (const auto& bloc : blocs) {
        if (bloc.y >= 0) {
            dessinerBloc(bloc.x, bloc.y + ombreY, tetromino.obtenirCouleur(), true);
        }
    }

    for (const auto& bloc : blocs) {
        if (bloc.y >= 0) {
            dessinerBloc(bloc.x, bloc.y, tetromino.obtenirCouleur());
        }
    }
}

void Rendu::dessinerProchainTetromino(const Tetromino& prochain) {
    if (!fenetre || !policeChargee) return;

    sf::Text texte("PROCHAIN", police, 20);
    texte.setPosition(DECALAGE_X + LARGEUR_GRILLE * TAILLE_CASE + 50, DECALAGE_Y);
    texte.setFillColor(sf::Color::White);
    fenetre->draw(texte);

    const auto& blocs = prochain.obtenirBlocs();
    for (const auto& bloc : blocs) {
        sf::Vector2f pos(DECALAGE_X + LARGEUR_GRILLE * TAILLE_CASE + 50 + bloc.x * TAILLE_CASE, DECALAGE_Y + 40 + bloc.y * TAILLE_CASE);
        caseForme.setPosition(pos);
        caseForme.setFillColor(prochain.obtenirCouleur());
        fenetre->draw(caseForme);
    }
}

void Rendu::dessinerProchainTetrominoIndex(const Tetromino& prochain, int index) {
    if (!fenetre || !policeChargee) return;

    const auto& blocs = prochain.obtenirBlocs();
    int decalageY = 40 + index * 70;
    for (const auto& bloc : blocs) {
        sf::Vector2f pos(DECALAGE_X + LARGEUR_GRILLE * TAILLE_CASE + 50 + bloc.x * TAILLE_CASE, DECALAGE_Y + decalageY + bloc.y * TAILLE_CASE);
        caseForme.setPosition(pos);
        caseForme.setFillColor(prochain.obtenirCouleur());
        fenetre->draw(caseForme);
    }
}

void Rendu::dessinerHoldTetromino(const Tetromino& hold) {
    if (!fenetre || !policeChargee) return;

    sf::Text texte("HOLD", police, 20);
    texte.setPosition(DECALAGE_X + LARGEUR_GRILLE * TAILLE_CASE + 50, DECALAGE_Y + 100);
    texte.setFillColor(sf::Color::White);
    fenetre->draw(texte);

    const auto& blocs = hold.obtenirBlocs();
    for (const auto& bloc : blocs) {
        sf::Vector2f pos(DECALAGE_X + LARGEUR_GRILLE * TAILLE_CASE + 50 + bloc.x * TAILLE_CASE, DECALAGE_Y + 140 + bloc.y * TAILLE_CASE);
        caseForme.setPosition(pos);
        caseForme.setFillColor(hold.obtenirCouleur());
        fenetre->draw(caseForme);
    }
}

void Rendu::dessinerScore(const GestionnaireScore& score) {
    if (!fenetre || !policeChargee) return;

    int x = DECALAGE_X + LARGEUR_GRILLE * TAILLE_CASE + 50;
    int y = DECALAGE_Y + 150;

    sf::Text texteScore("SCORE: " + std::to_string(score.obtenirScore()), police, 20);
    texteScore.setPosition(x, y);
    texteScore.setFillColor(sf::Color::White);
    fenetre->draw(texteScore);

    sf::Text texteMeilleur("MEILLEUR: " + std::to_string(score.obtenirMeilleurScore()), police, 20);
    texteMeilleur.setPosition(x, y + 30);
    texteMeilleur.setFillColor(sf::Color::Yellow);
    fenetre->draw(texteMeilleur);

    sf::Text texteNiveau("NIVEAU: " + std::to_string(score.obtenirNiveau()), police, 20);
    texteNiveau.setPosition(x, y + 60);
    texteNiveau.setFillColor(sf::Color::Cyan);
    fenetre->draw(texteNiveau);

    sf::Text texteLignes("LIGNES: " + std::to_string(score.obtenirLignesTotales()), police, 20);
    texteLignes.setPosition(x, y + 90);
    texteLignes.setFillColor(sf::Color::Green);
    fenetre->draw(texteLignes);
}

void Rendu::ajouterParticulesLigne(int y, const std::array<sf::Color, LARGEUR_GRILLE>& ligne) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> distAngle(0.0f, 2.0f * 3.14159f);
    static std::uniform_real_distribution<float> distVitesse(50.0f, 150.0f);
    static std::uniform_real_distribution<float> distVie(0.5f, 1.5f);
    static std::uniform_int_distribution<int> distCount(3, 6);

    for (int x = 0; x < LARGEUR_GRILLE; ++x) {
        if (ligne[x] != sf::Color::Transparent) {
            int nbParticules = distCount(gen);
            sf::Vector2f posDepart = positionEcran(x, y);
            posDepart.x += TAILLE_CASE / 2.0f;
            posDepart.y += TAILLE_CASE / 2.0f;

            for (int i = 0; i < nbParticules; ++i) {
                float angle = distAngle(gen);
                float vitesse = distVitesse(gen);
                Particule p;
                p.position = posDepart;
                p.vitesse = sf::Vector2f(std::cos(angle) * vitesse, std::sin(angle) * vitesse);
                p.couleur = ligne[x];
                p.vie = distVie(gen);
                p.vieMax = p.vie;
                particules.push_back(p);
            }
        }
    }
}

void Rendu::mettreAJourParticules(float dt) {
    for (auto it = particules.begin(); it != particules.end();) {
        it->position += it->vitesse * dt;
        it->vitesse.y += 200.0f * dt;
        it->vitesse *= 0.98f;
        it->vie -= dt;

        if (it->vie <= 0.0f) {
            it = particules.erase(it);
        } else {
            ++it;
        }
    }
}

void Rendu::dessinerParticules() {
    if (!fenetre) return;

    for (const auto& p : particules) {
        float alpha = p.vie / p.vieMax;
        sf::Color couleur = p.couleur;
        couleur.a = static_cast<sf::Uint8>(255 * alpha);
        particuleForme.setFillColor(couleur);
        particuleForme.setPosition(p.position);
        particuleForme.setScale(alpha, alpha);
        fenetre->draw(particuleForme);
    }
}

void Rendu::dessinerMenu() {
    if (!fenetre || !policeChargee) return;

    sf::Text titre("TETRIS", police, 60);
    titre.setPosition(DECALAGE_X + LARGEUR_GRILLE * TAILLE_CASE / 2 - 80, DECALAGE_Y + 50);
    titre.setFillColor(sf::Color::Cyan);
    fenetre->draw(titre);

    sf::Text instruction("APPUYEZ SUR ENTREE POUR JOUER", police, 24);
    instruction.setPosition(DECALAGE_X + 10, DECALAGE_Y + 150);
    instruction.setFillColor(sf::Color::White);
    fenetre->draw(instruction);

    sf::Text commandes("FLECHES: DEPLACER\nHAUT/X: ROTATION HORAIRE\nZ: ROTATION ANTI-HORAIRE\nBAS: ACCELERER\nESPACE: CHUTE IMMEDIATE\nC/SHIFT: HOLD\nP: PAUSE\nECHAP: QUITTER", police, 18);
    commandes.setPosition(DECALAGE_X + 10, DECALAGE_Y + 220);
    commandes.setFillColor(sf::Color(200, 200, 200));
    fenetre->draw(commandes);
}

void Rendu::dessinerPause() {
    if (!fenetre || !policeChargee) return;

    sf::RectangleShape overlay(sf::Vector2f(LARGEUR_GRILLE * TAILLE_CASE, HAUTEUR_GRILLE * TAILLE_CASE));
    overlay.setPosition(DECALAGE_X, DECALAGE_Y);
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    fenetre->draw(overlay);

    sf::Text texte("PAUSE", police, 50);
    texte.setPosition(DECALAGE_X + LARGEUR_GRILLE * TAILLE_CASE / 2 - 70, DECALAGE_Y + HAUTEUR_GRILLE * TAILLE_CASE / 2 - 50);
    texte.setFillColor(sf::Color::Yellow);
    fenetre->draw(texte);

    sf::Text instruction("APPUYEZ SUR P POUR REPRENDRE", police, 20);
    instruction.setPosition(DECALAGE_X + 30, DECALAGE_Y + HAUTEUR_GRILLE * TAILLE_CASE / 2 + 20);
    instruction.setFillColor(sf::Color::White);
    fenetre->draw(instruction);
}

void Rendu::dessinerGameOver(int scoreFinal, int meilleurScore) {
    if (!fenetre || !policeChargee) return;

    sf::RectangleShape overlay(sf::Vector2f(LARGEUR_GRILLE * TAILLE_CASE, HAUTEUR_GRILLE * TAILLE_CASE));
    overlay.setPosition(DECALAGE_X, DECALAGE_Y);
    overlay.setFillColor(sf::Color(0, 0, 0, 200));
    fenetre->draw(overlay);

    sf::Text texte("GAME OVER", police, 50);
    texte.setPosition(DECALAGE_X + LARGEUR_GRILLE * TAILLE_CASE / 2 - 110, DECALAGE_Y + HAUTEUR_GRILLE * TAILLE_CASE / 2 - 80);
    texte.setFillColor(sf::Color::Red);
    fenetre->draw(texte);

    sf::Text texteScore("SCORE: " + std::to_string(scoreFinal), police, 30);
    texteScore.setPosition(DECALAGE_X + LARGEUR_GRILLE * TAILLE_CASE / 2 - 80, DECALAGE_Y + HAUTEUR_GRILLE * TAILLE_CASE / 2);
    texteScore.setFillColor(sf::Color::White);
    fenetre->draw(texteScore);

    sf::Text texteMeilleur("MEILLEUR: " + std::to_string(meilleurScore), police, 30);
    texteMeilleur.setPosition(DECALAGE_X + LARGEUR_GRILLE * TAILLE_CASE / 2 - 80, DECALAGE_Y + HAUTEUR_GRILLE * TAILLE_CASE / 2 + 40);
    texteMeilleur.setFillColor(sf::Color::Yellow);
    fenetre->draw(texteMeilleur);

    sf::Text instruction("ENTREE: REJOUER  ECHAP: QUITTER", police, 20);
    instruction.setPosition(DECALAGE_X + 20, DECALAGE_Y + HAUTEUR_GRILLE * TAILLE_CASE / 2 + 100);
    instruction.setFillColor(sf::Color::White);
    fenetre->draw(instruction);
}

void Rendu::effacer() {
    if (fenetre) {
        fenetre->clear(sf::Color(20, 20, 30));
    }
}

void Rendu::afficher() {
    if (fenetre) {
        dessinerParticules();
        fenetre->display();
    }
}