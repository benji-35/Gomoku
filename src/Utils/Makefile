##
## EPITECH PROJECT, 2022
## Gomoku
## File description:
## Makefile
##

#
#	INCLUDES FOR SOURCE FILES
#

MAIN_PATH	=	src/

COM_PATH	=	$(MAIN_PATH)Communication/
GAME_PATH	=	$(MAIN_PATH)Game/
IA_PATH		=	$(MAIN_PATH)IA/
UTILS_PATH	=	$(MAIN_PATH)Utils/
AIS 		=	AIs/

INCLUDES =	-I $(MAIN_PATH) -I $(GAME_PATH) -I $(UTILS_PATH) -I $(IA_PATH) -I $(COM_PATH) -I $(AIS)

LIBS	=

CPP_SOURCES	=	$(MAIN_PATH)Main.cpp

TEST_SOURCES = 	tests/test_criterion.cpp

GAME_CPP_SOURCES	=	$(GAME_PATH)Game.cpp
BASIC_AI_SOURCES	=	$(AIS)BasicAI/BasicAI.cpp
IA_CPP_SOURCES		=

CPP_SOURCES += $(GAME_CPP_SOURCES)
CPP_SOURCES += $(IA_CPP_SOURCES)
CPP_SOURCES += $(BASIC_AI_SOURCES)

TEST_SOURCES += $(GAME_CPP_SOURCES)
TEST_SOURCES += $(IA_CPP_SOURCES)
TEST_SOURCES += $(BASIC_AI_SOURCES)

OBJ_SRC	=	$(CPP_SOURCES:.cpp=.o)

OBJ_TESTS = $(TEST_SOURCES:.cpp=.o)

FLAGS	=	-Wall -pedantic -ggdb -O2

%.o: %.cpp
	@echo "COMPILING [$@] > [CPP: $<]"
	@g++ $(FLAGS) -c $< $(INCLUDES) -o $@ -g
