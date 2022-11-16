/*
** EPITECH PROJECT, 2022
** Gomoku
** File description:
** Vector
*/

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <string>

namespace Gomoku {

    class Vector {
        public:
            Vector() {}
            Vector(int x, int y) {
                _x = x;
                _y = y;
            }
            ~Vector() {}

            void setX(int x) {
                _x = x;
            }
            void setY(int y) {
                _y = y;
            }

            int getX() const {
                return _x;
            }
            int getY() const {
                return _y;
            }

            std::string to_string() const {
                return "{" + std::to_string(_x) + "; " + std::to_string(_y) + "}";
            }

        protected:
        private:
            int _x;
            int _y;
    };

}

#endif /* !VECTOR_HPP_ */
