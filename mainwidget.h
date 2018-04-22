#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QGridLayout>

#include "engine.h"

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
    explicit MainWidget(QWidget* parent = 0);
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
    Engine*               m_engine;

private slots:
    void on_startBtn_clicked();
    void on_timeout();

};

#endif // MAINWIDGET_H
