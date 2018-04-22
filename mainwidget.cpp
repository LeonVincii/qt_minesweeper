#include <iostream>

#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget* parent) :
    QWidget         (parent),
    ui              (new Ui::MainWidget),
    m_engine        (NULL),
    m_difficulty    (&EASY),
    m_controlPannel (new QHBoxLayout),
    m_minePanel     (new QGridLayout)
{
    ui->setupUi(this);

    // Connect signals and slots
    MainWidget::connect(m_engine,   Engine::difficulty_changed,
                        this,       MainWidget::on_difficulty_changed);
}

MainWidget::~MainWidget()
{
    delete ui;
    delete m_controlPannel;
    delete m_minePanel;
}

void MainWidget::setEngine(Engine* engine)
{
    m_engine = engine;
}

void MainWidget::on_difficulty_changed()
{
    std::cout << "MainWidget >> Difficulty changed to "
              << m_difficulty->difficulty << ".\n";
}
