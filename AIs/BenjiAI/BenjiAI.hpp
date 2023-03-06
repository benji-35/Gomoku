/*
** EPITECH PROJECT, 2022
** Gomoku
** File description:
** BenjiAI
*/

#ifndef BENJIAI_HPP_
#define BENJIAI_HPP_

#include "Gomoku.hpp"

namespace Gomoku {

    class BenjiAI : public AbstractIA {
        public:

            struct PosCalculated {
                Vector pos;
                int scoreAI;
                int scoreGame;
            };

            BenjiAI();
            ~BenjiAI();

            Vector chooseBestMove() override;
        
        protected:
        private:
            std::vector<PosCalculated> getPoses();
            Vector getRandomMove();

            void calculHorAt(Vector pos, PosCalculated &calc);
            void calculVerAt(Vector pos, PosCalculated &calc);
            void calculDiag1At(Vector pos, PosCalculated &calc);
            void calculDiag2At(Vector pos, PosCalculated &calc);

            bool shouldCalculate(Vector pos);

            bool isClosePositionHor(Vector pos, MoveType player);
            bool isClosePositionVer(Vector pos, MoveType player);
            bool isClosePositionDiag1(Vector pos, MoveType player);
            bool isClosePositionDiag2(Vector pos, MoveType player);
    };

}

#endif /* !BENJIAI_HPP_ */
