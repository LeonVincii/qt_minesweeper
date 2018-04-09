#include "minezone.h"

MineZone::MineZone(QObject *parent, int dimension) :
    QObject(parent),
    m_dimension(dimension),
    m_mine_blocks(new MineBlockArr(dimension*dimension))
{}
