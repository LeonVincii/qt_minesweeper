#ifndef MINEBLOCKWIDGET_H
#define MINEBLOCKWIDGET_H

#include <QWidget>
#include <QMouseEvent>

#include "engine.h"

namespace Ui {
class MineBlockWidget;
}

class MineBlockWidget : public QWidget
{
    Q_OBJECT

public:
    /* ****************************************************************************************
     * Constructor & Destructor
     * ****************************************************************************************/
    explicit MineBlockWidget(QWidget* parent = 0, int id = 0, int value = 0);
    ~MineBlockWidget();

    /* ****************************************************************************************
     * Public Functions
     * ****************************************************************************************/
    void reveal();
    void mark  ();

protected:
    void mousePressEvent(QMouseEvent* event);

private:
    /* ****************************************************************************************
     * Attributes
     * ****************************************************************************************/
    Ui::MineBlockWidget* ui;
    int                  m_id;
    int                  m_value;
    bool                 m_marked;

signals:
    void clicked(int id, Qt::MouseButton btn);
};

#endif // MINEBLOCKWIDGET_H
