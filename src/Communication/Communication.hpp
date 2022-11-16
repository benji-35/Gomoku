/*
** EPITECH PROJECT, 2022
** Gomoku
** File description:
** Communication
*/

#ifndef COMMUNICATION_HPP_
#define COMMUNICATION_HPP_

#include <iostream>

namespace Gomoku {

    class Communication {
        public:

            static bool sendUnknown(std::string message) {
                return send("UNKNOWN", message);
            }

            static bool sendError(std::string message) {
                return send("ERROR", message);
            }

            static bool sendMessage(std::string message) {
                return send("MESSAGE", message);
            }

            static bool sendDebug(std::string message) {
                return send("DEBUG", message);
            }

            static bool sendSuggest(int x, int y) {
                return send("DEBUG", "" + std::to_string(x) + " " + std::to_string(y));
            }

            static bool sendMove(int x, int y) {
                return send("CONNECT_MESSAGES", "" + std::to_string(x) + " " + std::to_string(y));
            }

            static bool sendOK() {
                return send("CONNECT_MESSAGES", "OK");
            }

            static bool sendAbout(std::string about) {
                return send("CONNECT_MESSAGES", about);
            }

        protected:
        private:
            static bool send(std::string key, std::string content) {
                if (content == "")
                    return false;
                if (key == "UNKNOWN") {
                    std::cout << key << " " << content << std::endl;
                    return true;
                } else if (key == "ERROR") {
                    std::cout << key << " " << content << std::endl;
                    return true;
                } else if (key == "MESSAGE") {
                    std::cout << key << " " << content << std::endl;
                    return true;
                } else if (key == "DEBUG") {
                    std::cout << key << " " << content << std::endl;
                    return true;
                } else if (key == "SUGGEST") {
                    std::cout << key << " " << content << std::endl;
                    return true;
                } else if (key == "CONNECT_MESSAGES") {
                    std::cout << content << std::endl;
                    return true;
                } else {
                    return false;
                }
            }
    };

}

#endif /* !COMMUNICATION_HPP_ */
