#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QVector>

#include "engine.h"
#include "mineblockwidget.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{   
    Q_OBJECT

public:
    /* ****************************************************************************************
     * Constructor & Destructor
     * ****************************************************************************************/
    explicit MainWidget(QWidget* parent = 0, Engine* engine = NULL);
    ~MainWidget();

protected:
    void resizeEvent(QResizeEvent* event);

private:
    /* ****************************************************************************************
     * Member Functions
     * ****************************************************************************************/
    void reveal();

    /* ****************************************************************************************
     * Attributes
     * ****************************************************************************************/
    Ui::MainWidget*       ui;
    Engine*               m_engine;
    bool                  m_game_started;
    int                   m_col;
    int                   m_row;

private slots:
    void on_startBtn_clicked();
    void on_timeout();
};

#endif // MAINWIDGET_H
