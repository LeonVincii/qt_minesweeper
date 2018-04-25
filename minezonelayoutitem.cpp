#include "minezonelayoutitem.h"

MineZoneLayoutItem::MineZoneLayoutItem(QLayoutItem *parent, MineBlockWidget* mbWidget) :
    QLayoutItem (parent),
    m_mbWidget  (mbWidget)
{}
