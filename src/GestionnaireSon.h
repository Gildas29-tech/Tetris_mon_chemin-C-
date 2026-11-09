#pragma once
#include <SFML/Audio.hpp>
#include <array>

class GestionnaireSon {
public:
    GestionnaireSon();
    ~GestionnaireSon();

    void jouerRotation();
    void jouerDeplacement();
    void jouerVerrouillage();
    void jouerLigne(int nbLignes);
    void jouerGameOver();
    void jouerNiveau();
    void definirVolume(float volume);

private:
    sf::SoundBuffer bufferRotation;
    sf::SoundBuffer bufferDeplacement;
    sf::SoundBuffer bufferVerrouillage;
    sf::SoundBuffer bufferLigne1;
    sf::SoundBuffer bufferLigne2;
    sf::SoundBuffer bufferLigne3;
    sf::SoundBuffer bufferLigne4;
    sf::SoundBuffer bufferGameOver;
    sf::SoundBuffer bufferNiveau;

    sf::Sound sonEffet;

    void genererSonSimple(sf::SoundBuffer& buffer, float frequence, float duree, float volume = 50.f);
    void genererSonLigne(sf::SoundBuffer& buffer, int nbLignes);
};