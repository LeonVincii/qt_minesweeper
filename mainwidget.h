#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QVector>

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

private:
    /* ****************************************************************************************
     * Attributes
     * ****************************************************************************************/
    Ui::MainWidget*       ui;
    Engine*               m_engine;
    bool                  m_game_started;
    int                   m_col;
    int                   m_row;

    /* ****************************************************************************************
     * Member Functions
     * ****************************************************************************************/
    void reveal(QVector<int> ids);
    void mark  (int id);
    void initMineBlockWidgets();

private slots:
    void on_startBtn_clicked();
    void on_timeout();

public slots:
    void on_difficulty_changed(int col, int row);
    void onMineBlockWidgetClicked(int id, Qt::MouseButton btn);
    void on_mineZoneWidget_updated(Qt::MouseButton btn, QVector<int> ids);
};

#endif // MAINWIDGET_H
