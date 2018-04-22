#include <iostream>

#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget* parent) :
    QWidget         (parent),
    ui              (new Ui::MainWidget),
    m_engine        (NULL)
{
    ui->setupUi(this);
}

MainWidget::~MainWidget()
{
    delete ui;
    delete m_engine;
}

void MainWidget::setEngine(Engine* engine)
{
    m_engine = engine;

    // Connect signals and slots
    connect(m_engine, &Engine::timeout, this, &MainWidget::on_timeout);
}

void MainWidget::on_startBtn_clicked()
{
    m_engine->startGame();
}

void MainWidget::on_timeout()
{
    ui->timeDisplay->display(m_engine->time());
}
