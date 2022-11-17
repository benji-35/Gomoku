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
#include <map>
#include <functional>

#include "IA/AbstractIA.hpp"

namespace Gomoku {
    class Game {
        public:
            Game() {}
            ~Game() {}

            void start();

            void setIA(std::shared_ptr<AbstractIA> ia) {
                _ia = ia;
            }

            std::shared_ptr<AbstractIA> getIA() const {
                return _ia;
            }

        protected:
        private:
            std::shared_ptr<AbstractIA> _ia;
            bool _running = false;

            void readCommand();
            std::map<std::string, std::function<void (std::vector<std::string>)>> _commands;

            void __initCommands();

            bool __canPlay();

    };
}

#endif /* !GAME_HPP_ */
