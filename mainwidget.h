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

    typedef QVector<MineBlockWidget*> MineBlockWidgetArr;

    enum GameStatus { ACTIVE, FINISHED };

public:
    /* ****************************************************************************************
     * Constructor & Destructor
     * ****************************************************************************************/
    explicit MainWidget(QWidget* parent = 0, Engine* engine = nullptr);
    ~MainWidget();

private:
    /* ****************************************************************************************
     * Attributes
     * ****************************************************************************************/
    Ui::MainWidget*       ui;
    Engine*               m_engine;
    bool                  m_gameStarted;
    int                   m_col;
    int                   m_row;
    MineBlockWidgetArr*   m_mbWidgets;
    GameStatus            m_gameStatus;

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
    void on_win(Qt::MouseButton btn, QVector<int> ids);
    void on_gameOver();
};

#endif // MAINWIDGET_H
