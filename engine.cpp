#include "engine.h"

#include <iostream>

Engine::Engine(QObject *parent) :
    QObject     (parent),
    m_minezone  (new MineZone(nullptr, &EASY)),
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
    m_timer->start(1000);
}

void Engine::restartGame()
{
    m_time = 0;
    delete m_minezone;
    m_minezone = new MineZone(nullptr, m_difficulty);
    Engine::startGame();
}

void Engine::changeDifficulty(const Difficulty* difficulty)
{
    /*! \todo Connect to main widget and refresh minezone. */
}

void Engine::revealBlock(int id)
{

    QVector<int> ids = m_minezone->revealBlock(id);
    if (ids.first() == -1) {
        m_timer->stop();
        emit gameOver();
    }
    else {
        if (m_minezone->countdown() == 0) {
            m_timer->stop();
            emit win(Qt::MouseButton::LeftButton, ids);
        }
        else
            emit updateMineZoneView(Qt::MouseButton::LeftButton, ids);
    }
}

void Engine::markBlock(int id)
{
    int mark = m_minezone->markBlock(id);
    if (m_minezone->countdown() == 0) {
        m_timer->stop();
        emit win(Qt::MouseButton::RightButton, QVector<int>({mark}));
    }
    else
        emit updateMineZoneView(Qt::MouseButton::RightButton, QVector<int>({mark}));
}

int Engine::valueAtId(int id) const
{
    const MineBlock* mb = m_minezone->mineBlockAt(id);
    return mb->value();
}

int Engine::coord2Id(int x, int y)
{
    return (y*m_difficulty->width + x + 1);
}

void Engine::on_timeout()
{
    m_time ++;
    emit timeout();
}
