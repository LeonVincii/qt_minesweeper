#ifndef MINEBLOCKWIDGET_H
#define MINEBLOCKWIDGET_H

#include <QWidget>

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
    explicit MineBlockWidget(QWidget* parent = 0, int id = 0);
    ~MineBlockWidget();

private:
    /* ****************************************************************************************
     * Attributes
     * ****************************************************************************************/
    Ui::MineBlockWidget* ui;
    int                  m_id;
};

#endif // MINEBLOCKWIDGET_H
