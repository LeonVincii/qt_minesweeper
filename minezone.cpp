#include "minezone.h"
#include "mineblock.h"

#include <iostream>

MineZone* MineZone::m_instance = nullptr;

MineZone::MineZone(QObject *parent, int dimension) :
    QObject         (parent),
    m_dimension     (dimension),
    m_mine_blocks   (new MineBlockArr(dimension*dimension))
{
    // initialise mine blocks' id
    for (int i = 0; i < m_mine_blocks->size(); i ++) {
        (*m_mine_blocks)[i] = new MineBlock(nullptr, i+1);
    }
    std::cout << ">> Mine zone initialized successfully" << std::endl;
    for (MineBlock* block : *m_mine_blocks) {
        std::cout << block->id();
        if (block->id() % 9 == 0) std::cout << '\n';
        else std::cout << '\t';
    }
}

MineZone* MineZone::instance(int dimension)
{
    if (!m_instance) {
        m_instance = new MineZone(nullptr, dimension);
    }
    return m_instance;
}
