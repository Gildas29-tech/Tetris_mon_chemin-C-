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

private:
    int score;
    int meilleurScore;
    int niveau;
    int lignesTotales;
    float vitesse;
    std::string fichierScore;

    void chargerMeilleurScore();
    void mettreAJourNiveau();
};