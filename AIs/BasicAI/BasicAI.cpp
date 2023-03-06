/*
** EPITECH PROJECT, 2022
** Gomoku
** File description:
** IaTest
*/

#include "BasicAI.hpp"

Gomoku::BasicAI::BasicAI(std::string name, std::string version, std::string author, std::string country) : AbstractIA(name, version, author, country, true) {}

Gomoku::BasicAI::~BasicAI() {}

Gomoku::Vector Gomoku::BasicAI::chooseBestMove() {
    auto aiMoves = getBestMoves(MoveType::IA_MOVE, true);
    auto opponentsMove = getBestMoves(MoveType::GAME_MOVE, true);
    std::size_t iaBestMove = getBestMove(aiMoves, true);
    std::size_t opponentBestMove = getBestMove(opponentsMove, true);

    Communication::sendDebug("ia move: ");
    debugMoves(aiMoves);
    Communication::sendDebug("opponent move: ");
    debugMoves(opponentsMove);
    Communication::sendDebug("all moves debug");

    if (iaBestMove >= aiMoves.size() && opponentBestMove >= opponentsMove.size())
        return getRandomMove();
    if (iaBestMove >= aiMoves.size()) {
        return opponentsMove[opponentBestMove].pos;
    }
    if (opponentBestMove >= opponentsMove.size()) {
        return aiMoves[iaBestMove].pos;
    }
    if (aiMoves[iaBestMove].size >= opponentsMove[opponentBestMove].size) {
        return aiMoves[iaBestMove].pos;
    } else {
        return opponentsMove[opponentBestMove].pos;
    }
}

Gomoku::Vector Gomoku::BasicAI::getRandomMove() {
    int x = std::rand() % getBoardWidth();
    int y = std::rand() % getBoardHeight();

    while (!canMoveAtPos(x, y)) {
        x = std::rand() % getBoardWidth();
        y = std::rand() % getBoardHeight();
    }
    return Vector(x, y);
}

std::vector<Gomoku::BasicAI::CheckIntel> Gomoku::BasicAI::getBestMoves(MoveType ref, bool preshot) {
    return getBestMoves(ref, getHistory(), preshot);
}

std::vector<Gomoku::BasicAI::CheckIntel> Gomoku::BasicAI::getBestMoves(MoveType ref, std::vector<PosHistory> hist, bool preshot) {
    std::vector<CheckIntel> bestMoves;

    for (int y = 0; y < getBoardHeight(); y++) {
        for (int x = 0; x < getBoardWidth(); x++) {
            if (shouldCalculHere(Vector(x, y), ref, hist)) {
                if (!entoureByOpponent(Vector(x, y), ref, PatternType::HORIZONTAL, hist))
                    checkPosMoves(bestMoves, Vector(x, y), HORIZONTAL, ref, hist);
                if (!entoureByOpponent(Vector(x, y), ref, PatternType::VERTICAL, hist))
                    checkPosMoves(bestMoves, Vector(x, y), VERTICAL, ref, hist);
                if (!entoureByOpponent(Vector(x, y), ref, PatternType::DIAGONAL_BOTTOM_LEFT_TOP_RIGHT, hist))
                    checkPosMoves(bestMoves, Vector(x, y), DIAGONAL_BOTTOM_LEFT_TOP_RIGHT, ref, hist);
                if (!entoureByOpponent(Vector(x, y), ref, PatternType::DIAGONAL_TOP_LEFT_BOTTOM_RIGHT, hist))
                    checkPosMoves(bestMoves, Vector(x, y), DIAGONAL_TOP_LEFT_BOTTOM_RIGHT, ref, hist);
            }
        }
    }
    return bestMoves;
}

void Gomoku::BasicAI::checkPosMoves(std::vector<CheckIntel> &bestMoves, Vector pos, PatternType type, MoveType ref, std::vector<PosHistory> hist) {
    switch (type) {
        case HORIZONTAL:
            __checkHor(bestMoves, pos, ref, hist);
            break;
        case VERTICAL:
            __checkVer(bestMoves, pos, ref, hist);
            break;
        case DIAGONAL_BOTTOM_LEFT_TOP_RIGHT:
            __checkDiagBLTR(bestMoves, pos, ref, hist);
            break;
        case DIAGONAL_TOP_LEFT_BOTTOM_RIGHT:
            __checkDiagTLBR(bestMoves, pos, ref, hist);
            break;
    }
}

void Gomoku::BasicAI::__checkHor(std::vector<CheckIntel> &bestMoves, Vector pos, MoveType ref, std::vector<PosHistory> hist) {
    int size = 0;
    int sizeA = 0;
    int sizeB = 0;
    int sizeAEmpty = 0;
    int sizeBEmpty = 0;
    bool checkLeft = true;
    bool checkRight = true;

    for (int x = 1; x < 5; x++) {
        auto pA = whoPlayedAt(pos.getX() - x, pos.getY(), hist);
        auto pB = whoPlayedAt(pos.getX() + x, pos.getY(), hist);
        if (pos.getX() - x < 0)
            checkLeft = false;
        if (pos.getX() + x >= getBoardWidth())
            checkRight = false;
        if (checkLeft) {
            if (sizeAEmpty == 0 && pA == ref) {
                sizeA++;
            } else if (pA == MoveType::NONE) {
                sizeAEmpty++;
            } else {
                checkLeft = false;
            }
        }
        if (checkRight) {
            if (sizeBEmpty == 0 && pB == ref) {
                sizeA++;
            } else if (pB == MoveType::NONE) {
                sizeBEmpty++;
            } else {
                checkRight = false;
            }
        }
        if (checkLeft == false && checkRight == false)
            break;
    }
    size = sizeA + sizeB;
    // check .XtX.
    bestMoves.push_back(CheckIntel(pos, size));
}

void Gomoku::BasicAI::__checkVer(std::vector<CheckIntel> &bestMoves, Vector pos, MoveType ref, std::vector<PosHistory> hist) {
    int size = 0;
    int sizeA = 0;
    int sizeB = 0;
    int sizeAEmpty = 0;
    int sizeBEmpty = 0;
    bool checkLeft = true;
    bool checkRight = true;

    for (int y = 1; y < 5; y++) {
        auto pA = whoPlayedAt(pos.getX(), pos.getY() - y, hist);
        auto pB = whoPlayedAt(pos.getX(), pos.getY() + y, hist);
        if (pos.getY() - y < 0)
            checkLeft = false;
        if (pos.getY() + y >= getBoardWidth())
            checkRight = false;
        if (checkLeft) {
            if (sizeAEmpty == 0 && pA == ref) {
                sizeA++;
            } else if (pA == MoveType::NONE) {
                sizeAEmpty++;
            } else {
                checkLeft = false;
            }
        }
        if (checkRight) {
            if (sizeBEmpty == 0 && pB == ref) {
                sizeA++;
            } else if (pB == MoveType::NONE) {
                sizeBEmpty++;
            } else {
                checkRight = false;
            }
        }
        if (checkLeft == false && checkRight == false)
            break;
    }
    size = sizeA + sizeB;
    // check .XtX.
    bestMoves.push_back(CheckIntel(pos, size));
}

void Gomoku::BasicAI::__checkDiagBLTR(std::vector<CheckIntel> &bestMoves, Vector pos, MoveType ref, std::vector<PosHistory> hist) {
    int size = 0;
    int sizeA = 0;
    int sizeB = 0;
    int sizeAEmpty = 0;
    int sizeBEmpty = 0;
    bool checkLeft = true;
    bool checkRight = true;

    for (int i = 1; i < 5; i++) {
        auto pA = whoPlayedAt(pos.getX() + i, pos.getY() - i, hist);
        auto pB = whoPlayedAt(pos.getX() - i, pos.getY() + i, hist);
        if (pos.getX() + i >= getBoardWidth() || pos.getY() - i < 0)
            checkLeft = false;
        if (pos.getX() - i < 0 || pos.getY() + i >= getBoardWidth())
            checkRight = false;
        if (checkLeft) {
            if (sizeAEmpty == 0 && pA == ref) {
                sizeA++;
            } else if (pA == MoveType::NONE) {
                sizeAEmpty++;
            } else {
                checkLeft = false;
            }
        }
        if (checkRight) {
            if (sizeBEmpty == 0 && pB == ref) {
                sizeA++;
            } else if (pB == MoveType::NONE) {
                sizeBEmpty++;
            } else {
                checkRight = false;
            }
        }
        if (checkLeft == false && checkRight == false)
            break;
    }
    size = sizeA + sizeB;
    // check .XtX.
    bestMoves.push_back(CheckIntel(pos, size));
}

void Gomoku::BasicAI::__checkDiagTLBR(std::vector<CheckIntel> &bestMoves, Vector pos, MoveType ref, std::vector<PosHistory> hist) {
    int size = 0;
    int sizeA = 0;
    int sizeB = 0;
    int sizeAEmpty = 0;
    int sizeBEmpty = 0;
    bool checkLeft = true;
    bool checkRight = true;

    for (int i = 1; i < 5; i++) {
        auto pA = whoPlayedAt(pos.getX() + i, pos.getY() + i, hist);
        auto pB = whoPlayedAt(pos.getX() - i, pos.getY() - i, hist);
        if (pos.getX() + i >= getBoardWidth() || pos.getY() + i >= getBoardWidth())
            checkLeft = false;
        if (pos.getX() - i < 0 || pos.getY() - i < 0)
            checkRight = false;
        if (checkLeft) {
            if (sizeAEmpty == 0 && pA == ref) {
                sizeA++;
            } else if (pA == MoveType::NONE) {
                sizeAEmpty++;
            } else {
                checkLeft = false;
            }
        }
        if (checkRight) {
            if (sizeBEmpty == 0 && pB == ref) {
                sizeA++;
            } else if (pB == MoveType::NONE) {
                sizeBEmpty++;
            } else {
                checkRight = false;
            }
        }
        if (checkLeft == false && checkRight == false)
            break;
    }
    size = sizeA + sizeB;
    // check .XtX.
    bestMoves.push_back(CheckIntel(pos, size));
}

Gomoku::Vector Gomoku::BasicAI::myAIAlgo() {
    Communication::sendDebug("Random move");
    return getRandomMove();
}

std::size_t Gomoku::BasicAI::getBestMove(std::vector<CheckIntel> moves, bool takePreshots) {
    int max = 1;
    std::size_t id = moves.size();

    for (std::size_t i = 0; i < moves.size(); i++) {
        if (moves[i].size > max) {
            max = moves[i].size;
            id = i;
        }
    }
    return id;
}

bool Gomoku::BasicAI::shouldCalculHere(Vector pos, MoveType ref, std::vector<PosHistory> hist) {
    if (whoPlayedAt(pos, hist) != MoveType::NONE)
        return false;
    if (whoPlayedAt(pos.getX() - 1, pos.getY(), hist) == ref || whoPlayedAt(pos.getX() + 1, pos.getY(), hist) == ref)
        return true;
    if (whoPlayedAt(pos.getX(), pos.getY() - 1, hist) == ref || whoPlayedAt(pos.getX(), pos.getY() + 1, hist) == ref)
        return true;
    if (whoPlayedAt(pos.getX() - 1, pos.getY() - 1, hist) == ref || whoPlayedAt(pos.getX() + 1, pos.getY() + 1, hist) == ref)
        return true;
    if (whoPlayedAt(pos.getX() + 1, pos.getY() - 1, hist) == ref || whoPlayedAt(pos.getX() - 1, pos.getY() + 1, hist) == ref)
        return true;
    return false;
}

void Gomoku::BasicAI::debugMoves(std::vector<CheckIntel> moves) {
    for (auto &move : moves) {
        Communication::sendDebug("Move: " + move.pos.to_string() + ", size: " + std::to_string(move.size));
    }
}

bool Gomoku::BasicAI::entoureByOpponent(Vector pos, MoveType yourType, PatternType pattern, std::vector<PosHistory> hist) {
    MoveType opponent = MoveType::NONE;
    switch (yourType){
        case MoveType::IA_MOVE:
            opponent = MoveType::GAME_MOVE;
            break;
        case MoveType::GAME_MOVE:
            opponent = MoveType::IA_MOVE;
            break;
        default:
            return false;
    }
    Vector theoricLeftPos = Vector(-1, -1);
    Vector theoricRightPos = Vector(-1, -1);

    for (int i = 1; i < 5; i++) {
        if (Vector(-1, -1) != theoricLeftPos && Vector(-1, -1) != theoricRightPos)
            break;
        switch (pattern) {
            case PatternType::HORIZONTAL:
                if (whoPlayedAt(pos.getX() - i, pos.getY(), hist) == opponent && Vector(-1, -1) == theoricLeftPos) {
                    theoricLeftPos = Vector(pos.getX() - i, pos.getY());
                }
                if (whoPlayedAt(pos.getX() + i, pos.getY(), hist) == opponent && Vector(-1, -1) == theoricLeftPos) {
                    theoricRightPos = Vector(pos.getX() + i, pos.getY());
                }
                break;
            case PatternType::VERTICAL:
                if (whoPlayedAt(pos.getX(), pos.getY() - i, hist) == opponent && Vector(-1, -1) == theoricLeftPos) {
                    theoricLeftPos = Vector(pos.getX(), pos.getY() - i);
                }
                if (whoPlayedAt(pos.getX(), pos.getY() + i, hist) == opponent && Vector(-1, -1) == theoricLeftPos) {
                    theoricRightPos = Vector(pos.getX(), pos.getY() + i);
                }
                break;
            case PatternType::DIAGONAL_TOP_LEFT_BOTTOM_RIGHT:
                if (whoPlayedAt(pos.getX() - i, pos.getY() - i, hist) == opponent && Vector(-1, -1) == theoricLeftPos) {
                    theoricLeftPos = Vector(pos.getX() - i, pos.getY() - i);
                }
                if (whoPlayedAt(pos.getX() + i, pos.getY() + i, hist) == opponent && Vector(-1, -1) == theoricLeftPos) {
                    theoricRightPos = Vector(pos.getX() + i, pos.getY() + i);
                }
                break;
            case PatternType::DIAGONAL_BOTTOM_LEFT_TOP_RIGHT:
                if (whoPlayedAt(pos.getX() + i, pos.getY() - i, hist) == opponent && Vector(-1, -1) == theoricLeftPos) {
                    theoricLeftPos = Vector(pos.getX() + i, pos.getY() - i);
                }
                if (whoPlayedAt(pos.getX() - i, pos.getY() + i, hist) == opponent && Vector(-1, -1) == theoricLeftPos) {
                    theoricRightPos = Vector(pos.getX() - i, pos.getY() + i);
                }
                break;
        }
    }

    if (Vector(-1, -1) == theoricLeftPos || Vector(-1, -1) == theoricRightPos)
        return false;
    switch (pattern) {
        case PatternType::HORIZONTAL:
            if (theoricRightPos.getX() - theoricLeftPos.getX() <= 4)
                return true;
            break;
        case PatternType::VERTICAL:
            if (theoricRightPos.getY() - theoricLeftPos.getY() <= 4)
                return true;
            break;
        case PatternType::DIAGONAL_TOP_LEFT_BOTTOM_RIGHT:
            if (theoricRightPos.getX() - theoricLeftPos.getX() <= 4)
                return true;
            break;
        case PatternType::DIAGONAL_BOTTOM_LEFT_TOP_RIGHT:
            if (theoricRightPos.getX() - theoricLeftPos.getX() <= 4)
                return true;
            break;
    }
    return false;
}
