#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QGridLayout>

#include "engine.h"

class Engine;
struct Difficulty;

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
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

    /* ****************************************************************************************
     * Accessors & Mutators
     * ****************************************************************************************/
    void setEngine(Engine* engine);

private:
    /* ****************************************************************************************
     * Member Functions
     * ****************************************************************************************/
    ;

    /* ****************************************************************************************
     * Attributes
     * ****************************************************************************************/
    Ui::MainWidget*       ui;
    const Engine*         m_engine;
    const Difficulty*     m_difficulty;
    const QHBoxLayout*    m_controlPannel;
    const QGridLayout*    m_minePanel;

private slots:
    void on_difficulty_changed();
};

#endif // MAINWIDGET_H
