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
     * Accessor & Mutator
     * ****************************************************************************************/
    int value() const { return m_value; }

    /* ****************************************************************************************
     * Public Functions
     * ****************************************************************************************/
    void reveal();
    void mark  ();
    void reset ();

protected:
    void mousePressEvent(QMouseEvent* event);

private:
    /* ****************************************************************************************
     * Attributes
     * ****************************************************************************************/
    Ui::MineBlockWidget* ui;
    int                  m_id;
    int                  m_value;
    BlockState           m_state;

    /* ****************************************************************************************
     * Member Functions
     * ****************************************************************************************/
    QString colorFigure();

signals:
    void clicked(int id, Qt::MouseButton btn);
};

#endif // MINEBLOCKWIDGET_H
