/*
** EPITECH PROJECT, 2022
** Gomoku
** File description:
** BenjiAI
*/

#include "BenjiAI.hpp"

Gomoku::BenjiAI::BenjiAI() : AbstractIA("BenjiAI", "1.0.0", "benji-35", "France", true) {}

Gomoku::BenjiAI::~BenjiAI() {}

Gomoku::Vector Gomoku::BenjiAI::chooseBestMove() {
    auto poses = getPoses();
    int bestAI = 0;
    int bestGame = 0;

    if (poses.size() == 0)
        return getRandomMove();

    for (std::size_t i = 0; i < poses.size(); i++) {
        Communication::sendDebug("poses[" + std::to_string(i) + "], at: " + poses[i].pos.to_string() + " , scoreAI = " + std::to_string(poses[i].scoreAI) + " , scoreGame = " + std::to_string(poses[i].scoreGame));
        if (poses[i].scoreAI > 500) {
            bestAI = i;
            break;
        }
        if (poses[i].scoreAI > poses[bestAI].scoreAI) {
            bestAI = i;
        }
        if (poses[i].scoreGame > poses[bestGame].scoreGame) {
            bestGame = i;
        }
    }
    if (poses[bestAI].scoreAI >= poses[bestGame].scoreGame || poses[bestAI].scoreAI >= 500) {
        return poses[bestAI].pos;
    } else {
        return poses[bestGame].pos;
    }
}

Gomoku::Vector Gomoku::BenjiAI::getRandomMove() {
    Vector result;

    result.setX(rand() % getBoardWidth());
    result.setY(rand() % getBoardHeight());

    while (whoPlayedAt(result) != MoveType::NONE) {
        result.setX(rand() % getBoardWidth());
        result.setY(rand() % getBoardHeight());
    }

    return result;
}

std::vector<Gomoku::BenjiAI::PosCalculated> Gomoku::BenjiAI::getPoses() {
    std::vector<PosCalculated> poses;
    for (int y = 0; y < getBoardHeight(); y++) {
        for (int x = 0; x < getBoardWidth(); x++) {
            if (shouldCalculate(Vector(x, y))) {
                PosCalculated calc;
                calc.pos = Vector(x, y);
                calc.scoreAI = 0;
                calc.scoreGame = 0;
                calculHorAt(Vector(x, y), calc);
                calculVerAt(Vector(x, y), calc);
                calculDiag1At(Vector(x, y), calc);
                calculDiag2At(Vector(x, y), calc);
                poses.push_back(calc);
            }
        }
    }
    return poses;
}

bool Gomoku::BenjiAI::shouldCalculate(Vector pos) {
    if (whoPlayedAt(pos) != MoveType::NONE)
        return false;
    if (whoPlayedAt(Vector(pos.getX() + 1, pos.getY())) != MoveType::NONE)
        return true;
    if (whoPlayedAt(Vector(pos.getX() - 1, pos.getY())) != MoveType::NONE)
        return true;
    if (whoPlayedAt(Vector(pos.getX(), pos.getY() + 1)) != MoveType::NONE)
        return true;
    if (whoPlayedAt(Vector(pos.getX(), pos.getY() - 1)) != MoveType::NONE)
        return true;
    if (whoPlayedAt(Vector(pos.getX() + 1, pos.getY() + 1)) != MoveType::NONE)
        return true;
    if (whoPlayedAt(Vector(pos.getX() - 1, pos.getY() - 1)) != MoveType::NONE)
        return true;
    if (whoPlayedAt(Vector(pos.getX() + 1, pos.getY() - 1)) != MoveType::NONE)
        return true;
    if (whoPlayedAt(Vector(pos.getX() - 1, pos.getY() + 1)) != MoveType::NONE)
        return true;
    return false;
}

void Gomoku::BenjiAI::calculHorAt(Vector pos, PosCalculated &calc) {
    int scoreAI = 1;
    int scoreGame = 1;
    int x = pos.getX();
    int y = pos.getY();
    int i = 1;

    while (whoPlayedAt(Vector(x + i, y)) == MoveType::IA_MOVE) {
        scoreAI++;
        i++;
    }
    i = 1;
    while (whoPlayedAt(Vector(x - i, y)) == MoveType::IA_MOVE) {
        scoreAI++;
        i++;
    }
    i = 1;
    while (whoPlayedAt(Vector(x + i, y)) == MoveType::GAME_MOVE) {
        scoreGame++;
        i++;
    }
    i = 1;
    while (whoPlayedAt(Vector(x - i, y)) == MoveType::GAME_MOVE) {
        scoreGame++;
        i++;
    }
    if (scoreAI >= 5)
        scoreAI *= 100;
    if (scoreGame >= 5)
        scoreGame *= 100;
    if (scoreAI == 4)
        scoreAI *= 10;
    if (scoreGame == 4)
        scoreGame *= 10;
    if (isClosePositionHor(pos, MoveType::IA_MOVE))
        calc.scoreAI += scoreAI;
    if (isClosePositionHor(pos, MoveType::GAME_MOVE))
        calc.scoreGame += scoreGame;
}

void Gomoku::BenjiAI::calculVerAt(Vector pos, PosCalculated &calc) {
    int scoreAI = 1;
    int scoreGame = 1;
    int x = pos.getX();
    int y = pos.getY();
    int i = 1;

    while (whoPlayedAt(Vector(x, y + i)) == MoveType::IA_MOVE) {
        scoreAI++;
        i++;
    }
    i = 1;
    while (whoPlayedAt(Vector(x, y - i)) == MoveType::IA_MOVE) {
        scoreAI++;
        i++;
    }
    i = 1;
    while (whoPlayedAt(Vector(x, y + i)) == MoveType::GAME_MOVE) {
        scoreGame++;
        i++;
    }
    i = 1;
    while (whoPlayedAt(Vector(x, y - i)) == MoveType::GAME_MOVE) {
        scoreGame++;
        i++;
    }
    if (scoreAI >= 5)
        scoreAI *= 100;
    if (scoreGame >= 5)
        scoreGame *= 100;
    if (scoreAI == 4)
        scoreAI *= 10;
    if (scoreGame == 4)
        scoreGame *= 10;
    if (isClosePositionVer(pos, MoveType::IA_MOVE))
        calc.scoreAI += scoreAI;
    if (isClosePositionVer(pos, MoveType::GAME_MOVE))
        calc.scoreGame += scoreGame;
}

void Gomoku::BenjiAI::calculDiag1At(Vector pos, PosCalculated &calc) {
    int scoreAI = 1;
    int scoreGame = 1;
    int x = pos.getX();
    int y = pos.getY();
    int i = 1;

    while (whoPlayedAt(Vector(x + i, y + i)) == MoveType::IA_MOVE) {
        scoreAI++;
        i++;
    }
    i = 1;
    while (whoPlayedAt(Vector(x - i, y - i)) == MoveType::IA_MOVE) {
        scoreAI++;
        i++;
    }
    i = 1;
    while (whoPlayedAt(Vector(x + i, y + i)) == MoveType::GAME_MOVE) {
        scoreGame++;
        i++;
    }
    i = 1;
    while (whoPlayedAt(Vector(x - i, y - i)) == MoveType::GAME_MOVE) {
        scoreGame++;
        i++;
    }
    if (scoreAI >= 5)
        scoreAI *= 100;
    if (scoreGame >= 5)
        scoreGame *= 100;
    if (scoreAI == 4)
        scoreAI *= 10;
    if (scoreGame == 4)
        scoreGame *= 10;
    if (isClosePositionDiag1(pos, MoveType::IA_MOVE))
        calc.scoreAI += scoreAI;
    if (isClosePositionDiag1(pos, MoveType::GAME_MOVE))
        calc.scoreGame += scoreGame;
}

void Gomoku::BenjiAI::calculDiag2At(Vector pos, PosCalculated &calc) {
    int scoreAI = 1;
    int scoreGame = 1;
    int x = pos.getX();
    int y = pos.getY();
    int i = 1;

    while (whoPlayedAt(Vector(x + i, y - i)) == MoveType::IA_MOVE) {
        scoreAI++;
        i++;
    }
    i = 1;
    while (whoPlayedAt(Vector(x - i, y + i)) == MoveType::IA_MOVE) {
        scoreAI++;
        i++;
    }
    i = 1;
    while (whoPlayedAt(Vector(x + i, y - i)) == MoveType::GAME_MOVE) {
        scoreGame++;
        i++;
    }
    i = 1;
    while (whoPlayedAt(Vector(x - i, y + i)) == MoveType::GAME_MOVE) {
        scoreGame++;
        i++;
    }
    if (scoreAI >= 5)
        scoreAI *= 100;
    if (scoreGame >= 5)
        scoreGame *= 100;
    if (scoreAI == 4)
        scoreAI *= 10;
    if (scoreGame == 4)
        scoreGame *= 10;
    if (isClosePositionDiag2(pos, MoveType::IA_MOVE))
        calc.scoreAI += scoreAI;
    if (isClosePositionDiag2(pos, MoveType::GAME_MOVE))
        calc.scoreGame += scoreGame;
}

bool Gomoku::BenjiAI::isClosePositionHor(Vector pos, MoveType player) {
    int x = pos.getX();
    int y = pos.getY();
    int left = 0;
    int right = 0;

    for (int i = 0; i < 5; i++) {
        if (whoPlayedAt(Vector(x - i, y)) == player || (whoPlayedAt(Vector(x - i, y)) == MoveType::NONE && x - i > 0))
            left++;
        if (whoPlayedAt(Vector(x + i, y)) == player || (whoPlayedAt(Vector(x + i, y)) == MoveType::NONE && x + i < getBoardWidth()))
            right++;
    }
    if (left + right >= 5)
        return true;
    return false;
}

bool Gomoku::BenjiAI::isClosePositionVer(Vector pos, MoveType player) {
    int x = pos.getX();
    int y = pos.getY();
    int top = 0;
    int bottom = 0;

    for (int i = 0; i < 5; i++) {
        if (whoPlayedAt(Vector(x, y - i)) == player || (whoPlayedAt(Vector(x, y - i)) == MoveType::NONE && y - i > 0))
            top++;
        if (whoPlayedAt(Vector(x, y + i)) == player || (whoPlayedAt(Vector(x, y + i)) == MoveType::NONE && y + i < getBoardHeight()))
            bottom++;
    }
    if (top + bottom >= 5)
        return true;
    return false;
}

bool Gomoku::BenjiAI::isClosePositionDiag1(Vector pos, MoveType player) {
    int x = pos.getX();
    int y = pos.getY();
    int top = 0;
    int bottom = 0;

    for (int i = 0; i < 5; i++) {
        if (whoPlayedAt(Vector(x - i, y - i)) == player || (whoPlayedAt(Vector(x - i, y - i)) == MoveType::NONE && x - i > 0 && y - i > 0))
            top++;
        if (whoPlayedAt(Vector(x + i, y + i)) == player || (whoPlayedAt(Vector(x + i, y + i)) == MoveType::NONE && x + i < getBoardWidth() && y + i < getBoardHeight()))
            bottom++;
    }
    if (top + bottom >= 5)
        return true;
    return false;
}

bool Gomoku::BenjiAI::isClosePositionDiag2(Vector pos, MoveType player) {
    int x = pos.getX();
    int y = pos.getY();
    int top = 0;
    int bottom = 0;

    for (int i = 0; i < 5; i++) {
        if (whoPlayedAt(Vector(x - i, y + i)) == player || (whoPlayedAt(Vector(x - i, y + i)) == MoveType::NONE && x - i > 0 && y + i < getBoardHeight()))
            top++;
        if (whoPlayedAt(Vector(x + i, y - i)) == player || (whoPlayedAt(Vector(x + i, y - i)) == MoveType::NONE && x + i < getBoardWidth() && y - i > 0))
            bottom++;
    }
    if (top + bottom >= 5)
        return true;
    return false;
}
