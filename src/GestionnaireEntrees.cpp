#include "GestionnaireEntrees.h"
#include <SFML/Window/Event.hpp>

GestionnaireEntrees::GestionnaireEntrees() {
    for (int i = 0; i < sf::Keyboard::KeyCount; ++i) {
        touchePrecedente[i] = false;
    }
}

GestionnaireEntrees::Action GestionnaireEntrees::traiterEvenements(sf::RenderWindow& fenetre) {
    sf::Event evenement;
    while (fenetre.pollEvent(evenement)) {
        if (evenement.type == sf::Event::Closed) {
            return Action::QUITTER;
        }
    }

    bool gauche = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    bool droite = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    bool bas = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    bool haut = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    bool x = sf::Keyboard::isKeyPressed(sf::Keyboard::X);
    bool z = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
    bool espace = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    bool p = sf::Keyboard::isKeyPressed(sf::Keyboard::P);
    bool entree = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
    bool echap = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
    bool c = sf::Keyboard::isKeyPressed(sf::Keyboard::C);
    bool shiftGauche = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

    if (echap) return Action::QUITTER;
    if (entree) return Action::DEMARRER;
    if (p) return Action::PAUSE;
    if (gauche) return Action::GAUCHE;
    if (droite) return Action::DROITE;
    if (bas) return Action::BAS;
    if (haut || x) return Action::ROTATION_HORAIRE;
    if (z) return Action::ROTATION_ANTI_HORAIRE;
    if (espace) return Action::CHUTE_IMMEDIATE;
    if (c || shiftGauche) return Action::HOLD;

    return Action::RIEN;
}

bool GestionnaireEntrees::estAppuye(sf::Keyboard::Key touche) const {
    return sf::Keyboard::isKeyPressed(touche);
}