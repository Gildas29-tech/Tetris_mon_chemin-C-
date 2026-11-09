#pragma once
#include <SFML/Window.hpp>

class GestionnaireEntrees {
public:
    enum class Action { RIEN, GAUCHE, DROITE, BAS, ROTATION_HORAIRE, ROTATION_ANTI_HORAIRE, CHUTE_IMMEDIATE, PAUSE, DEMARRER, QUITTER };

    GestionnaireEntrees();

    Action traiterEvenements(sf::RenderWindow& fenetre);
    bool estAppuye(sf::Keyboard::Key touche) const;

private:
    bool touchePrecedente[sf::Keyboard::KeyCount];
};