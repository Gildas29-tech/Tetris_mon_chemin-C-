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

    for (int y = 0; y < HAUTEUR_GRILLE; ++y) {
        for (int x = 0; x < LARGEUR_GRILLE; ++x) {
            sf::RectangleShape rect(sf::Vector2f(TAILLE_CASE, TAILLE_CASE));
            rect.setPosition(DECALAGE_X + x * TAILLE_CASE, DECALAGE_Y + y * TAILLE_CASE);
            rect.setFillColor((x + y) % 2 == 0 ? sf::Color(30, 30, 40) : sf::Color(25, 25, 35));
            fondGrille.push_back(rect);
        }
    }
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
        sf::Color couleurClair = couleur;
        sf::Color couleurFonce = couleur;
        couleurClair.r = std::min(255, couleur.r + 60);
        couleurClair.g = std::min(255, couleur.g + 60);
        couleurClair.b = std::min(255, couleur.b + 60);
        couleurFonce.r = std::max(0, couleur.r - 60);
        couleurFonce.g = std::max(0, couleur.g - 60);
        couleurFonce.b = std::max(0, couleur.b - 60);

        caseForme.setFillColor(couleur);
        fenetre->draw(caseForme);

        sf::VertexArray haut(sf::TrianglesStrip, 4);
        haut[0] = sf::Vertex(pos, couleurClair);
        haut[1] = sf::Vertex(sf::Vector2f(pos.x + TAILLE_CASE - 2, pos.y), couleurClair);
        haut[2] = sf::Vertex(sf::Vector2f(pos.x, pos.y + 3), sf::Color(couleurClair.r, couleurClair.g, couleurClair.b, 100));
        haut[3] = sf::Vertex(sf::Vector2f(pos.x + TAILLE_CASE - 2, pos.y + 3), sf::Color(couleurClair.r, couleurClair.g, couleurClair.b, 100));
        fenetre->draw(haut);

        sf::VertexArray gauche(sf::TrianglesStrip, 4);
        gauche[0] = sf::Vertex(pos, couleurClair);
        gauche[1] = sf::Vertex(sf::Vector2f(pos.x + 3, pos.y), sf::Color(couleurClair.r, couleurClair.g, couleurClair.b, 100));
        gauche[2] = sf::Vertex(sf::Vector2f(pos.x, pos.y + TAILLE_CASE - 2), couleurClair);
        gauche[3] = sf::Vertex(sf::Vector2f(pos.x + 3, pos.y + TAILLE_CASE - 2), sf::Color(couleurClair.r, couleurClair.g, couleurClair.b, 100));
        fenetre->draw(gauche);

        sf::VertexArray bas(sf::TrianglesStrip, 4);
        bas[0] = sf::Vertex(sf::Vector2f(pos.x, pos.y + TAILLE_CASE - 2), couleurFonce);
        bas[1] = sf::Vertex(sf::Vector2f(pos.x + TAILLE_CASE - 2, pos.y + TAILLE_CASE - 2), couleurFonce);
        bas[2] = sf::Vertex(sf::Vector2f(pos.x, pos.y + TAILLE_CASE - 5), sf::Color(couleurFonce.r, couleurFonce.g, couleurFonce.b, 100));
        bas[3] = sf::Vertex(sf::Vector2f(pos.x + TAILLE_CASE - 2, pos.y + TAILLE_CASE - 5), sf::Color(couleurFonce.r, couleurFonce.g, couleurFonce.b, 100));
        fenetre->draw(bas);

        sf::VertexArray droite(sf::TrianglesStrip, 4);
        droite[0] = sf::Vertex(sf::Vector2f(pos.x + TAILLE_CASE - 2, pos.y), couleurFonce);
        droite[1] = sf::Vertex(sf::Vector2f(pos.x + TAILLE_CASE - 5, pos.y), sf::Color(couleurFonce.r, couleurFonce.g, couleurFonce.b, 100));
        droite[2] = sf::Vertex(sf::Vector2f(pos.x + TAILLE_CASE - 2, pos.y + TAILLE_CASE - 2), couleurFonce);
        droite[3] = sf::Vertex(sf::Vector2f(pos.x + TAILLE_CASE - 5, pos.y + TAILLE_CASE - 2), sf::Color(couleurFonce.r, couleurFonce.g, couleurFonce.b, 100));
        fenetre->draw(droite);
    }
}

void Rendu::dessinerGrille(const Grille& grille) {
    if (!fenetre) return;

    for (const auto& rect : fondGrille) {
        fenetre->draw(rect);
    }

    for (int y = 0; y < HAUTEUR_GRILLE; ++y) {
        for (int x = 0; x < LARGEUR_GRILLE; ++x) {
            sf::Color couleur = grille.obtenirCellules()[y][x];
            if (couleur != sf::Color::Transparent) {
                dessinerBloc(x, y, couleur);
            }
        }
    }

    sf::RectangleShape bordure(sf::Vector2f(LARGEUR_GRILLE * TAILLE_CASE + 2, HAUTEUR_GRILLE * TAILLE_CASE + 2));
    bordure.setPosition(DECALAGE_X - 1, DECALAGE_Y - 1);
    bordure.setFillColor(sf::Color::Transparent);
    bordure.setOutlineThickness(2);
    bordure.setOutlineColor(sf::Color::White);
    fenetre->draw(bordure);

    sf::RectangleShape bordureInterieure(sf::Vector2f(LARGEUR_GRILLE * TAILLE_CASE - 2, HAUTEUR_GRILLE * TAILLE_CASE - 2));
    bordureInterieure.setPosition(DECALAGE_X, DECALAGE_Y);
    bordureInterieure.setFillColor(sf::Color::Transparent);
    bordureInterieure.setOutlineThickness(1);
    bordureInterieure.setOutlineColor(sf::Color(100, 100, 120));
    fenetre->draw(bordureInterieure);
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
    texte.setOutlineColor(sf::Color::Black);
    texte.setOutlineThickness(1);
    fenetre->draw(texte);

    const auto& blocs = prochain.obtenirBlocs();
    for (const auto& bloc : blocs) {
        sf::Vector2f pos(DECALAGE_X + LARGEUR_GRILLE * TAILLE_CASE + 50 + bloc.x * TAILLE_CASE, DECALAGE_Y + 40 + bloc.y * TAILLE_CASE);
        caseForme.setPosition(pos);
        caseForme.setFillColor(prochain.obtenirCouleur());
        caseForme.setOutlineColor(sf::Color(100, 100, 100));
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
        caseForme.setOutlineColor(sf::Color(100, 100, 100));
        fenetre->draw(caseForme);
    }
}

void Rendu::dessinerHoldTetromino(const Tetromino& hold) {
    if (!fenetre || !policeChargee) return;

    sf::Text texte("HOLD", police, 20);
    texte.setPosition(DECALAGE_X + LARGEUR_GRILLE * TAILLE_CASE + 50, DECALAGE_Y + 100);
    texte.setFillColor(sf::Color::White);
    texte.setOutlineColor(sf::Color::Black);
    texte.setOutlineThickness(1);
    fenetre->draw(texte);

    const auto& blocs = hold.obtenirBlocs();
    for (const auto& bloc : blocs) {
        sf::Vector2f pos(DECALAGE_X + LARGEUR_GRILLE * TAILLE_CASE + 50 + bloc.x * TAILLE_CASE, DECALAGE_Y + 140 + bloc.y * TAILLE_CASE);
        caseForme.setPosition(pos);
        caseForme.setFillColor(hold.obtenirCouleur());
        caseForme.setOutlineColor(sf::Color(100, 100, 100));
        fenetre->draw(caseForme);
    }
}

void Rendu::dessinerScore(const GestionnaireScore& score) {
    if (!fenetre || !policeChargee) return;

    int x = DECALAGE_X + LARGEUR_GRILLE * TAILLE_CASE + 50;
    int y = DECALAGE_Y + 150;

    auto dessinerLigneScore = [&](const std::string& label, const std::string& valeur, sf::Color couleurLabel, sf::Color couleurValeur, int decalageY) {
        sf::Text texteLabel(label, police, 18);
        texteLabel.setPosition(x, y + decalageY);
        texteLabel.setFillColor(couleurLabel);
        texteLabel.setOutlineColor(sf::Color::Black);
        texteLabel.setOutlineThickness(1);
        fenetre->draw(texteLabel);

        sf::Text texteValeur(valeur, police, 20);
        texteValeur.setPosition(x, y + decalageY + 22);
        texteValeur.setFillColor(couleurValeur);
        texteValeur.setOutlineColor(sf::Color::Black);
        texteValeur.setOutlineThickness(1);
        texteValeur.setStyle(sf::Text::Bold);
        fenetre->draw(texteValeur);
    };

    dessinerLigneScore("SCORE", std::to_string(score.obtenirScore()), sf::Color(200, 200, 200), sf::Color::White, 0);
    dessinerLigneScore("MEILLEUR", std::to_string(score.obtenirMeilleurScore()), sf::Color(200, 200, 100), sf::Color::Yellow, 50);
    dessinerLigneScore("NIVEAU", std::to_string(score.obtenirNiveau()), sf::Color(100, 200, 200), sf::Color::Cyan, 100);
    dessinerLigneScore("LIGNES", std::to_string(score.obtenirLignesTotales()), sf::Color(100, 200, 100), sf::Color::Green, 150);

    if (score.obtenirNiveau() > 1) {
        int lignesPourProchainNiveau = 10 - (score.obtenirLignesTotales() % 10);
        if (lignesPourProchainNiveau == 10) lignesPourProchainNiveau = 0;
        sf::Text texteProchain("PROCHAIN NIVEAU: " + std::to_string(lignesPourProchainNiveau) + " lignes", police, 14);
        texteProchain.setPosition(x, y + 190);
        texteProchain.setFillColor(sf::Color(150, 150, 150));
        texteProchain.setOutlineColor(sf::Color::Black);
        texteProchain.setOutlineThickness(1);
        fenetre->draw(texteProchain);
    }
}

void Rendu::dessinerMenu() {
    if (!fenetre || !policeChargee) return;

    for (const auto& rect : fondGrille) {
        fenetre->draw(rect);
    }

    sf::Text titre("TETRIS", police, 70);
    titre.setPosition(DECALAGE_X + LARGEUR_GRILLE * TAILLE_CASE / 2 - 100, DECALAGE_Y + 30);
    titre.setFillColor(sf::Color::Cyan);
    titre.setOutlineColor(sf::Color::Blue);
    titre.setOutlineThickness(2);
    titre.setStyle(sf::Text::Bold);
    fenetre->draw(titre);

    sf::Text sousTitre("C++ / SFML", police, 20);
    sousTitre.setPosition(DECALAGE_X + LARGEUR_GRILLE * TAILLE_CASE / 2 - 50, DECALAGE_Y + 100);
    sousTitre.setFillColor(sf::Color(150, 150, 150));
    fenetre->draw(sousTitre);

    sf::RectangleShape cadre(sf::Vector2f(300, 280));
    cadre.setPosition(DECALAGE_X + 20, DECALAGE_Y + 140);
    cadre.setFillColor(sf::Color(20, 20, 30, 200));
    cadre.setOutlineColor(sf::Color(100, 100, 120));
    cadre.setOutlineThickness(2);
    fenetre->draw(cadre);

    sf::Text instruction("APPUYEZ SUR ENTREE", police, 24);
    instruction.setPosition(DECALAGE_X + 40, DECALAGE_Y + 160);
    instruction.setFillColor(sf::Color::White);
    instruction.setOutlineColor(sf::Color::Black);
    instruction.setOutlineThickness(1);
    fenetre->draw(instruction);

    sf::Text pourJouer("POUR JOUER", police, 24);
    pourJouer.setPosition(DECALAGE_X + 60, DECALAGE_Y + 195);
    pourJouer.setFillColor(sf::Color::White);
    pourJouer.setOutlineColor(sf::Color::Black);
    pourJouer.setOutlineThickness(1);
    fenetre->draw(pourJouer);

    sf::Text commandes("CONTROLES:", police, 18);
    commandes.setPosition(DECALAGE_X + 40, DECALAGE_Y + 250);
    commandes.setFillColor(sf::Color::Cyan);
    commandes.setStyle(sf::Text::Bold);
    fenetre->draw(commandes);

    std::vector<std::pair<std::string, std::string>> controles = {
        {"Fleches", "Deplacer"},
        {"Haut / X", "Rotation horaire"},
        {"Z", "Rotation anti-horaire"},
        {"Bas", "Accelerer"},
        {"Espace", "Chute immediate"},
        {"C / Shift", "Hold (reserve)"},
        {"P", "Pause / Reprendre"},
        {"Echap", "Quitter"}
    };

    for (size_t i = 0; i < controles.size(); ++i) {
        sf::Text touche(controles[i].first, police, 16);
        touche.setPosition(DECALAGE_X + 40, DECALAGE_Y + 275 + i * 22);
        touche.setFillColor(sf::Color::Yellow);
        touche.setOutlineColor(sf::Color::Black);
        touche.setOutlineThickness(1);
        fenetre->draw(touche);

        sf::Text action("-> " + controles[i].second, police, 16);
        action.setPosition(DECALAGE_X + 130, DECALAGE_Y + 275 + i * 22);
        action.setFillColor(sf::Color(200, 200, 200));
        action.setOutlineColor(sf::Color::Black);
        action.setOutlineThickness(1);
        fenetre->draw(action);
    }
}

void Rendu::dessinerPause() {
    if (!fenetre || !policeChargee) return;

    sf::RectangleShape overlay(sf::Vector2f(LARGEUR_GRILLE * TAILLE_CASE, HAUTEUR_GRILLE * TAILLE_CASE));
    overlay.setPosition(DECALAGE_X, DECALAGE_Y);
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    fenetre->draw(overlay);

    sf::Text texte("PAUSE", police, 60);
    texte.setPosition(DECALAGE_X + LARGEUR_GRILLE * TAILLE_CASE / 2 - 80, DECALAGE_Y + HAUTEUR_GRILLE * TAILLE_CASE / 2 - 70);
    texte.setFillColor(sf::Color::Yellow);
    texte.setOutlineColor(sf::Color::Black);
    texte.setOutlineThickness(2);
    texte.setStyle(sf::Text::Bold);
    fenetre->draw(texte);

    sf::Text instruction("APPUYEZ SUR P POUR REPRENDRE", police, 22);
    instruction.setPosition(DECALAGE_X + 30, DECALAGE_Y + HAUTEUR_GRILLE * TAILLE_CASE / 2 + 20);
    instruction.setFillColor(sf::Color::White);
    instruction.setOutlineColor(sf::Color::Black);
    instruction.setOutlineThickness(1);
    fenetre->draw(instruction);
}

void Rendu::dessinerGameOver(int scoreFinal, int meilleurScore) {
    if (!fenetre || !policeChargee) return;

    sf::RectangleShape overlay(sf::Vector2f(LARGEUR_GRILLE * TAILLE_CASE, HAUTEUR_GRILLE * TAILLE_CASE));
    overlay.setPosition(DECALAGE_X, DECALAGE_Y);
    overlay.setFillColor(sf::Color(0, 0, 0, 220));
    fenetre->draw(overlay);

    sf::RectangleShape cadre(sf::Vector2f(350, 300));
    cadre.setPosition(DECALAGE_X + LARGEUR_GRILLE * TAILLE_CASE / 2 - 175, DECALAGE_Y + HAUTEUR_GRILLE * TAILLE_CASE / 2 - 150);
    cadre.setFillColor(sf::Color(30, 20, 20, 240));
    cadre.setOutlineColor(sf::Color::Red);
    cadre.setOutlineThickness(3);
    fenetre->draw(cadre);

    sf::Text texte("GAME OVER", police, 55);
    texte.setPosition(DECALAGE_X + LARGEUR_GRILLE * TAILLE_CASE / 2 - 120, DECALAGE_Y + HAUTEUR_GRILLE * TAILLE_CASE / 2 - 130);
    texte.setFillColor(sf::Color::Red);
    texte.setOutlineColor(sf::Color::Black);
    texte.setOutlineThickness(2);
    texte.setStyle(sf::Text::Bold);
    fenetre->draw(texte);

    sf::Text texteScore("SCORE FINAL", police, 20);
    texteScore.setPosition(DECALAGE_X + LARGEUR_GRILLE * TAILLE_CASE / 2 - 80, DECALAGE_Y + HAUTEUR_GRILLE * TAILLE_CASE / 2 - 50);
    texteScore.setFillColor(sf::Color(200, 200, 200));
    texteScore.setOutlineColor(sf::Color::Black);
    texteScore.setOutlineThickness(1);
    fenetre->draw(texteScore);

    sf::Text valeurScore(std::to_string(scoreFinal), police, 40);
    valeurScore.setPosition(DECALAGE_X + LARGEUR_GRILLE * TAILLE_CASE / 2 - 60, DECALAGE_Y + HAUTEUR_GRILLE * TAILLE_CASE / 2 - 20);
    valeurScore.setFillColor(sf::Color::White);
    valeurScore.setOutlineColor(sf::Color::Black);
    valeurScore.setOutlineThickness(1);
    valeurScore.setStyle(sf::Text::Bold);
    fenetre->draw(valeurScore);

    sf::Text texteMeilleur("MEILLEUR SCORE", police, 18);
    texteMeilleur.setPosition(DECALAGE_X + LARGEUR_GRILLE * TAILLE_CASE / 2 - 75, DECALAGE_Y + HAUTEUR_GRILLE * TAILLE_CASE / 2 + 30);
    texteMeilleur.setFillColor(sf::Color(200, 200, 100));
    texteMeilleur.setOutlineColor(sf::Color::Black);
    texteMeilleur.setOutlineThickness(1);
    fenetre->draw(texteMeilleur);

    sf::Text valeurMeilleur(std::to_string(meilleurScore), police, 28);
    valeurMeilleur.setPosition(DECALAGE_X + LARGEUR_GRILLE * TAILLE_CASE / 2 - 50, DECALAGE_Y + HAUTEUR_GRILLE * TAILLE_CASE / 2 + 55);
    valeurMeilleur.setFillColor(sf::Color::Yellow);
    valeurMeilleur.setOutlineColor(sf::Color::Black);
    valeurMeilleur.setOutlineThickness(1);
    valeurMeilleur.setStyle(sf::Text::Bold);
    fenetre->draw(valeurMeilleur);

    if (scoreFinal >= meilleurScore && scoreFinal > 0) {
        sf::Text texteNouveau("NOUVEAU RECORD !", police, 22);
        texteNouveau.setPosition(DECALAGE_X + LARGEUR_GRILLE * TAILLE_CASE / 2 - 90, DECALAGE_Y + HAUTEUR_GRILLE * TAILLE_CASE / 2 + 95);
        texteNouveau.setFillColor(sf::Color::Cyan);
        texteNouveau.setOutlineColor(sf::Color::Black);
        texteNouveau.setOutlineThickness(2);
        texteNouveau.setStyle(sf::Text::Bold);
        fenetre->draw(texteNouveau);
    }

    sf::Text instruction("ENTREE: REJOUER  ECHAP: QUITTER", police, 18);
    instruction.setPosition(DECALAGE_X + 40, DECALAGE_Y + HAUTEUR_GRILLE * TAILLE_CASE / 2 + 140);
    instruction.setFillColor(sf::Color::White);
    instruction.setOutlineColor(sf::Color::Black);
    instruction.setOutlineThickness(1);
    fenetre->draw(instruction);
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

void Rendu::effacer() {
    if (fenetre) {
        fenetre->clear(sf::Color(15, 15, 25));
    }
}

void Rendu::afficher() {
    if (fenetre) {
        dessinerParticules();
        fenetre->display();
    }
}