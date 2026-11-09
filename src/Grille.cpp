#include "Grille.h"

Grille::Grille() {
    reinitialiser();
}

bool Grille::estValide(const Tetromino& tetromino) const {
    for (const auto& bloc : tetromino.obtenirBlocs()) {
        if (bloc.x < 0 || bloc.x >= LARGEUR_GRILLE || bloc.y >= HAUTEUR_GRILLE) {
            return false;
        }
        if (bloc.y >= 0 && cellules[bloc.y][bloc.x] != sf::Color::Transparent) {
            return false;
        }
    }
    return true;
}

void Grille::verrouiller(const Tetromino& tetromino) {
    for (const auto& bloc : tetromino.obtenirBlocs()) {
        if (bloc.y >= 0 && bloc.y < HAUTEUR_GRILLE && bloc.x >= 0 && bloc.x < LARGEUR_GRILLE) {
            cellules[bloc.y][bloc.x] = tetromino.obtenirCouleur();
        }
    }
}

int Grille::supprimerLignesCompletes() {
    int lignesSupprimees = 0;
    for (int y = HAUTEUR_GRILLE - 1; y >= 0; --y) {
        bool complete = true;
        for (int x = 0; x < LARGEUR_GRILLE; ++x) {
            if (cellules[y][x] == sf::Color::Transparent) {
                complete = false;
                break;
            }
        }
        if (complete) {
            for (int yy = y; yy > 0; --yy) {
                for (int x = 0; x < LARGEUR_GRILLE; ++x) {
                    cellules[yy][x] = cellules[yy - 1][x];
                }
            }
            for (int x = 0; x < LARGEUR_GRILLE; ++x) {
                cellules[0][x] = sf::Color::Transparent;
            }
            ++lignesSupprimees;
            ++y;
        }
    }
    return lignesSupprimees;
}

bool Grille::estPleine(int x, int y) const {
    return y >= 0 && y < HAUTEUR_GRILLE && x >= 0 && x < LARGEUR_GRILLE && cellules[y][x] != sf::Color::Transparent;
}

void Grille::reinitialiser() {
    for (auto& ligne : cellules) {
        ligne.fill(sf::Color::Transparent);
    }
}

const std::array<std::array<sf::Color, LARGEUR_GRILLE>, HAUTEUR_GRILLE>& Grille::obtenirCellules() const {
    return cellules;
}