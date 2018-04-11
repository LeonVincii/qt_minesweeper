#include "minezone.h"
#include "mineblock.h"

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
