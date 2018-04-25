#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <iostream>

MainWidget::MainWidget(QWidget* parent, Engine* engine) :
    QWidget         (parent),
    ui              (new Ui::MainWidget),
    m_engine        (engine),
    m_game_started  (false),
    m_col           (engine->col()),
    m_row           (engine->row())
{
    ui->setupUi(this);

    ui->startBtn->setText(QChar(0xf118));

    ui->minezoneLayout->setHorizontalSpacing(0);
    ui->minezoneLayout->setVerticalSpacing(0);

    // Initialise mine block widgets.
    for (int row = 0; row < m_row; row ++)
        for (int col = 0; col < m_col; col ++) {
            MineBlockWidget* mbWidget = new MineBlockWidget(NULL, row*m_col + col+1);
            ui->minezoneLayout->addWidget(mbWidget, row, col);
            MainWidget::connect(mbWidget, &MineBlockWidget::clicked,
                                this,     &MainWidget::on_mineBlockWidget_clicked);
        }

    // Connect signals and slots.
    connect(m_engine, &Engine::timeout, this, &MainWidget::on_timeout);
}

MainWidget::~MainWidget()
{
    delete ui;
    delete m_engine;
}

void MainWidget::reveal()
{

}

void MainWidget::on_startBtn_clicked()
{
    if (m_game_started) {
        m_engine->restartGame();
        ui->timerWidget->display(0);
    }
    else {
        m_engine->startGame();
        m_game_started = true;
    }
}

void MainWidget::on_timeout()
{
    ui->timerWidget->display(m_engine->time());
}

void MainWidget::on_mineBlockWidget_clicked(int id, Qt::MouseButton btn)
{
    if (m_game_started)
        std::cout << btn << " " << id << std::endl;
    else
        std::cout << "Game hasn't started yet!" << std::endl;
}
