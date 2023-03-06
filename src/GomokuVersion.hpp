/*
** EPITECH PROJECT, 2022
** Gomoku
** File description:
** GomokuVersion
*/

#ifndef GOMOKUVERSION_HPP_
#define GOMOKUVERSION_HPP_

#define GOMOKU_VERSION_AI_MAJOR 1
#define GOMOKU_VERSION_AI_MINOR 001

#define GOMOKU_VERSION_AI "1.001"

#define IS_GOMOKU_VERSION_AI(x, y) (GOMOKU_VERSION_AI_MAJOR != x)? false : (GOMOKU_VERSION_AI_MINOR != y)? false : true
#define IS_MAX_GOMOKU_VERSION_AI(x, y) (GOMOKU_VERSION_AI_MAJOR < x)? true : (GOMOKU_VERSION_AI_MAJOR > x)? false : (GOMOKU_VERSION_AI_MINOR <= y)? true : false
#define IS_MIN_GOMOKU_VERSION_AI(x, y) (GOMOKU_VERSION_AI_MAJOR < x)? false : (GOMOKU_VERSION_AI_MAJOR > x)? true : (GOMOKU_VERSION_AI_MINOR < y)? false : true

#endif /* !GOMOKUVERSION_HPP_ */
