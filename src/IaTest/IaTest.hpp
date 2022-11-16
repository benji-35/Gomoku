/*
** EPITECH PROJECT, 2022
** Gomoku
** File description:
** IaTest
*/

#ifndef IATEST_HPP_
#define IATEST_HPP_

#include "Gomoku.hpp"

namespace Gomoku {

    class IaTest : public AbstractIA {
        public:
            IaTest();
            ~IaTest();

            Vector chooseBestMove() override;

        protected:
        private:
    };

}

#endif /* !IATEST_HPP_ */
