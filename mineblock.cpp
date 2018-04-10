#include "mineblock.h"

MineBlock::MineBlock(QObject *parent, int id, int zone_dimen) :
    QObject     (parent),
    m_id        (id),
    m_is_mine   (false),
    m_value     (0)
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
    m_top_left_block    = top_left;
    m_top_block         = top;
    m_top_right_block   = top_right;
    m_left_block        = left;
    m_right_block       = right;
    m_btm_left_block    = btm_left;
    m_btm_block         = btm;
    m_btm_right_block   = btm_right;
}

void MineBlock::setMine(bool is_mine)
{
    m_is_mine = is_mine;
}

void MineBlock::setValue()
{
    int top_left_val    = (m_top_left_block == NULL)    ? 0 : m_top_left_block->isMine();
    int top_val         = (m_top_block == NULL)         ? 0 : m_top_block->isMine();
    int top_right_val   = (m_top_right_block == NULL)   ? 0 : m_top_right_block->isMine();
    int left_val        = (m_left_block == NULL)        ? 0 : m_left_block->isMine();
    int right_val       = (m_right_block == NULL)       ? 0 : m_right_block->isMine();
    int btm_left_val    = (m_btm_left_block == NULL)    ? 0 : m_btm_left_block->isMine();
    int btm_val         = (m_btm_block == NULL)         ? 0 : m_btm_block->isMine();
    int btm_right_val   = (m_btm_right_block == NULL)   ? 0 : m_btm_right_block->isMine();

    m_value     =   top_left_val + top_val + top_right_val +
                    left_val + right_val +
                    btm_left_val + btm_val + btm_right_val;
}


