/*
** EPITECH PROJECT, 2022
** Gomoku AI 2
** File description:
** BestMinMax
*/

#include "BestMinMax.hpp"
#include <cmath>

Gomoku::BestMinMax::BestMinMax() : BasicAI("BestMinMax") {}

Gomoku::BestMinMax::~BestMinMax() {}

Gomoku::Vector Gomoku::BestMinMax::chooseBestMove() {
    std::vector<MinMaxIntel> minMax = getMinMax(getHistory());
    int max = 0;
    int index = 0;
    if (minMax.size() == 0)
        return getRandomMove();
    for (std::size_t i = 0; i < minMax.size(); i++) {
        if (minMax[i].state == WIN) {
            max = minMax[i].score;
            index = i;
        } else if (minMax[i].state == LOSE && minMax[index].state != WIN) {
            max = minMax[i].score;
            index = i;
        } else if (minMax[i].state == SAME && minMax[index].state != WIN && minMax[index].state != LOSE) {
            max = minMax[i].score;
            index = i;
        } else if (minMax[i].state == NONE && minMax[index].state != WIN && minMax[index].state != LOSE && minMax[index].state != SAME && minMax[i].score > max) {
            max = minMax[i].score;
            index = i;
        }
    }
    return minMax[index].pos;
}

std::vector<Gomoku::BestMinMax::MinMaxIntel> Gomoku::BestMinMax::getMinMax(std::vector<PosHistory> history, int depth) {
    std::vector<Gomoku::BestMinMax::MinMaxIntel> result;

    if (depth > 1)
        return result;

    Communication::sendDebug("Depth: " + std::to_string(depth));
    auto aiMoves = getBestMoves(MoveType::IA_MOVE, history);
    auto opponentMoves = getBestMoves(MoveType::GAME_MOVE, history);

    PosHistory lastPosCalc;
    int score = 0;
    for (std::size_t i = 0; i < aiMoves.size(); i++) {
        if (lastPosCalc.pos != aiMoves[i].pos) {
            MinMaxIntel intel;
            intel.player = MoveType::IA_MOVE;
            intel.pos = aiMoves[i].pos;
            intel.score = score;
            result.push_back(intel);

            lastPosCalc.player = MoveType::IA_MOVE;
            lastPosCalc.pos = aiMoves[i].pos;
            score = aiMoves[i].size;
        } else {
            score += aiMoves[i].size;
        }
    }

    lastPosCalc.pos = Vector(-1, -1);
    score = 0;
    for (std::size_t i = 0; i < opponentMoves.size(); i++) {
        if (lastPosCalc.pos != opponentMoves[i].pos) {
            MinMaxIntel intel;
            intel.player = MoveType::GAME_MOVE;
            intel.pos = opponentMoves[i].pos;
            intel.score = score;
            result.push_back(intel);

            lastPosCalc.player = MoveType::GAME_MOVE;
            lastPosCalc.pos = opponentMoves[i].pos;
            score = opponentMoves[i].size * -1;
        } else {
            score += (opponentMoves[i].size * -1);
        }
    }

    for (std::size_t i = 0; i < result.size(); i++) {
        if (isWinningMove(result[i].player, result[i].pos, history)) {
            if (result[i].player == MoveType::IA_MOVE)
                result[i].state = WIN;
            else
                result[i].state = LOSE;
            return result;
        } else {
            result[i].state = NONE;
        }
    }

    for (std::size_t i = 0; i < result.size(); i++) {
        std::vector<PosHistory> nHistory = history;
        PosHistory nHist;
        nHist.player = result[i].player;
        nHist.pos = result[i].pos;
        nHistory.push_back(nHist);

        std::vector<MinMaxIntel> nResult = getMinMax(nHistory, depth + 1);
        for (std::size_t j = 0; j < nResult.size(); j++) {
            result[i].score += nResult[j].score;
            if (nResult[j].score == 1000 || nResult[j].score == -1000) {
                return result;
            }
            if (isWinningMove(nResult[j].player, nResult[j].pos, nHistory)) {
                if (nResult[j].player == MoveType::IA_MOVE)
                    result[i].state = WIN;
                else
                    result[i].state = LOSE;
                return result;
            }
        }
    }
    return result;
}

bool Gomoku::BestMinMax::isWinningMove(MoveType player, Vector pos, std::vector<PosHistory> history) {
    PosHistory nHist;
    nHist.player = player;
    nHist.pos = pos;
    history.push_back(nHist);

    for (std::size_t i = 0; i < history.size(); i++) {
        bool hor = true;
        bool ver = true;
        bool dia1 = true;
        bool dia2 = true;
        for (int j = 0; j < 5; j++) {
            //check horizontal
            if (whoPlayedAt(Vector(history[i].pos.getX() + j, history[i].pos.getY()), history) != player)
                hor = false;
            //check vertical
            if (whoPlayedAt(Vector(history[i].pos.getX(), history[i].pos.getY() + j), history) != player)
                ver = false;
            //check diag1
            if (whoPlayedAt(Vector(history[i].pos.getX() + j, history[i].pos.getY() + j), history) != player)
                dia1 = false;
            //check diag2
            if (whoPlayedAt(Vector(history[i].pos.getX() + j, history[i].pos.getY() - j), history) != player)
                dia2 = false;
        }
        if (hor || ver || dia1 || dia2)
            return true;
    }
    return false;
}
