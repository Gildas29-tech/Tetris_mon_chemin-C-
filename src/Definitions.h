#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <utility>
#include <vector>

constexpr int LARGEUR_GRILLE = 10;
constexpr int HAUTEUR_GRILLE = 20;
constexpr int TAILLE_CASE = 30;
constexpr int DECALAGE_X = 50;
constexpr int DECALAGE_Y = 50;

enum class TypeTetromino { I, J, L, O, S, T, Z, COUNT };

const std::array<sf::Color, 7> COULEURS_TETROMINOS = {
    sf::Color::Cyan,
    sf::Color::Blue,
    sf::Color(255, 165, 0),
    sf::Color::Yellow,
    sf::Color::Green,
    sf::Color::Magenta,
    sf::Color::Red
};

constexpr std::array<std::array<std::pair<int, int>, 4>, 7> FORMES_TETROMINOS = {{
    {{{0,0}, {1,0}, {2,0}, {3,0}}},
    {{{0,0}, {0,1}, {1,1}, {2,1}}},
    {{{2,0}, {0,1}, {1,1}, {2,1}}},
    {{{0,0}, {1,0}, {0,1}, {1,1}}},
    {{{1,0}, {2,0}, {0,1}, {1,1}}},
    {{{1,0}, {0,1}, {1,1}, {2,1}}},
    {{{0,0}, {1,0}, {1,1}, {2,1}}}
}};

enum class EtatJeu { MENU, JEU, PAUSE, GAME_OVER };

struct Position {
    int x, y;
    bool operator==(const Position& autre) const { return x == autre.x && y == autre.y; }
};