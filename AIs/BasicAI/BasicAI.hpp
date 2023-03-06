/*
** EPITECH PROJECT, 2022
** Gomoku
** File description:
** IaTest
*/

#ifndef BASIC_AI_GOMOKU_HPP_
#define BASIC_AI_GOMOKU_HPP_

#include "Gomoku.hpp"

namespace Gomoku {

    class BasicAI : public AbstractIA {
        public:

            struct CheckIntel {
                int size;
                Vector pos;

                CheckIntel(int size, Vector pos) : size(size), pos(pos) {}
                CheckIntel(Vector pos, int size) : size(size), pos(pos) {}
            };

            enum PatternType {
                HORIZONTAL,
                VERTICAL,
                DIAGONAL_BOTTOM_LEFT_TOP_RIGHT,
                DIAGONAL_TOP_LEFT_BOTTOM_RIGHT
            };

            BasicAI(std::string name = "My AI", std::string version = "1.0.0", std::string author = "benji-35", std::string country = "France");
            ~BasicAI();

            virtual Vector chooseBestMove() override;
            virtual Vector myAIAlgo();

        protected:
            std::vector<CheckIntel> getBestMoves(MoveType ref, bool preshot = false);
            std::vector<CheckIntel> getBestMoves(MoveType ref, std::vector<PosHistory> historic, bool preshot = false);
            Vector getRandomMove();
            std::size_t getBestMove(std::vector<CheckIntel> moves, bool takePreshots = false);

        private:
            void checkPosMoves(std::vector<CheckIntel> &bestMoves, Vector pos, PatternType type, MoveType ref, std::vector<PosHistory> hist);
            void __checkHor(std::vector<CheckIntel> &bestMoves, Vector pos, MoveType ref, std::vector<PosHistory> hist);
            void __checkVer(std::vector<CheckIntel> &bestMoves, Vector pos, MoveType ref, std::vector<PosHistory> hist);
            void __checkDiagBLTR(std::vector<CheckIntel> &bestMoves, Vector pos, MoveType ref, std::vector<PosHistory> hist);
            void __checkDiagTLBR(std::vector<CheckIntel> &bestMoves, Vector pos, MoveType ref, std::vector<PosHistory> hist);
            bool shouldCalculHere(Vector pos, MoveType ref, std::vector<PosHistory> hist);
            void debugMoves(std::vector<CheckIntel> moves);
            bool entoureByOpponent(Vector pos, MoveType yourType, PatternType pattern, std::vector<PosHistory> hist);
    };

}

#endif /* !BASIC_AI_GOMOKU_HPP_ */
