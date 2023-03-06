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
            Vector() : _x(0), _y(0) {}
            Vector(int x, int y) {
                _x = x;
                _y = y;
            }
            Vector(Vector const& vec) {
                *this = vec;
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

            Vector &operator=(Vector const& vec) {
                _x = vec.getX();
                _y = vec.getY();
                return *this;
            }

            bool operator==(Vector const& vec) const {
                return _x == vec.getX() && _y == vec.getY();
            }

            bool operator!=(Vector const& vec) const {
                return !(vec == *this);
            }

            bool operator<(Vector const& vec) const {
                return _x < vec.getX() && _y < vec.getY();
            }

            bool operator>(Vector const& vec) const {
                return _x > vec.getX() && _y > vec.getY();
            }

            bool operator<=(Vector const& vec) const {
                return _x <= vec.getX() && _y <= vec.getY();
            }

            bool operator>=(Vector const& vec) const {
                return _x >= vec.getX() && _y >= vec.getY();
            }

            Vector operator+(Vector const& vec) const {
                return Vector(_x + vec.getX(), _y + vec.getY());
            }

            Vector operator-(Vector const& vec) const {
                return Vector(_x - vec.getX(), _y - vec.getY());
            }

            Vector &operator+=(Vector const& vec) {
                _x += vec.getX();
                _y += vec.getY();
                return *this;
            }

            Vector &operator-=(Vector const& vec) {
                _x -= vec.getX();
                _y -= vec.getY();
                return *this;
            }

        protected:
        private:
            int _x;
            int _y;
    };

}

#endif /* !VECTOR_HPP_ */
