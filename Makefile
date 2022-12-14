##
## EPITECH PROJECT, 2022
## Gomoku
## File description:
## Makefile
##

BIN_NAME	=	pbrain-gomoku-ai

include src/Utils/Makefile

#
# To include your IA source :
# CPP : IA_CPP_SOURCES = <file>
# HPP : INCLUDES += <PATH IA HPP>
#

IA_CPP_SOURCES += src/IaTest/IaTest.cpp
INCLUDES += -I src/IaTest/


.PHONY: all fclean clean re

all:	$(BIN_NAME)

fclean: clean
	@rm -rf $(BIN_NAME)

clean:
	@rm -rf $(OBJ_SRC)

re: fclean all

$(BIN_NAME):	$(OBJ_SRC)
	@g++ $(FLAGS) -o $(BIN_NAME) $(OBJ_SRC) $(INCLUDES) $(LIBS)

