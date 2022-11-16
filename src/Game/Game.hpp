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

#include "AbstractIA.hpp"

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

            std::vector<std::string> splitString(std::string str, std::string separator) {
                std::vector<std::string> result;
                std::size_t lastPos = 0;
                std::size_t pos = 0;
                std::string wordGot = "";

                while((pos = str.find(separator, pos)) != std::string::npos) {
                    wordGot = str.substr(lastPos, pos - lastPos);
                    result.push_back(wordGot);
                    lastPos = pos;
                    pos++;
                }
                result.push_back(str.substr(lastPos, pos - lastPos)); // Last word

                return result;
            }
    };
}

#endif /* !GAME_HPP_ */
