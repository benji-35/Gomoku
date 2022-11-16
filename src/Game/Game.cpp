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
    std::vector<std::string> cmds = Communication::readManager();
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
        if (args.size() != 1) {
            Communication::sendError("You need 1 parameter to use START (size of map)");
            return;
        }
        std::size_t val;
        std::stringstream ss;
        ss << args[0];
        ss >> val;
        if (val <= 0) {
            Communication::sendError("The parameter must be higher than 0");
            return;
        }
        getIA()->startIA(val);
    }));
    _commands.insert(std::pair<std::string, std::function<void (std::vector<std::string>)>>("TURN", [this](std::vector<std::string> args) {
        if (args.size() != 1) {
            Communication::sendError("You need 1 parameter to use TURN (X,Y)");
            return;
        }
        std::vector<std::string> poses = Communication::splitString(args[0], ",");
        if (poses.size() != 2) {
            Communication::sendError("You need 1 parameter to use TURN (X,Y) parameter=" + args[0]);
            return;
        }
        Vector pos;
        std::stringstream s1;
        std::stringstream s2;
        int v1;
        int v2;

        s1 << poses[0];
        s2 << poses[1];

        s1 >> v1;
        s2 >> v2;

        pos.setX(v1);
        pos.setY(v2);

        if (!getIA()->setMove(pos, MoveType::GAME_MOVE)) {
            Communication::sendError("You can't pos at this positions: " + pos.to_string());
            return;
        }
        if (!__canPlay()) {
            Communication::sendError("IA can't play in this game");
            return;
        }
        pos = getIA()->chooseBestMove();
        if (!getIA()->setMove(pos)) {
            Communication::sendDebug("IA you can't pos at this positions: " + pos.to_string());
        }
    }));
    _commands.insert(std::pair<std::string, std::function<void (std::vector<std::string>)>>("BEGIN", [this](std::vector<std::string> args) {
        if (!__canPlay()) {
            Communication::sendError("IA can't play in this game");
            return;
        }
        Vector pos = getIA()->chooseBestMove();
        if (!getIA()->setMove(pos)) {
            Communication::sendDebug("IA you can't pos at this positions: " + pos.to_string());
        }
    }));
    _commands.insert(std::pair<std::string, std::function<void (std::vector<std::string>)>>("BOARD", [this](std::vector<std::string> args) {
        if (args.size() > 0) {
            Communication::sendError("BOARD do not have any arguments");
            return;
        }
        if (!__canPlay()) {
            Communication::sendError("No one can play in this game");
            return;
        }
        std::vector<Vector> p1;
        std::vector<Vector> p2;
        std::vector<std::string> tmpCmd;
        std::string tmpValues = "";
        while (tmpValues != "DONE") {
            tmpValues = "";
            tmpCmd = Communication::readManager();
            if (tmpCmd.size() == 1) {
                tmpValues = tmpCmd[0];
                if (tmpValues == "DONE")
                    break;
                std::vector<std::string> splitted = Communication::splitString(tmpValues, ",");
                if (splitted.size() == 3) {
                        Vector pos;
                        std::stringstream ss1;
                        std::stringstream ss2;
                        std::stringstream ss3;
                        int p = -1;
                        int x = -1;
                        int y = -1;

                        ss1 << splitted[0];
                        ss2 << splitted[1];
                        ss3 << splitted[2];

                        ss3 >> p;
                        ss2 >> y;
                        ss1 >> x;

                        pos.setX(x);
                        pos.setY(y);

                    if (p == 1) {
                        p1.push_back(pos);
                    } else if (p == 2) {
                        p2.push_back(pos);
                    }
                } else {
                    Communication::sendDebug("Bad input got splite size: " + std::to_string(splitted.size()));
                }
            }
        }
    
        for (std::size_t i = 0; i < p1.size(); i++) {
            if (!getIA()->setMove(p1[i], MoveType::GAME_MOVE)) {
                Communication::sendDebug("p1 board " + p1[i].to_string() + " can't be put");
            }
        }
        for (std::size_t i = 0; i < p2.size(); i++) {
            if (!getIA()->setMove(p2[i])) {
                Communication::sendDebug("p2 board " + p2[i].to_string() + " can't be put");
            }
        }
    }));
    _commands.insert(std::pair<std::string, std::function<void (std::vector<std::string>)>>("INFO", [this](std::vector<std::string> args) {
        //info command
    }));
    _commands.insert(std::pair<std::string, std::function<void (std::vector<std::string>)>>("END", [this](std::vector<std::string> args) {
        getIA()->stopAll();
        _running = false;
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
