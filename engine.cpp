#include "engine.h"
#include "minezone.h"

#include <iostream>
#include <QStringList>
#include <QTextStream>

QTextStream in  (stdin);
QTextStream out (stdout, QIODevice::WriteOnly);

Engine* Engine::m_instance = nullptr;

Engine::Engine(QObject *parent) :
    QObject         (parent),
    m_difficulty    (&EASY)
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
    std::cout << "ENGINE >> Engine is on" << std::endl;

    while (true) {
        std::cout << "ENGINE $$ (start | setdiff [easy|normal|hard] | quit) ";
        QString     cmd     = in.readLine();
        QStringList command = cmd.split(" ");

        if (!QString::compare(command.at(0), "start")) Engine::startGame();
        else if (!QString::compare(command.at(0), "setdiff")) {
            if      (!QString::compare(command.at(1), "easy"))   m_difficulty = &EASY;
            else if (!QString::compare(command.at(1), "normal")) m_difficulty = &NORMAL;
            else if (!QString::compare(command.at(1), "hard"))   m_difficulty = &HARD;
            else    std::cout << "ENGINE >> Command not recognized" << std::endl;
        }
        else if (!QString::compare(command.at(0), "quit"))        break;
        else    std::cout << "ENGINE >> Command not recognized" << std::endl;
    }
}

void Engine::off()
{
    Engine::~Engine();
}

void Engine::startGame()
{
    m_minezone = new MineZone(NULL, m_difficulty);
    std::string name;
    std::cout << "ENGINE >> Starting game" << std::endl;
    std::cout << "ENGINE >> Please enter your name to start" << std::endl;
    std::cout << "ENGINE $$ ";
    std::cin  >> name;
    std::cout << "ENGINE >> (r x y) for revealing block [x, y]" << std::endl;
    std::cout << "ENGINE >> (m x y) for marking block [x, y] as mine" << std::endl;
    std::cout << "ENGINE >> (back) to get back to menu" << std::endl;
    m_minezone->initMines();
    bool alive = false;
    do {
        m_minezone->drawBlocks();
        std::cout << name << " $$ ";
        in.skipWhiteSpace();
        QString cmd = in.readLine();
        QStringList command = cmd.split(' ');
        if      (!QString::compare(command.at(0), "cheat")) m_minezone->cheat_showMines();
        else if (!QString::compare(command.at(0), "back")) break;
        else {
            int x = command.at(1).toInt();
            int y = command.at(2).toInt();
            if (!QString::compare(command.at(0), "r"))
                alive = m_minezone->revealBlock(x, y);
            else if (!QString::compare(command.at(0), "m")) {
                alive = true;
                m_minezone->markBlock(x, y);
            }
        }
    } while(alive);
    delete m_minezone;
}

void Engine::gameOver()
{
    std::cout << "ENGINE >> Game over" << std::endl;
}

void Engine::restart()
{
    std::cout << "ENGINE >> Restarting game" << std::endl;
}
