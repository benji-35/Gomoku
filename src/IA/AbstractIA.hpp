/*
** EPITECH PROJECT, 2022
** Gomoku
** File description:
** IA
*/

#ifndef IA_HPP_
#define IA_HPP_

#include <vector>

#include "MoveType.hpp"
#include "Vector.hpp"

namespace Gomoku {

    class AbstractIA {
        public:
            AbstractIA(Game &game) : _game(game) {}
            ~AbstractIA() = default;

            virtual Vector chooseBestMove() = 0;

            void setBoardSize(std::size_t size) {
                _boardSize = size;
            }

            bool setMove(Vector pos, MoveType moveType = MoveType::IA_MOVE) {
                if (!canMoveAtPos(pos.getX(), pos.getY()))
                    return false;
                if (moveType == MoveType::GAME_MOVE) {
                    _board[pos.getY()][pos.getX()] = _gameChar;
                } else {
                    _board[pos.getY()][pos.getX()] = _iaChar;
                }
                _history.push_back(pos);
                return true;
            }

            bool backMove() {
                if (_history.size() == 0)
                    return false;
                Vector last = _history[_history.size() - 1];
                _board[last.getY()][last.getX()] = _emptyChar;
                _history.pop_back();
            }

            bool restartIA() {
                _history.clear();
                __initBoard();
            }

            void startIA(std:size_t size) {
                setBoardSize(size);
                restartIA();
            }

        protected:
            char getIAChar() const {
                return _iaChar;
            }

            char getGameChar() const {
                return _gameChar;
            }

            bool canMoveAtPos(int x, int y) {
                if (y >= _board.size())
                    return false;
                if (x >= _board[y].size())
                    return false;
                return _board[y][x] == _emptyChar;
            }

        private:
            std::vector<std::string> _board;
            std::vector<Vector> _history;
            std::size_t _boardSize = 0;
            char _iaChar = "x";
            char _gameChar = "o";
            char _emptyChar = ".";

            //create empty board
            void __initBoard() {
                _board.clear();
                for (std::size_t y = 0; y < _boardSize; y++) {
                    std::string line = "";
                    for (std::size_t x = 0; x < _boardSize; x++) {
                        line += _emptyChar;
                    }
                    _board.push_back(line);
                }
            }
    };

}

#endif /* !IA_HPP_ */
