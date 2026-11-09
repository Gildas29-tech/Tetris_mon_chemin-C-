#include "GestionnaireScore.h"
#include <fstream>

GestionnaireScore::GestionnaireScore() : score(0), meilleurScore(0), niveau(1), lignesTotales(0), vitesse(1.0f), fichierScore("meilleur_score.txt"),
    partiesJouees(0), lignesTotalGlobal(0), meilleurNiveau(1), meilleurScorePartie(0), fichierStats("stats.txt") {
    chargerMeilleurScore();
    chargerStats();
}

GestionnaireScore::~GestionnaireScore() {
    sauvegarder();
    sauvegarderStats();
}

void GestionnaireScore::ajouterScore(int lignes) {
    static const int pointsParLignes[5] = {0, 100, 300, 500, 800};
    if (lignes >= 1 && lignes <= 4) {
        score += pointsParLignes[lignes] * niveau;
        lignesTotales += lignes;
        lignesTotalGlobal += lignes;
        mettreAJourNiveau();
        if (score > meilleurScore) {
            meilleurScore = score;
        }
        if (score > meilleurScorePartie) {
            meilleurScorePartie = score;
        }
        if (niveau > meilleurNiveau) {
            meilleurNiveau = niveau;
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

void GestionnaireScore::nouvellePartie() {
    partiesJouees++;
}

void GestionnaireScore::finPartie() {
    sauvegarderStats();
}

int GestionnaireScore::obtenirPartiesJouees() const {
    return partiesJouees;
}

int GestionnaireScore::obtenirLignesTotalGlobal() const {
    return lignesTotalGlobal;
}

int GestionnaireScore::obtenirMeilleurNiveau() const {
    return meilleurNiveau;
}

int GestionnaireScore::obtenirMeilleurScorePartie() const {
    return meilleurScorePartie;
}

void GestionnaireScore::chargerStats() {
    std::ifstream fichier(fichierStats);
    if (fichier.is_open()) {
        fichier >> partiesJouees >> lignesTotalGlobal >> meilleurNiveau >> meilleurScorePartie;
    }
}

void GestionnaireScore::sauvegarderStats() {
    std::ofstream fichier(fichierStats);
    if (fichier.is_open()) {
        fichier << partiesJouees << " " << lignesTotalGlobal << " " << meilleurNiveau << " " << meilleurScorePartie;
    }
}