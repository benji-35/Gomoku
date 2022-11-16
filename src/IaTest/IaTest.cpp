/*
** EPITECH PROJECT, 2022
** Gomoku
** File description:
** IaTest
*/

#include "IaTest.hpp"

Gomoku::IaTest::IaTest() : AbstractIA("My IA", "1.0.0", "Benji-35", "France", true) {

}

Gomoku::IaTest::~IaTest() {

}

Gomoku::Vector Gomoku::IaTest::chooseBestMove() {
    Vector result = getWinPosAI();
    if (result.getX() != -1 && result.getY() != -1)
        return result;
    result = getWinPosPlayer();
    if (result.getX() != -1 && result.getY() != -1)
        return result;
    
    int x = std::rand() % getBoardWidth();
    int y = std::rand() % getBoardHeight();

    while (!canMoveAtPos(x, y)) {
        x = std::rand() % getBoardWidth();
        y = std::rand() % getBoardHeight();
    }
    result.setX(x);
    result.setY(y);
    return result;
}
