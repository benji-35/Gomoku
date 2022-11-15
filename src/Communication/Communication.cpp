/*
** EPITECH PROJECT, 2022
** Gomoku
** File description:
** Communication
*/

#include "Communication.hpp"

#include <iostream>
#include <string>

Gomoku::Communication::Communication()
{
}

Gomoku::Communication::~Communication()
{
}

void Gomoku::Communication::listen() {
    std::string line;
    while (std::getline (std::cin, line)) {
        std::cout << line << std::endl;
    }
}
