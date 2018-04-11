#include "engine.h"
#include "minezone.h"

#include <iostream>

Engine* Engine::m_instance = nullptr;

Engine::Engine(QObject *parent) : QObject(parent)
{}

Engine::~Engine()
{
    delete m_minezone;
}

Engine* Engine::instance()
{
    if (!m_instance) {
        m_instance = new Engine();
    }
    return m_instance;
}

void Engine::on()
{
    m_minezone = MineZone::instance(&EASY);
    std::string cmd;

    std::cout << "ENGINE >> Engine is on" << std::endl;

    while (true) {
        std::cout << "ENGINE $$ (start | showdiff | setdiff | quit) ";
        std::cin >> cmd;

        if (!cmd.compare("start")) Engine::startGame();
        else if (!cmd.compare("setdiff")) {
            std::cout << "ENGINE $$ (easy | normal | hard) ";
            std::string diff;
            std::cin >> diff;
            if      (!diff.compare("easy"))   m_minezone->setDifficulty(&EASY);
            else if (!diff.compare("normal")) m_minezone->setDifficulty(&NORMAL);
            else if (!diff.compare("hard"))   m_minezone->setDifficulty(&HARD);
            else    std::cout << "ENGINE >> Command not recognized" << std::endl;
        }
        else if (!cmd.compare("showdiff")) m_minezone->displayDifficulty();
        else if (!cmd.compare("quit")) break;
        else std::cout << "ENGINE >> Command not recognized" << std::endl;
    }
}

void Engine::off()
{
    Engine::~Engine();
}

void Engine::startGame()
{
    std::cout << "ENGINE >> Starting game" << std::endl;
}

void Engine::gameOver()
{
    std::cout << "ENGINE >> Game over" << std::endl;
}

void Engine::restart()
{
    std::cout << "ENGINE >> Restarting game" << std::endl;
}
