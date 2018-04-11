#include "minezone.h"
#include "mineblock.h"

#include <cstdlib>
#include <iostream>

MineZone* MineZone::m_instance = nullptr;

MineZone::MineZone(QObject *parent, const Difficulty* difficulty) :
    QObject         (parent),
    m_difficulty    (difficulty),
    m_mine_blocks   (new MineBlockArr(difficulty->height * difficulty->width))
{
    std::cout << "MINEZONE >> Initializing mine zone with default difficulty: "
              << m_difficulty->difficulty << std::endl;
    // initialise mine blocks' id
    for (int i = 0; i < m_mine_blocks->size(); i ++) {
        (*m_mine_blocks)[i] = new MineBlock(nullptr, i + 1);
    }
    std::cout << "         >> Default Mine zone initialized successfully" << std::endl;
}

MineZone::~MineZone()
{
    for (MineBlock* mb : *m_mine_blocks) delete mb;
    delete m_mine_blocks;
}

MineZone* MineZone::instance(const Difficulty* difficulty)
{
    if (!m_instance) {
        m_instance = new MineZone(nullptr, difficulty);
    }
    return m_instance;
}

void MineZone::setDifficulty(const Difficulty* difficulty)
{
    m_difficulty = difficulty;

    //! \todo reinitialise m_mine_blocks
}

void MineZone::displayDifficulty()
{
    std::cout << "MINEZONE >> Current mine zone is set to the difficulty of: "
              << m_difficulty->difficulty << std::endl;
    std::cout << "         >> Dimension: "
              << m_difficulty->height << " × " << m_difficulty->width << std::endl;
    std::cout << "         >> Number of mines: "
              << m_difficulty->num_of_mines << std::endl;
}

void MineZone::initMines()
{
    int rdm;
    for (int num = 0; num < m_difficulty->num_of_mines;) {
        rdm = rand() % m_mine_blocks->size();
        if (!(*m_mine_blocks)[rdm]->isMine()) {
            (*m_mine_blocks)[rdm]->setMine(true);
            num ++;
        }
    }
    for (MineBlock* block : *m_mine_blocks) {
        int w = m_difficulty->width;
        int h = m_difficulty->height;
        if (block->id() % w == 0 && block->id() != w && block->id() != w*h)
            block->setNeighbors(
                (*m_mine_blocks)[block->id() - w - 1 - 1],
                (*m_mine_blocks)[block->id() - w     - 1],
                nullptr,
                (*m_mine_blocks)[block->id()     - 1 - 1],
                nullptr,
                (*m_mine_blocks)[block->id() + w - 1 - 1],
                (*m_mine_blocks)[block->id() + w     - 1],
                nullptr
            );
        else if (block->id() % w == 1 && block->id() != 1 && block->id() != (w*h - w + 1))
            block->setNeighbors(
                nullptr,
                (*m_mine_blocks)[block->id() - w     - 1],
                (*m_mine_blocks)[block->id() - w + 1 - 1],
                nullptr,
                (*m_mine_blocks)[block->id()     + 1 - 1],
                nullptr,
                (*m_mine_blocks)[block->id() + w     - 1],
                (*m_mine_blocks)[block->id() + w + 1 - 1]
           );
        else if (block->id() > 1 && block->id() < w)
            block->setNeighbors(
                nullptr,
                nullptr,
                nullptr,
                (*m_mine_blocks)[block->id()     - 1 - 1],
                (*m_mine_blocks)[block->id()     + 1 - 1],
                (*m_mine_blocks)[block->id() + w - 1 - 1],
                (*m_mine_blocks)[block->id() + w     - 1],
                (*m_mine_blocks)[block->id() + w + 1 - 1]
           );
        else if (block->id() > (w*h - w + 1) && block->id() < w*h)
            block->setNeighbors(
                (*m_mine_blocks)[block->id() - w - 1 - 1],
                (*m_mine_blocks)[block->id() - w     - 1],
                (*m_mine_blocks)[block->id() - w + 1 - 1],
                (*m_mine_blocks)[block->id()     - 1 - 1],
                (*m_mine_blocks)[block->id()     + 1 - 1],
                nullptr,
                nullptr,
                nullptr
           );
        else if (block->id() == 1)
            block->setNeighbors(
                nullptr,
                nullptr,
                nullptr,
                nullptr,
                (*m_mine_blocks)[block->id()     + 1 - 1],
                nullptr,
                (*m_mine_blocks)[block->id() + w - 1 - 1],
                (*m_mine_blocks)[block->id() + w + 1 - 1]
           );
        else if (block->id() == w)
            block->setNeighbors(
                nullptr,
                nullptr,
                nullptr,
                (*m_mine_blocks)[block->id()     - 1 - 1],
                nullptr,
                (*m_mine_blocks)[block->id() + w - 1 - 1],
                (*m_mine_blocks)[block->id() + w     - 1],
                nullptr
           );
        else if (block->id() == (w*h - w + 1))
            block->setNeighbors(
                nullptr,
                (*m_mine_blocks)[block->id() - w     - 1],
                (*m_mine_blocks)[block->id() - w + 1 - 1],
                nullptr,
                (*m_mine_blocks)[block->id()     + 1 - 1],
                nullptr,
                nullptr,
                nullptr
           );
        else if (block->id() == w*h)
            block->setNeighbors(
                (*m_mine_blocks)[block->id() - w - 1 - 1],
                (*m_mine_blocks)[block->id() - w     - 1],
                nullptr,
                (*m_mine_blocks)[block->id()     - 1 - 1],
                nullptr,
                nullptr,
                nullptr,
                nullptr
           );
        else
            block->setNeighbors(
                (*m_mine_blocks)[block->id() - w - 1 - 1],
                (*m_mine_blocks)[block->id() - w     - 1],
                (*m_mine_blocks)[block->id() - w + 1 - 1],
                (*m_mine_blocks)[block->id()     - 1 - 1],
                (*m_mine_blocks)[block->id()     + 1 - 1],
                (*m_mine_blocks)[block->id() + w - 1 - 1],
                (*m_mine_blocks)[block->id() + w     - 1],
                (*m_mine_blocks)[block->id() + w + 1 - 1]
           );
        block->setValue();
    }
}

void MineZone::dev_showMines()
{
    for (MineBlock* block : *m_mine_blocks) {
        if (block->isMine()) std::cout << "X";
        else std::cout << block->value();
        if (block->id() % 9 == 0) std::cout << '\n';
        else std::cout << '\t';
    }
}
