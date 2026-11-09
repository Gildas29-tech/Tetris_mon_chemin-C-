#pragma once
#include <fstream>
#include <string>

class GestionnaireScore {
public:
    GestionnaireScore();
    ~GestionnaireScore();

    void ajouterScore(int lignes);
    int obtenirScore() const;
    int obtenirMeilleurScore() const;
    int obtenirNiveau() const;
    int obtenirLignesTotales() const;
    float obtenirVitesse() const;
    void reinitialiser();
    void sauvegarder();
    void nouvellePartie();
    void finPartie();

    int obtenirPartiesJouees() const;
    int obtenirLignesTotalGlobal() const;
    int obtenirMeilleurNiveau() const;
    int obtenirMeilleurScorePartie() const;

private:
    int score;
    int meilleurScore;
    int niveau;
    int lignesTotales;
    float vitesse;
    std::string fichierScore;

    int partiesJouees;
    int lignesTotalGlobal;
    int meilleurNiveau;
    int meilleurScorePartie;
    std::string fichierStats;

    void chargerMeilleurScore();
    void chargerStats();
    void sauvegarderStats();
    void mettreAJourNiveau();
};