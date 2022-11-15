/*
** EPITECH PROJECT, 2022
** Gomoku
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <memory>
#include <iostream>
#include "Gomoku.hpp"

namespace Gomoku {
    class Game {
        public:
            Game() {
                _com = std::make_shared<Communication>();
            }
            ~Game() {}

            void start();

        protected:
        private:
            std::shared_ptr<Communication> _com;
    };
}

#endif /* !GAME_HPP_ */
