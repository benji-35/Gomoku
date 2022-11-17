/*
** EPITECH PROJECT, 2022
** Gomoku
** File description:
** Main
*/

#include "Gomoku.hpp"
#include "IaTest/IaTest.hpp"

int main() {
    Gomoku::Game game;
    std::shared_ptr<Gomoku::IaTest> nIA = std::make_shared<Gomoku::IaTest>();

    game.setIA(nIA);
    game.start();
}
