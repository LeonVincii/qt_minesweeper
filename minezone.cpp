#include <cstdlib>
#include <ctime>
#include <iostream>
#include <queue>
#include <vector>
#include <QtAlgorithms>

#include "minezone.h"

MineZone::MineZone(QObject *parent, const Difficulty* difficulty) :
    QObject         (parent),
    m_difficulty    (difficulty),
    m_mine_blocks   (new MineBlockArr(difficulty->height * difficulty->width)),
    m_countdown     (difficulty->height * difficulty->width),
    m_flag_countdown (difficulty->num_of_mines)
{
    std::cout << "MINEZONE >> Initializing mine zone with difficulty: "
              << m_difficulty->difficulty << std::endl;

    // Initialise mine blocks' id
    for (int i = 0; i < m_mine_blocks->size(); i ++) {
        (*m_mine_blocks)[i] = new MineBlock(nullptr, i + 1);
    }
    MineZone::initMines();
    std::cout << "         >> Mine zone initialized successfully" << std::endl;
    MineZone::displayDifficulty();
}

MineZone::~MineZone()
{
    for (MineBlock* mb : *m_mine_blocks) delete mb;
    delete m_mine_blocks;
}

void MineZone::displayDifficulty() const
{
    std::cout << "MINEZONE >> Current mine zone is set to the difficulty of: "
              << m_difficulty->difficulty << std::endl;
    std::cout << "         >> Dimension: "
              << m_difficulty->width << " x " << m_difficulty->height << std::endl;
    std::cout << "         >> Number of mines: "
              << m_difficulty->num_of_mines << std::endl;
}

void MineZone::initMines()
{
    int rdm;
    srand(time(0));
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
                (*m_mine_blocks)[block->id() + w     - 1],
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

QVector<int> MineZone::revealBlock(int id)
{
    std::queue<MineBlock*> q;
    int                    dimen = m_difficulty->width * m_difficulty->height;
    std::vector<bool>      p(dimen);
    MineBlock*             root  = (*m_mine_blocks)[id - 1];

    if (root->state() == REVEALED)  return QVector<int>({ 0});
    if (root->isMine())             return QVector<int>({-1});

    q.push(root);
    while (!q.empty()) {
        MineBlock* block = q.front();
        int        value = block->reveal();
        m_countdown --;
        if (value == 0) {
            int neighbor_size = sizeof(*block->neighbors()) / sizeof(*block->neighbors())[0];
            for (int i = 0; i < neighbor_size; i ++) {
                if ((*block->neighbors())[i] != nullptr &&
                        !p[(*block->neighbors())[i]->id() - 1] &&
                        (*block->neighbors())[i]->state() == NONE) {
                    q.push((*block->neighbors())[i]);
                    p[(*block->neighbors())[i]->id() - 1] = true;
                }
            }
        }
        p[block->id() - 1] = true;
        q.pop();
    }

    QVector<int> revealedBlockIds(0);
    for (int index = 0; index < p.size(); index ++)
        if (p[index]) revealedBlockIds.append(index + 1);

    return revealedBlockIds;
}

int MineZone::markBlock(int id)
{
    MineBlock*  block = (*m_mine_blocks)[id - 1];
    int         mark  = block->mark();

    m_countdown      += mark;
    m_flag_countdown  += mark;

    return id;
}

void MineZone::drawBlocks()
{
    std::cout << std::endl;
    for (int i = 1; i <= m_difficulty->width; i ++)
        std::cout << " " << i % 10 << " ";
    std::cout << std::endl;
    int i = 1;
    for (MineBlock* block : *m_mine_blocks) {
        block->draw();
        if (block->id() % m_difficulty->width == 0)
            std::cout << " " << i ++ << std::endl;
    }
    std::cout << std::endl;
}

const MineBlock* MineZone::mineBlockAt(int id) const
{
    return (*m_mine_blocks)[id - 1];
}
