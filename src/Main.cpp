/*
** EPITECH PROJECT, 2022
** Gomoku
** File description:
** Main
*/

#include "Gomoku.hpp"
#include "BasicAI/BasicAI.hpp"
#include "BestMinMax/BestMinMax.hpp"
#include "BenjiAI/BenjiAI.hpp"

int main() {
    Gomoku::Game game;
    std::shared_ptr<Gomoku::BenjiAI> nIA = std::make_shared<Gomoku::BenjiAI>();

    game.setIA(nIA);
    game.start();
}
