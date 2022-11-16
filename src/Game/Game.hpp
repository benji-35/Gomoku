/*
** EPITECH PROJECT, 2022
** Gomoku
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <memory>
#include <vector>

#include "AbstractIA.hpp"

namespace Gomoku {
    class Game {
        public:
            Game() {
                _com = std::make_shared<Communication>();
            }
            ~Game() {}

            void start();

            void setBoardSize(std::size_t boardSize) {
                _boardSize=  boardSize;
            }

            void setIA(std::shared_ptr<AbstractIA> ia) {
                _ia = ia;
            }

            std::shared_ptr<AbstractIA> getIA() const {
                return _ia;
            }

        protected:
        private:
            std::shared_ptr<AbstractIA> _ia;
            std::vector<std::string> _board;
            std::size_t _boardSize;
            bool _running = false;
    };
}

#endif /* !GAME_HPP_ */
