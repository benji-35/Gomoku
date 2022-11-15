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

INCLUDES =	-I $(MAIN_PATH) -I $(COM_PATH) -I $(GAME_PATH)

LIBS	=

CPP_SOURCES	=	$(MAIN_PATH)Main.cpp

GAME_CPP_SOURCES	=	$(GAME_PATH)Game.cpp
COM_CPP_SOURCES	=	$(COM_PATH)Communication.cpp

CPP_SOURCES += $(GAME_CPP_SOURCES)
CPP_SOURCES += $(COM_CPP_SOURCES)

OBJ_SRC	=	$(CPP_SOURCES:.cpp=.o)

%.o: %.cpp
	@echo "COMPILING [$@] > [CPP: $<]"
	@g++ -c $< $(INCLUDES) -o $@ -g
