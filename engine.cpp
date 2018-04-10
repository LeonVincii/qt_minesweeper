#include "engine.h"
#include "minezone.h"

#include <iostream>

Engine* Engine::m_instance = nullptr;

Engine::Engine(QObject *parent) : QObject(parent)
{
    qDebug(">> Setting game difficulty to EASY (default)");
    Engine::setDifficulty(EASY);
    qDebug() << ">> Number of mines: " << m_current_difficulty.num_of_mines;
}

Engine* Engine::instance()
{
    if (!m_instance) {
        m_instance = new Engine();
    }
    return m_instance;
}

void Engine::setDifficulty(const Difficulty& difficulty)
{
    m_current_difficulty = difficulty;
}

void Engine::start()
{
    std::cout << ">> Starting game with difficulty: "
              << m_current_difficulty.difficulty << std::endl;

    // start timer
    std::cout << ">> Starting timer" << std::endl;

    // initialise number of mine
    std::cout << ">> Remaining mines: " << m_current_difficulty.num_of_mines << std::endl;

    // initialise MineZone
    std::cout << ">> Initializing mine zone" << std::endl;
    m_minezone = MineZone::instance(m_current_difficulty.dimension);
}

void Engine::gameOver()
{

}

void Engine::restart()
{

}
