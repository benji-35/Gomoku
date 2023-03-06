/*
** EPITECH PROJECT, 2022
** Gomoku
** File description:
** test_criterion
*/

#include "Gomoku.hpp"
#include "BestMinMax/BestMinMax.hpp"
#include "BenjiAI/BenjiAI.hpp"

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include <string>

using namespace Gomoku;

void redirect_all_stdout_simple(void) {
        cr_redirect_stdout();
        cr_redirect_stderr();
}

//all easy mandatories for ai

Test(Mandatories, Mandatory1, .init=redirect_all_stdout_simple) {
    BenjiAI ai;
    ai.setBoardSize(20);
    ai.setMove(Vector(0, 0), MoveType::IA_MOVE, true);
    ai.setMove(Vector(1, 0), MoveType::IA_MOVE, true);
    ai.setMove(Vector(2, 0), MoveType::IA_MOVE, true);
    ai.setMove(Vector(3, 0), MoveType::IA_MOVE, true);

    cr_assert(ai.chooseBestMove() == Vector(4, 0));
}

Test(Mandatories, Mandatory2, .init=redirect_all_stdout_simple) {
    BenjiAI ai;
    ai.setBoardSize(20);
    ai.setMove(Vector(0, 0), MoveType::IA_MOVE, true);
    ai.setMove(Vector(0, 1), MoveType::IA_MOVE, true);
    ai.setMove(Vector(0, 2), MoveType::IA_MOVE, true);
    ai.setMove(Vector(0, 3), MoveType::IA_MOVE, true);

    cr_assert(ai.chooseBestMove() == Vector(0, 4));
}

Test(Mandatories, Mandatory3, .init=redirect_all_stdout_simple) {
    BenjiAI ai;
    ai.setBoardSize(20);
    ai.setMove(Vector(0, 0), MoveType::IA_MOVE, true);
    ai.setMove(Vector(1, 1), MoveType::IA_MOVE, true);
    ai.setMove(Vector(2, 2), MoveType::IA_MOVE, true);
    ai.setMove(Vector(3, 3), MoveType::IA_MOVE, true);

    cr_assert(ai.chooseBestMove() == Vector(4, 4));
}

Test(Mandatories, Mandatory4, .init=redirect_all_stdout_simple) {
    BenjiAI ai;
    ai.setBoardSize(20);
    ai.setMove(Vector(10, 10), MoveType::IA_MOVE, true);
    ai.setMove(Vector(9, 11), MoveType::IA_MOVE, true);
    ai.setMove(Vector(8, 12), MoveType::IA_MOVE, true);
    ai.setMove(Vector(7, 13), MoveType::IA_MOVE, true);

    cr_assert((ai.chooseBestMove() == Vector(6, 14)) || (ai.chooseBestMove() == Vector(11, 9)));
}

Test(Mandatories, Mandatory5, .init=redirect_all_stdout_simple) {
    BenjiAI ai;
    ai.setBoardSize(20);
    ai.setMove(Vector(0, 0), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(1, 0), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(2, 0), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(3, 0), MoveType::GAME_MOVE, true);

    cr_assert(ai.chooseBestMove() == Vector(4, 0));
}

Test(Mandatories, Mandatory6, .init=redirect_all_stdout_simple) {
    BenjiAI ai;
    ai.setBoardSize(20);
    ai.setMove(Vector(0, 0), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(0, 1), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(0, 2), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(0, 3), MoveType::GAME_MOVE, true);

    cr_assert(ai.chooseBestMove() == Vector(0, 4));
}

Test(Mandatories, Mandatory7, .init=redirect_all_stdout_simple) {
    BenjiAI ai;
    ai.setBoardSize(20);
    ai.setMove(Vector(0, 0), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(1, 1), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(2, 2), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(3, 3), MoveType::GAME_MOVE, true);

    cr_assert(ai.chooseBestMove() == Vector(4, 4));
}

Test(Mandatories, Mandatory8, .init=redirect_all_stdout_simple) {
    BenjiAI ai;
    ai.setBoardSize(20);
    ai.setMove(Vector(10, 10), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(9, 11), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(8, 12), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(7, 13), MoveType::GAME_MOVE, true);

    auto result = ai.chooseBestMove();

    cr_assert((result == Vector(6, 14)) || (result == Vector(11, 9)), "Got: {%d, %d}. But excpected: {%d, %d} or {%d, %d}", result.getX(), result.getY(), 6, 14, 11, 9);
}

//easy for ai

Test(Easy, Easy1, .init=redirect_all_stdout_simple) {
    BenjiAI ai;
    ai.setBoardSize(20);
    ai.setMove(Vector(1, 0), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(2, 0), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(3, 0), MoveType::GAME_MOVE, true);

    auto result = ai.chooseBestMove();

    cr_assert((result == Vector(0, 0)) || (result == Vector(4, 0)), "Got: {%d, %d} but expected {%d, %d} or {%d, %d}", result.getX(), result.getY(), 0, 0, 4, 0);
}

Test(Easy, Easy2, .init=redirect_all_stdout_simple) {
    BenjiAI ai;
    ai.setBoardSize(20);
    ai.setMove(Vector(0, 1), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(0, 2), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(0, 3), MoveType::GAME_MOVE, true);

    auto result = ai.chooseBestMove();

    cr_assert((result == Vector(0, 0)) || (result == Vector(0, 4)), "Got: {%d, %d} but expected {%d, %d} or {%d, %d}", result.getX(), result.getY(), 0, 0, 0, 4);
}

Test(Easy, Easy3, .init=redirect_all_stdout_simple) {
    BenjiAI ai;
    ai.setBoardSize(20);
    ai.setMove(Vector(1, 1), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(2, 2), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(3, 3), MoveType::GAME_MOVE, true);

    auto result = ai.chooseBestMove();

    cr_assert((result == Vector(0, 0)) || (result == Vector(4, 4)), "Got: {%d, %d} but expected {%d, %d} or {%d, %d}", result.getX(), result.getY(), 0, 0, 4, 4);
}

Test(Easy, Easy4, .init=redirect_all_stdout_simple) {
    BenjiAI ai;
    ai.setBoardSize(20);
    ai.setMove(Vector(10, 10), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(9, 11), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(8, 12), MoveType::GAME_MOVE, true);

    auto result = ai.chooseBestMove();

    cr_assert((result == Vector(11, 9)) || (result == Vector(7, 13)), "Got: {%d, %d} but expected {%d, %d} or {%d, %d}", result.getX(), result.getY(), 11, 9, 7, 13);
}

//choose better positions

Test(ChooseBetterPositions, Choose1, .init=redirect_all_stdout_simple) {
    BenjiAI ai;
    ai.setBoardSize(20);

    ai.setMove(Vector(0, 0), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(1, 0), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(2, 0), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(3, 0), MoveType::GAME_MOVE, true);

    ai.setMove(Vector(0, 2), MoveType::IA_MOVE, true);
    ai.setMove(Vector(1, 2), MoveType::IA_MOVE, true);
    ai.setMove(Vector(2, 2), MoveType::IA_MOVE, true);
    ai.setMove(Vector(3, 2), MoveType::IA_MOVE, true);

    auto result = ai.chooseBestMove();

    cr_assert((result == Vector(4, 2)), "Got: {%d, %d}. But expected {%d, %d}", result.getX(), result.getY(), 4, 2);
}

Test(ChooseBetterPositions, Choose2, .init=redirect_all_stdout_simple) {
    BenjiAI ai;
    ai.setBoardSize(20);

    ai.setMove(Vector(0, 0), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(1, 0), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(3, 0), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(4, 0), MoveType::GAME_MOVE, true);

    ai.setMove(Vector(0, 2), MoveType::IA_MOVE, true);
    ai.setMove(Vector(1, 2), MoveType::IA_MOVE, true);
    ai.setMove(Vector(2, 2), MoveType::IA_MOVE, true);

    auto result = ai.chooseBestMove();

    cr_assert((result == Vector(2, 0)), "Got: {%d, %d}. But expected {%d, %d}", result.getX(), result.getY(), 2, 0);
}

Test(ChooseBetterPositions, Choose3, .init=redirect_all_stdout_simple) {
    BenjiAI ai;
    ai.setBoardSize(20);

    ai.setMove(Vector(0, 0), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(1, 0), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(3, 0), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(4, 0), MoveType::GAME_MOVE, true);

    ai.setMove(Vector(0, 2), MoveType::IA_MOVE, true);
    ai.setMove(Vector(1, 2), MoveType::IA_MOVE, true);
    ai.setMove(Vector(2, 2), MoveType::IA_MOVE, true);

    auto result = ai.chooseBestMove();

    cr_assert((result == Vector(2, 0)), "Got: {%d, %d}. But expected {%d, %d}", result.getX(), result.getY(), 2, 0);
}

//Hard choose
Test(Hard, ChooseHard1, .init=redirect_all_stdout_simple) {
    BenjiAI ai;
    ai.setBoardSize(20);
    //set enemy moves
    ai.setMove(Vector(10, 14), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(11, 14), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(12, 14), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(14, 15), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(15, 16), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(13, 17), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(13, 18), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(13, 19), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(12, 19), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(14, 19), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(16, 19), MoveType::GAME_MOVE, true);

    //set ia moves
    ai.setMove(Vector(11, 19), MoveType::IA_MOVE, true);
    ai.setMove(Vector(12, 18), MoveType::IA_MOVE, true);
    ai.setMove(Vector(12, 17), MoveType::IA_MOVE, true);
    ai.setMove(Vector(12, 16), MoveType::IA_MOVE, true);
    ai.setMove(Vector(12, 15), MoveType::IA_MOVE, true);
    ai.setMove(Vector(13, 16), MoveType::IA_MOVE, true);
    ai.setMove(Vector(14, 17), MoveType::IA_MOVE, true);
    ai.setMove(Vector(15, 18), MoveType::IA_MOVE, true);
    ai.setMove(Vector(15, 19), MoveType::IA_MOVE, true);

    auto result = ai.chooseBestMove();
    cr_assert((result == Vector(13, 14)), "Got: {%d, %d}. But expected {%d, %d}", result.getX(), result.getY(), 13, 14);
}

Test(Hard, ChooseHard2, .init=redirect_all_stdout_simple) {
    BenjiAI ai;
    ai.setBoardSize(20);
    //set enemy moves
    ai.setMove(Vector(2, 1), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(2, 2), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(2, 3), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(1, 4), MoveType::GAME_MOVE, true);
    ai.setMove(Vector(3, 4), MoveType::GAME_MOVE, true);


    auto result = ai.chooseBestMove();
    cr_assert((result == Vector(2, 4)), "Got: {%d, %d}. But expected {%d, %d}", result.getX(), result.getY(), 2, 4);
}
