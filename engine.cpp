#include "engine.h"

#include <iostream>

Engine::Engine(QObject *parent) :
    QObject     (parent),
    m_minezone  (new MineZone(NULL, &EASY)),
    m_difficulty(&EASY),
    m_timer     (new QTimer(this)),
    m_time      (0)
{
    connect(m_timer, &QTimer::timeout, this, &Engine::on_timeout);
}

Engine::~Engine()
{
    delete m_minezone;
    delete m_timer;
}

void Engine::startGame()
{
    m_minezone->initMines();
    m_timer->start(1000);
}

void Engine::restartGame()
{
    m_time = 0;
    delete m_minezone;
    m_minezone = new MineZone(nullptr, m_difficulty);
    Engine::startGame();
}

void Engine::on_timeout()
{
    m_time ++;
    std::cout << m_time << std::endl;
    emit timeout();
}
