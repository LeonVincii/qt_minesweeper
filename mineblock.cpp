#include "mineblock.h"

#include <iostream>

MineBlock::MineBlock(QObject *parent, int id) :
    QObject     (parent),
    m_id        (id),
    m_value     (0),
    m_is_mine   (false),
    m_revealed  (false)
{}

MineBlock::~MineBlock()
{}

void MineBlock::setNeighbors(MineBlock* top_left,
                             MineBlock* top,
                             MineBlock* top_right,
                             MineBlock* left,
                             MineBlock* right,
                             MineBlock* btm_left,
                             MineBlock* btm,
                             MineBlock* btm_right)
{
    m_neighbors[0] = top_left;
    m_neighbors[1] = top;
    m_neighbors[2] = top_right;
    m_neighbors[3] = left;
    m_neighbors[4] = right;
    m_neighbors[5] = btm_left;
    m_neighbors[6] = btm;
    m_neighbors[7] = btm_right;
}

void MineBlock::setMine(bool is_mine)
{
    m_is_mine = is_mine;
}

void MineBlock::setValue()
{
    if (m_is_mine) m_value = 99;
    else
        for (MineBlock* neighbor : m_neighbors)
            m_value += (neighbor == NULL) ? 0 : neighbor->isMine();
}

int MineBlock::reveal()
{
    m_revealed = true;
    // if reveal a mine, game is over
    if (m_is_mine) return -1;
    return m_value;
}

void MineBlock::draw()
{
    std::cout << "[";
    if (revealed()) {
        if (m_is_mine) std::cout << "X";
        else std::cout << m_value;
    }
    else std::cout << " ";
    std::cout << "]";
}
