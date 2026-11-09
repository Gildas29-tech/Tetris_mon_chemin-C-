#include "GestionnaireScore.h"
#include <fstream>

GestionnaireScore::GestionnaireScore() : score(0), meilleurScore(0), niveau(1), lignesTotales(0), vitesse(1.0f), fichierScore("meilleur_score.txt") {
    chargerMeilleurScore();
}

GestionnaireScore::~GestionnaireScore() {
    sauvegarder();
}

void GestionnaireScore::ajouterScore(int lignes) {
    static const int pointsParLignes[5] = {0, 100, 300, 500, 800};
    if (lignes >= 1 && lignes <= 4) {
        score += pointsParLignes[lignes] * niveau;
        lignesTotales += lignes;
        mettreAJourNiveau();
        if (score > meilleurScore) {
            meilleurScore = score;
        }
    }
}

int GestionnaireScore::obtenirScore() const {
    return score;
}

int GestionnaireScore::obtenirMeilleurScore() const {
    return meilleurScore;
}

int GestionnaireScore::obtenirNiveau() const {
    return niveau;
}

int GestionnaireScore::obtenirLignesTotales() const {
    return lignesTotales;
}

float GestionnaireScore::obtenirVitesse() const {
    return vitesse;
}

void GestionnaireScore::reinitialiser() {
    score = 0;
    niveau = 1;
    lignesTotales = 0;
    vitesse = 1.0f;
}

void GestionnaireScore::sauvegarder() {
    std::ofstream fichier(fichierScore);
    if (fichier.is_open()) {
        fichier << meilleurScore;
    }
}

void GestionnaireScore::chargerMeilleurScore() {
    std::ifstream fichier(fichierScore);
    if (fichier.is_open()) {
        fichier >> meilleurScore;
    }
}

void GestionnaireScore::mettreAJourNiveau() {
    niveau = lignesTotales / 10 + 1;
    vitesse = 1.0f - (niveau - 1) * 0.1f;
    if (vitesse < 0.1f) vitesse = 0.1f;
}