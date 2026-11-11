#include "GestionnaireSon.h"
#include <algorithm>
#include <cmath>
#include <vector>

GestionnaireSon::GestionnaireSon() {
    genererSonSimple(bufferRotation, 440.0f, 0.1f, 30.f);
    genererSonSimple(bufferDeplacement, 220.0f, 0.05f, 20.f);
    genererSonSimple(bufferVerrouillage, 150.0f, 0.15f, 40.f);
    genererSonLigne(bufferLigne1, 1);
    genererSonLigne(bufferLigne2, 2);
    genererSonLigne(bufferLigne3, 3);
    genererSonLigne(bufferLigne4, 4);
    genererSonSimple(bufferGameOver, 100.0f, 0.5f, 50.f);
    genererSonSimple(bufferNiveau, 880.0f, 0.3f, 40.f);
}

GestionnaireSon::~GestionnaireSon() {}

void GestionnaireSon::genererSonSimple(sf::SoundBuffer& buffer, float frequence, float duree, float volume) {
    const unsigned int tauxEchantillonnage = 44100;
    const unsigned int nbEchantillons = static_cast<unsigned int>(tauxEchantillonnage * duree);
    std::vector<sf::Int16> echantillons(nbEchantillons);

    for (unsigned int i = 0; i < nbEchantillons; ++i) {
        float t = static_cast<float>(i) / tauxEchantillonnage;
        float enveloppe = 1.0f - t / duree;
        float valeur = std::sin(2.0f * 3.14159f * frequence * t) * enveloppe * volume * 327.67f;
        echantillons[i] = static_cast<sf::Int16>(std::max(-32768.0f, std::min(32767.0f, valeur)));
    }

    buffer.loadFromSamples(echantillons.data(), nbEchantillons, 1, tauxEchantillonnage);
}

void GestionnaireSon::genererSonLigne(sf::SoundBuffer& buffer, int nbLignes) {
    const unsigned int tauxEchantillonnage = 44100;
    const float duree = 0.3f + nbLignes * 0.1f;
    const unsigned int nbEchantillons = static_cast<unsigned int>(tauxEchantillonnage * duree);
    std::vector<sf::Int16> echantillons(nbEchantillons);

    float frequenceBase = 300.0f + nbLignes * 150.0f;

    for (unsigned int i = 0; i < nbEchantillons; ++i) {
        float t = static_cast<float>(i) / tauxEchantillonnage;
        float enveloppe = 1.0f - t / duree;
        float valeur = 0.0f;

        for (int h = 1; h <= nbLignes; ++h) {
            valeur += std::sin(2.0f * 3.14159f * (frequenceBase * h) * t) * (1.0f / h);
        }

        valeur *= enveloppe * 40.f * 327.67f;
        echantillons[i] = static_cast<sf::Int16>(std::max(-32768.0f, std::min(32767.0f, valeur)));
    }

    buffer.loadFromSamples(echantillons.data(), nbEchantillons, 1, tauxEchantillonnage);
}

void GestionnaireSon::jouerRotation() {
    sonEffet.setBuffer(bufferRotation);
    sonEffet.play();
}

void GestionnaireSon::jouerDeplacement() {
    sonEffet.setBuffer(bufferDeplacement);
    sonEffet.play();
}

void GestionnaireSon::jouerVerrouillage() {
    sonEffet.setBuffer(bufferVerrouillage);
    sonEffet.play();
}

void GestionnaireSon::jouerLigne(int nbLignes) {
    switch (nbLignes) {
        case 1: sonEffet.setBuffer(bufferLigne1); break;
        case 2: sonEffet.setBuffer(bufferLigne2); break;
        case 3: sonEffet.setBuffer(bufferLigne3); break;
        case 4: sonEffet.setBuffer(bufferLigne4); break;
        default: return;
    }
    sonEffet.play();
}

void GestionnaireSon::jouerGameOver() {
    sonEffet.setBuffer(bufferGameOver);
    sonEffet.play();
}

void GestionnaireSon::jouerNiveau() {
    sonEffet.setBuffer(bufferNiveau);
    sonEffet.play();
}

void GestionnaireSon::definirVolume(float volume) {
    sonEffet.setVolume(volume);
}