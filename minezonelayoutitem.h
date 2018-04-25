#ifndef MINEZONELAYOUTITEM_H
#define MINEZONELAYOUTITEM_H

#include <QLayoutItem>

#include <mineblockwidget.h>

class MineZoneLayoutItem : public QLayoutItem
{
    Q_OBJECT
public:
    /* ****************************************************************************************
     * Constructor & Destructor
     * ****************************************************************************************/
    explicit MineZoneLayoutItem(QLayoutItem*     parent   = nullptr,
                                MineBlockWidget* mbWidget = nullptr);
    ~MineZoneLayoutItem();

    /* ****************************************************************************************
     * Public Functions
     * ****************************************************************************************/
    MineBlockWidget* getMBWidget()    const   { return m_mbWidget; }

private:
    /* ****************************************************************************************
     * Attributes
     * ****************************************************************************************/
    MineBlockWidget*  m_mbWidget;

signals:

public slots:
};

#endif // MINEZONELAYOUTITEM_H
