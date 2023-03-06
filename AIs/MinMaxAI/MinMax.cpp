/*
** EPITECH PROJECT, 2022
** Gomoku
** File description:
** MinMax
*/

#include "MinMax.hpp"
#include <limits>

Gomoku::MinMax::MinMax() {
}

Gomoku::MinMax::~MinMax() {
}

Gomoku::Vector Gomoku::MinMax::chooseBestMove() {
    int bestScore = std::numeric_limits<int>::min();
    Gomoku::Vector bestMove;
    auto board = getBoard();

    for (int i = 0; i < getBoardHeight(); i++) {
        for (int j = 0; j < getBoardWidth(); j++) {
            if (board[i][j] == getEmptyChar()) {
                board[i][j] = getIAChar();
                int score = minimax(board, 0, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
                board[i][j] = getEmptyChar();
                if (score > bestScore) {
                    bestScore = score;
                    bestMove.setX(i);
                    bestMove.setY(j);
                }
            }
        }
    }
    return bestMove;
}

int Gomoku::MinMax::minimax(std::vector<std::string> board, int depth, bool isMaximizing, int alpha, int beta) {

    int result = checkWin(board);

    if (result != 0) {
        return result;
    }

    if (isMaximizing) {
        int bestScore = std::numeric_limits<int>::min();
        for (int i = 0; i < getBoardHeight(); i++) {
            for (int j = 0; j < getBoardWidth(); j++) {
                if (board[i][j] == getEmptyChar()) {
                    board[i][j] = getIAChar();
                    int score = minimax(board, depth + 1, false, alpha, beta);
                    board[i][j] = getEmptyChar();
                    bestScore = std::max(score, bestScore);
                    alpha = std::max(alpha, bestScore);
                    if (beta <= alpha)
                        break;
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = std::numeric_limits<int>::max();
        for (int i = 0; i < getBoardHeight(); i++) {
            for (int j = 0; j < getBoardWidth(); j++) {
                if (board[i][j] == getEmptyChar()) {
                    board[i][j] = getGameChar();
                    int score = minimax(board, depth + 1, true, alpha, beta);
                    board[i][j] = getEmptyChar();
                    bestScore = std::min(score, bestScore);
                    beta = std::min(beta, bestScore);
                    if (beta <= alpha)
                        break;
                }
            }
        }
        return bestScore;
    }
}

int Gomoku::MinMax::checkWin(std::vector<std::string> board) {
    return 0;
}