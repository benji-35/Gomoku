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
                Communication::sendDebug("Win AI calc");
                return __getWinPos(_iaChar);
            }

            /**
             * @brief get win position available for Player
            */
            Vector getWinPosPlayer() {
                Communication::sendDebug("Win opponent calc");
                return __getWinPos(_gameChar, true);
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
    
            Vector __getWinPos(char ref, bool preshot = false) {
                if (preshot) {
                    Communication::sendDebug("Calc preshots");
                    /*
                        checkSpecificsPattern does not working

                    Vector res = __checkSpecificsPattern(ref);
                    if (res.getX() != -1 && res.getY() != -1)
                        return res;*/
                }
                Communication::sendDebug("Calc hor");
                Vector result(__checkWinHorizontal(ref, preshot));
                if (result.getX() != -1 && result.getY() != -1)
                    return result;
                Communication::sendDebug("Calc vert");
                result = __checkWinVertical(ref, preshot);
                if (result.getX() != -1 && result.getY() != -1)
                    return result;
                Communication::sendDebug("No win");
                return result;
            }
    
            Vector __checkWinHorizontal(char ref, bool preshot = true) {
                for (std::size_t y = 0; y < _board.size(); y++) {
                    //ref place
                    int refF = 0;
                    //empty place
                    int refE = 0;
                    //first char found
                    int _found = -1;
                    for (std::size_t x = 0; x < _board[y].size(); x++) {
                        if (_board[y][x] == ref) {
                            refF++;
                            if (_found == -1) {
                                _found = static_cast<int>(x);
                            }
                        } else if (_board[y][x] == _emptyChar) {
                            refE++;
                            if (_found == -1) {
                                _found = static_cast<int>(x);
                            }
                        } else {
                            _found = -1;
                            refE = 0;
                            refF = 0;
                        }
                        //check refresh selection
                        if (refE > 2) {
                            refF = 0;
                            refE = 0;
                            _found = -1;
                        } else if (refE == 2 && refF == 0) {
                            refF = 0;
                            refE = 1;
                            _found++;
                        }
                        //check winning positions
                        if ((refF == 4 && refE == 1) || (refF == 3 && refE == 2 && preshot)) {
                            break;
                        }
                    }
                    if ((refF == 4 && refE == 1) || (refF == 3 && refE == 2 && preshot)) {
                        //check position to give
                        int posAvailable = -1;
                        int firstRef = -1;
                        for (std::size_t x = 0; x < _board[y].size(); x++) {
                            if (_board[y][x] == ref && firstRef == -1) {
                                firstRef = x;
                                if (x > 0 && _board[y][firstRef - 1] == _emptyChar) {
                                    posAvailable = firstRef - 1;
                                    break;
                                }
                                break;
                            }
                        }
                        if (posAvailable == -1) {
                            return Vector(firstRef + refF, y);
                        }
                        return Vector(posAvailable, y);
                    }
                }
                return Vector(-1, -1);
            }

            Vector __checkWinVertical(char ref, bool preshot = true) {
                for (std::size_t x = 0; x < _boardSizeX; x++) {
                    //var for first interesting char
                    int firstPos = -1;
                    //var for nb Empty chars
                    int nbE = 0;
                    //var for nb Ref chars
                    int nbR = 0;
                    //read board
                    for (std::size_t y = 0; y < _boardSizeY; y++) {
                        if (_board[y][x] == _emptyChar) {
                            nbE++;
                            if (firstPos == -1)
                                firstPos = y;
                            if (nbE == 2 && nbR == 0) {
                                nbE--;
                                firstPos++;
                            }
                        } else if (_board[y][x] == ref) {
                            nbR++;
                            if (firstPos == -1)
                                firstPos = y;
                        } else {
                            firstPos = -1;
                            nbR = 0;
                            nbE = 0;
                        }
                        if ((nbE == 1 && nbR == 4) || (nbE == 2 && nbR == 3 && preshot)) {
                            break;
                        }
                    }
                
                    if ((nbE == 1 && nbR == 4) || (nbE == 2 && nbR == 3 && preshot)) {
                        for (std::size_t y = static_cast<std::size_t>(firstPos); y < _boardSizeY; y++) {
                            if (_board[y][x] == _emptyChar)
                                return Vector(x, y);
                        }
                    }
                }
                return Vector(-1, -1);
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

            Vector __checkSpecificsPattern(char ref) {
                //this function is call only with preshot active
                {
                    /**
                     * Square Empty Middle :
                     * .XXX.
                     * .X.X.
                     * .XXX.
                     * here we want the middle point
                    */
                    std::vector<std::string> _squareEmptyMiddle;

                    std::string l1;
                    std::string l2;
                    std::string l3;

                    l1 = ref + ref + ref;
                    l2 = ref + _emptyChar + ref;
                    l3 = l1;

                    _squareEmptyMiddle.push_back(l1);
                    _squareEmptyMiddle.push_back(l2);
                    _squareEmptyMiddle.push_back(l3);

                    Vector result = findPattern(_squareEmptyMiddle);
                    if (result.getX() != 1 && result.getY() != 1) {
                        // here result give top left corner pattern pos
                        // we want middle so let's do some calculations
                        result.setX(result.getX() + 1);
                        result.setY(result.getY() + 1);
                    }
                    return result;
                }
                return Vector(-1, -1);
            }

            Vector findPattern(std::vector<std::string> pattern) {
                Vector result(-1, -1);

                int yVerrified = 0;
                int yRes = -1;
                int xRes = -1;

                for (std::size_t y = 0; y < _boardSizeY; y++) {
                    std::size_t xF = findLinePattern(_board[y], pattern[yVerrified]);
                    if (xF != _board[y].size()) {
                        yVerrified++;
                        yRes = y;
                        xRes = static_cast<int>(xF);
                    } else {
                        yRes = -1;
                        xRes = -1;
                        yVerrified = 0;
                    }
                    if (static_cast<std::size_t>(yVerrified) == pattern.size()) {
                        break;
                    }
                }

                if (static_cast<std::size_t>(yVerrified) != pattern.size())
                    return result;
                if (yRes != -1 && xRes != -1) {
                    result.setX(xRes);
                    result.setY(yRes);
                    Communication::sendDebug("Find pattern at: " + result.to_string());
                }
                return result;
            }

            std::size_t findLinePattern(std::string line, std::string pattern) {
                auto res = line.find(pattern);

                if (res == std::string::npos)
                    return line.size();
                return res;
            }
    };

}

#endif /* !IA_HPP_ */
