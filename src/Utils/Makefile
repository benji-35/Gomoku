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

GAME_PATH	=	$(MAIN_PATH)Game/
IA_PATH		=	$(MAIN_PATH)IA/
UTILS_PATH	=	$(MAIN_PATH)Utils/

INCLUDES =	-I $(MAIN_PATH) -I $(GAME_PATH) -I $(UTILS_PATH) -I $(IA_PATH)

LIBS	=

CPP_SOURCES	=	$(MAIN_PATH)Main.cpp

GAME_CPP_SOURCES	=	$(GAME_PATH)Game.cpp
IA_CPP_SOURCES		=

CPP_SOURCES += $(GAME_CPP_SOURCES)

OBJ_SRC	=	$(CPP_SOURCES:.cpp=.o)

%.o: %.cpp
	@echo "COMPILING [$@] > [CPP: $<]"
	@g++ -c $< $(INCLUDES) -o $@ -g
