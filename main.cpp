#include "mainwindow.h"
#include "engine.h"

#include <QApplication>
#include <QDebug>
#include <QString>

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication minesweeper(argc, argv);
    std::cout << ">> Initialising game engine" << std::endl;
    Engine* engine = Engine::instance();
    std::cout << ">> Engine initialisation successfully" << std::endl;

    std::string cmd;

    while (cmd != "quit") {
        std::cout << "start | showdiff | setdiff $$ ";
        std::cin >> cmd;

        if (!cmd.compare("start")) {
            engine->start();
        }
        else if (!cmd.compare("setdiff")) {
            std::cout << "easy | normal | hard $$ ";
            std::string diff;
            std::cin >> diff;
            std::cout << ">> Setting difficulty to: " << diff << std::endl;
            if      (!diff.compare("easy"))   engine->setDifficulty(EASY);
            else if (!diff.compare("normal")) engine->setDifficulty(NORMAL);
            else if (!diff.compare("hard"))   engine->setDifficulty(HARD);
            else    std::cout << ">> Command not recognized" << std::endl;
        }
        else if (!cmd.compare("showdiff")) {
            std::cout << ">> Game difficulty set to: "
                      << engine->difficulty().difficulty << std::endl;
        }
    }

    return minesweeper.exec();
}
