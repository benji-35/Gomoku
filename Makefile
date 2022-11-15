##
## EPITECH PROJECT, 2022
## Gomoku
## File description:
## Makefile
##

BIN_NAME	=	pbrain-gomoku-ai

include src/Utils/Makefile

.PHONY: all fclean clean re

all:	$(BIN_NAME)

fclean:

clean:

re: clean all

$(BIN_NAME):	$(OBJ_SRC)
	@g++ -o $(BIN_NAME) $(OBJ_SRC) $(INCLUDES) $(LIBS)

