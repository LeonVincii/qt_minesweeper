#include "engine.h"
#include "minezone.h"

#include <QApplication>
#include <iostream>

int main(/*int argc, char *argv[]*/)
{
//    QApplication minesweeper(argc, argv);

    std::cout << ">> Initialising game engine" << std::endl;
    Engine* engine = Engine::instance();
    std::cout << ">> Engine initialisation successfully" << std::endl;
    std::cout << ">> Launching game engine" << std::endl;
    engine->on();
    std::cout << ">> Shutting down game engine" << std::endl;
    engine->off();
    std::cout << ">> Engine shut down" << std::endl;

    return 0;

//    return minesweeper.exec();
}
