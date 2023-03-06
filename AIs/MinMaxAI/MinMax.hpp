/*
** EPITECH PROJECT, 2022
** Gomoku
** File description:
** MinMax
*/

#ifndef MINMAX_HPP_
#define MINMAX_HPP_

#include "Gomoku.hpp"
#include "BasicAI/BasicAI.hpp"

namespace Gomoku {
    class MinMax : public BasicAI {
        public:
            MinMax();
            ~MinMax();

            Vector chooseBestMove() override;

    protected:
    private:
        int minimax(std::vector<std::string> board, int depth, bool isMaximizing, int alpha, int beta);
        int checkWin(std::vector<std::string> board);
    };
}

#endif /* !MINMAX_HPP_ */
