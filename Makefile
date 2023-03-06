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
# Your AI have to be code in C++ and have to be in a folder in the AIs/yourFolder.
# CPP : IA_CPP_SOURCES = <file>
#

# Here example with a MinMaxAI
IA_CPP_SOURCES += AIs/MinMaxAI/MinMax.cpp
IA_CPP_SOURCES += AIs/BestMinMax/BestMinMax.cpp
IA_CPP_SOURCES += AIs/BenjiAI/BenjiAI.cpp

.PHONY: all fclean clean re

all:	$(BIN_NAME)

fclean: clean
	@rm -rf $(BIN_NAME)
	@rm -rf unit_tests

clean:
	@rm -rf $(OBJ_SRC)
	@rm -rf $(OBJ_TESTS)

re: fclean all

build-tests:	$(OBJ_TESTS)
	@g++ $(FLAGS) -o unit_tests $(OBJ_TESTS) $(INCLUDES) $(LIBS) -lcriterion

$(BIN_NAME):	$(OBJ_SRC)
	@g++ $(FLAGS) -o $(BIN_NAME) $(OBJ_SRC) $(INCLUDES) $(LIBS)

