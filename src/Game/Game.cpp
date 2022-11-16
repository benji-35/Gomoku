/*
** EPITECH PROJECT, 2022
** Gomoku
** File description:
** Game
*/

#include "Game.hpp"
#include <iostream>
#include <sstream>
#include "Vector.hpp"

void Gomoku::Game::start() {
    if (_ia.use_count() == 0) {
        Communication::sendError("Can't play with this IA, ia not set !");
        return;
    }
    _running = true;
    __initCommands();

    while (_running) {
        readCommand();
    }
}

void Gomoku::Game::readCommand() {
    std::string cmd = "";
    std::getline(std::cin, cmd);
    if (cmd == "")
        return;
    std::vector<std::string> cmds = splitString(cmd, " ");
    std::vector<std::string> args;
    for (std::size_t i = 1; i < cmds.size(); i++) {
        args.push_back(cmds[i]);
    }
    
    auto it = _commands.find(cmds[0]);
    if (it == _commands.end()) {
        Communication::sendError("Command " + cmds[0] + " unknown");
        return;
    } else {
        it->second(args);
    }
}

bool Gomoku::Game::__canPlay() {
    if (getIA()->getBoardWidth() == 0 || getIA()->getBoardHeight() == 0)
        return false;
    return true;
}

void Gomoku::Game::__initCommands() {
    _commands.insert(std::pair<std::string, std::function<void (std::vector<std::string>)>>("START", [this](std::vector<std::string> args) {
        //start command
    }));
    _commands.insert(std::pair<std::string, std::function<void (std::vector<std::string>)>>("TURN", [this](std::vector<std::string> args) {
        //turn command
    }));
    _commands.insert(std::pair<std::string, std::function<void (std::vector<std::string>)>>("BEGIN", [this](std::vector<std::string> args) {
        //begin command
    }));
    _commands.insert(std::pair<std::string, std::function<void (std::vector<std::string>)>>("BOARD", [this](std::vector<std::string> args) {
        //board command
    }));
    _commands.insert(std::pair<std::string, std::function<void (std::vector<std::string>)>>("INFO", [this](std::vector<std::string> args) {
        //info command
    }));
    _commands.insert(std::pair<std::string, std::function<void (std::vector<std::string>)>>("END", [this](std::vector<std::string> args) {
        getIA()->stopAll();
    }));
    _commands.insert(std::pair<std::string, std::function<void (std::vector<std::string>)>>("ABOUT", [this](std::vector<std::string> args) {
        Communication::sendAbout(getIA()->getAbout());
    }));
    _commands.insert(std::pair<std::string, std::function<void (std::vector<std::string>)>>("RECSTART", [this](std::vector<std::string> args) {
        if (args.size() != 2) {
            Communication::sendError("You need 2 parameters to use RECSTART");
            return;
        }
        std::stringstream s1;
        std::stringstream s2;
        int v1;
        int v2;

        s1 << args[0];
        s2 << args[1];

        s1 >> v1;
        s2 >> v2;
        //recstart command
        if (v1 <= 0 || v2 <= 0) {
            Communication::sendError("All parameters must be higher than 0");
        } else {
            getIA()->setBoardSize(v1, v2);
            getIA()->restartIA();
            Communication::sendOK();
        }
    }));
    _commands.insert(std::pair<std::string, std::function<void (std::vector<std::string>)>>("RESTART", [this](std::vector<std::string> args) {
        if (!getIA()->restartIA()) {
            Communication::sendError("Can't restart the party");
        } else {
            Communication::sendOK();
        }
    }));
    _commands.insert(std::pair<std::string, std::function<void (std::vector<std::string>)>>("TAKEBACK", [this](std::vector<std::string> args) {
        if (!getIA()->backMove()) {
            Communication::sendError("Failed to TAKEBACK");
        } else {
            Communication::sendOK();
        }
    }));
    _commands.insert(std::pair<std::string, std::function<void (std::vector<std::string>)>>("PLAY", [this](std::vector<std::string> args) {
        if (args.size() != 2) {
            Communication::sendError("You need 2 parameters to use PLAY");
            return;
        }
        std::stringstream s1;
        std::stringstream s2;
        Vector pos;

        int val;
        //set x position
        s1 << args[0];
        s1 >> val;
        pos.setX(val);

        //set y position
        s2 << args[1];
        s2 >> val;
        pos.setY(val);
        if (!getIA()->setMove(pos)) {
            Communication::sendError("Can't move to position " + pos.to_string());
        } else {
            Communication::sendOK();
        }
    }));
}
