/*
** EPITECH PROJECT, 2022
** Gomoku AI 2
** File description:
** BestMinMax
*/

#ifndef BESTMINMAX_HPP_
#define BESTMINMAX_HPP_

#include "Gomoku.hpp"
#include "BasicAI/BasicAI.hpp"

namespace Gomoku {

    class BestMinMax : public BasicAI {
        public:
            enum WinningState {
                WIN = 0,
                LOSE,
                SAME,
                NONE
            };

            struct MinMaxIntel {
                MoveType player;
                Vector pos;
                int score;
                WinningState state = NONE;
            };

            BestMinMax();
            ~BestMinMax();

            Vector chooseBestMove() override;

            std::vector<MinMaxIntel> getMinMax(std::vector<PosHistory> history, int depth = 0);
            bool isWinningMove(MoveType player, Vector pos, std::vector<PosHistory> history);

        protected:
        private:
    };

}

#endif /* !BESTMINMAX_HPP_ */
