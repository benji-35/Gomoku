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

#include "Utils/MoveType.hpp"
#include "Utils/Vector.hpp"
#include "Communication/Communication.hpp"

namespace Gomoku {
    class Communication;
}

namespace Gomoku {

    class AbstractIA {
        public:

            struct PosHistory {
                Vector pos = Vector(-1, -1);
                MoveType player = MoveType::NONE;
            };

            AbstractIA(bool debug = false) : _debugMode(debug) {}
            AbstractIA(std::string const& iaName, std::string const& iaVersion, std::string const& iaAuthor, std::string const& iaCountry, bool debug = false) : 
                _iaName(iaName), _iaVersion(iaVersion), _iaAuthor(iaAuthor), _iaCountry(iaCountry), _debugMode(debug) {}
            ~AbstractIA() = default;

            virtual Vector chooseBestMove() = 0;

            void setBoardSize(int size) {
                _boardSizeX = size;
                _boardSizeY = size;
            }

            void setBoardSize(int sizeX, int sizeY) {
                _boardSizeX = sizeX;
                _boardSizeY = sizeY;
            }

            bool setMove(Vector pos, MoveType moveType = MoveType::IA_MOVE, bool board = false) {
                if (!canMoveAtPos(pos.getX(), pos.getY()))
                    return false;
                if (!board && moveType == MoveType::IA_MOVE)
                    Communication::sendMove(pos.getX(), pos.getY());
                PosHistory hist;
                hist.pos = pos;
                hist.player = moveType;
                _history.push_back(hist);
                if (_debugMode) {
                    __debugMap();
                }
                return true;
            }

            bool backMove() {
                if (_history.size() == 0)
                    return false;
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

            void startIA(int size) {
                setBoardSize(size);
                restartIA();
            }

            std::string getAbout() const {
                return "name=" + _iaName + ", version=" + _iaVersion + ", author=" + _iaAuthor + ", country=" + _iaCountry;
            }

            void stopAll() {
                _history.clear();
            }

            int getBoardWidth() const {
                return _boardSizeX;
            }

            int getBoardHeight() const {
                return _boardSizeY;
            }

            std::vector<PosHistory> getHistory() const {
                return _history;
            }

        protected:
            char getIAChar() const {
                return _iaChar;
            }

            char getGameChar() const {
                return _gameChar;
            }

            char getEmptyChar() const {
                return _emptyChar;
            }

            bool canMoveAtPos(int x, int y) {
                if (y >= static_cast<int>(_boardSizeY) || y < 0)
                    return false;
                if (x >= static_cast<int>(_boardSizeX) || x < 0)
                    return false;
                return !(posIsPlayed(x, y));
            }

            bool canMoveAtPos(Vector pos) {
                return canMoveAtPos(pos.getX(), pos.getY());
            }

            bool posIsPlayed(Vector pos) {
                return posIsPlayed(pos.getX(), pos.getY());
            }

            bool posIsPlayed(int x, int y) {
                if (y >= static_cast<int>(_boardSizeY) || y < 0)
                    return false;
                if (x >= static_cast<int>(_boardSizeX) || x < 0)
                    return false;
                for (std::size_t i = 0; i < _history.size(); i++) {
                    if (_history[i].pos.getX() == x && _history[i].pos.getY() == y)
                        return true;
                }
                return false;
            }

            MoveType whoPlayedAt(int x, int y) {
                if (!posIsPlayed(x, y))
                    return MoveType::NONE;
                for (std::size_t i = 0; i < _history.size(); i++) {
                    if (_history[i].pos.getX() == x && _history[i].pos.getY() == y)
                        return _history[i].player;
                }
                return MoveType::NONE;
            }

            MoveType whoPlayedAt(Vector pos) {
                return whoPlayedAt(pos.getX(), pos.getY());
            }

            MoveType whoPlayedAt(int x, int y, std::vector<PosHistory> hist) {
                if (hist.empty())
                    return whoPlayedAt(x, y);
                for (std::size_t i = 0; i < hist.size(); i++) {
                    if (hist[i].pos.getX() == x && hist[i].pos.getY() == y)
                        return hist[i].player;
                }
                return MoveType::NONE;
            }

            MoveType whoPlayedAt(Vector pos, std::vector<PosHistory> hist) {
                return whoPlayedAt(pos.getX(), pos.getY(), hist);
            }

            std::vector<std::string> getBoard() const {
                return getBoard(_history);
            }

            std::vector<std::string> getBoard(std::vector<PosHistory> poses) const {
                std::vector<std::string> nBoard;
                for (int i = 0; i < _boardSizeY; i++) {
                    std::string line = "";
                    for (int j = 0; j < _boardSizeX; j++) {
                        line += _emptyChar;
                    }
                    nBoard.push_back(line);
                }
                for (std::size_t i = 0; i < poses.size(); i++) {
                    if (poses[i].player == MoveType::GAME_MOVE && poses[i].pos.getX() < _boardSizeX && poses[i].pos.getY() < _boardSizeY && poses[i].pos.getX() >= 0 && poses[i].pos.getY() >= 0) {
                        nBoard[poses[i].pos.getY()][poses[i].pos.getX()] = _gameChar;
                    } else if (poses[i].pos.getX() < _boardSizeX && poses[i].pos.getY() < _boardSizeY && poses[i].pos.getX() >= 0 && poses[i].pos.getY() >= 0) {
                        nBoard[poses[i].pos.getY()][poses[i].pos.getX()] = _iaChar;
                    }
                }
                return nBoard;
            }

        private:
            std::vector<PosHistory> _history;
            int _boardSizeX = 0;
            int _boardSizeY = 0;
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
                _history.clear();
            }

            void __debugMap() {
                auto board = getBoard();
                std::string line = "";
                for (int i = 0; i < _boardSizeX + 2; i++) {
                    if (i == 0 || i == _boardSizeX + 1) {
                        line += "+";
                    } else {
                        line += "-";
                    }
                }
                Communication::sendDebug(line);
                for (int y = 0; y < _boardSizeY; y++) {
                    Communication::sendDebug("|" + board[y] + "|");
                }
                Communication::sendDebug(line);
            }

    };
}

#endif /* !IA_HPP_ */
