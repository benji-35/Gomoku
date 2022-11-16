/*
** EPITECH PROJECT, 2022
** Gomoku
** File description:
** IA
*/

#ifndef IA_HPP_
#define IA_HPP_

#include <vector>
#include <string>

#include "MoveType.hpp"
#include "Vector.hpp"
#include "Communication.hpp"

namespace Gomoku {
    class Communication;
}

namespace Gomoku {

    class AbstractIA {
        public:
            AbstractIA(bool debug = false) : _debugMode(debug) {}
            AbstractIA(std::string const& iaName, std::string const& iaVersion, std::string const& iaAuthor, std::string const& iaCountry, bool debug = false) : 
                _iaName(iaName), _iaVersion(iaVersion), _iaAuthor(iaAuthor), _iaCountry(iaCountry), _debugMode(debug) {}
            ~AbstractIA() = default;

            virtual Vector chooseBestMove() = 0;

            void setBoardSize(std::size_t size) {
                _boardSizeX = size;
                _boardSizeY = size;
            }

            void setBoardSize(std::size_t sizeX, std::size_t sizeY) {
                _boardSizeX = sizeX;
                _boardSizeY = sizeY;
            }

            bool setMove(Vector pos, MoveType moveType = MoveType::IA_MOVE) {
                if (!canMoveAtPos(pos.getX(), pos.getY()))
                    return false;
                if (moveType == MoveType::GAME_MOVE) {
                    _board[pos.getY()][pos.getX()] = _gameChar;
                } else {
                    _board[pos.getY()][pos.getX()] = _iaChar;
                    Communication::sendMove(pos.getX(), pos.getY());
                }
                _history.push_back(pos);
                if (_debugMode) {
                    __debugMap();
                }
                return true;
            }

            bool backMove() {
                if (_history.size() == 0)
                    return false;
                Vector last = _history[_history.size() - 1];
                _board[last.getY()][last.getX()] = _emptyChar;
                _history.pop_back();
                return true;
            }

            bool restartIA() {
                if (_boardSizeX == 0 || _boardSizeY == 0)
                    return false;
                if (_debugMode)
                    Communication::sendDebug("Clearing ia");
                _history.clear();
                if (_debugMode)
                    Communication::sendDebug("Clearing create map");
                __initBoard();
                if (_debugMode)
                    __debugMap();
                return true;
            }

            void startIA(std::size_t size) {
                setBoardSize(size);
                restartIA();
            }

            std::vector<std::string> getBoard() const {
                return _board;
            }

            std::vector<Vector> getHistory() const {
                return _history;
            }

            std::size_t getBoardWidth() const {
                return _boardSizeX;
            }

            std::size_t getBoardHeight() const {
                return _boardSizeY;
            }

            std::string getAbout() const {
                return "name=" + _iaName + ", version=" + _iaVersion + ", author=" + _iaAuthor + ", country=" + _iaCountry;
            }

            void stopAll() {
                _board.clear();
                _history.clear();
            }

        protected:
            char getIAChar() const {
                return _iaChar;
            }

            char getGameChar() const {
                return _gameChar;
            }

            bool canMoveAtPos(int x, int y) {
                if (y >= static_cast<int>(_boardSizeY))
                    return false;
                if (x >= static_cast<int>(_boardSizeX))
                    return false;
                return _board[y][x] == _emptyChar;
            }

            /**
             * @brief get win position available for IA
            */
            Vector getWinPosAI() {
                return __getWinPos(_iaChar);
            }

            /**
             * @brief get win position available for Player
            */
            Vector getWinPosPlayer() {
                return __getWinPos(_gameChar);
            }

        private:
            std::vector<std::string> _board;
            std::vector<Vector> _history;
            std::size_t _boardSizeX = 0;
            std::size_t _boardSizeY = 0;
            char _iaChar = 'x';
            char _gameChar = 'o';
            char _emptyChar = '.';

            std::string _iaName = "IA Gomoku by kap35";
            std::string _iaVersion = "1.0";
            std::string _iaAuthor = "kap35";
            std::string _iaCountry = "France";

            bool _debugMode = false;

            //create empty board
            void __initBoard() {
                _board.clear();
                for (std::size_t y = 0; y < _boardSizeY; y++) {
                    std::string line = "";
                    for (std::size_t x = 0; x < _boardSizeX; x++) {
                        line += _emptyChar;
                    }
                    _board.push_back(line);
                }
            }
    
            Vector __getWinPos(char ref) {
                Vector result(-1, -1);

                return result;
            }
    
            void __debugMap() {
                std::string line = "";
                for (std::size_t i = 0; i < _boardSizeX + 2; i++) {
                    if (i == 0 || i == _boardSizeX + 1) {
                        line += "+";
                    } else {
                        line += "-";
                    }
                }
                Communication::sendDebug(line);
                for (std::size_t y = 0; y < _boardSizeY; y++) {
                    Communication::sendDebug("|" + _board[y] + "|");
                }
                Communication::sendDebug(line);
            }
    };

}

#endif /* !IA_HPP_ */
