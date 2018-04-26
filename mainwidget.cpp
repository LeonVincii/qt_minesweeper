#include <iostream>

#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget* parent, Engine* engine) :
    QWidget         (parent),
    ui              (new Ui::MainWidget),
    m_engine        (engine),
    m_gameStarted   (false),
    m_col           (engine->col()),
    m_row           (engine->row()),
    m_mbWidgets     (new MineBlockWidgetArr(m_col*m_row)),
    m_gameStatus    (ACTIVE)
{
    ui->setupUi(this);

    ui->startBtn->setText(QChar(0xf118));

    ui->minezoneLayout->setHorizontalSpacing(0);
    ui->minezoneLayout->setVerticalSpacing(0);

    // Initialise mine block widgets.
    MainWidget::initMineBlockWidgets();

    // Connect signals and slots.
    connect(m_engine, &Engine::timeout,            this, &MainWidget::on_timeout);
    connect(m_engine, &Engine::updateMineZoneView, this, &MainWidget::on_mineZoneWidget_updated);
    connect(m_engine, &Engine::win,                this, &MainWidget::on_win);
    connect(m_engine, &Engine::gameOver,           this, &MainWidget::on_gameOver);
}

MainWidget::~MainWidget()
{
    delete ui;
    delete m_engine;
}

void MainWidget::reveal(QVector<int> ids)
{
    for (int id : ids)
        (*m_mbWidgets)[id - 1]->reveal();
}

void MainWidget::mark(int id)
{
    (*m_mbWidgets)[id - 1]->mark();
}

void MainWidget::initMineBlockWidgets()
{
    for (int row = 0; row < m_row; row ++)
        for (int col = 0; col < m_col; col ++) {
            int id = row*m_col + col + 1;
            if ((*m_mbWidgets)[id - 1] != nullptr) delete (*m_mbWidgets)[id - 1];
            (*m_mbWidgets)[id - 1] = new MineBlockWidget(this, id, m_engine->valueAtId(id));
            if (ui->minezoneLayout->itemAtPosition(row, col) != nullptr)
                delete ui->minezoneLayout->itemAtPosition(row, col);
            ui->minezoneLayout->addWidget((*m_mbWidgets)[id - 1], row, col);
            // Connect mine block widget signals to main widget.
            MainWidget::connect((*m_mbWidgets)[id - 1], &MineBlockWidget::clicked,
                                this,                   &MainWidget::onMineBlockWidgetClicked);
        }
    ui->flagNumberWidget->display(m_engine->numOfMines());
}

void MainWidget::on_startBtn_clicked()
{
    if (m_gameStatus != ACTIVE) m_gameStatus = ACTIVE;

    if (m_gameStarted) {
        m_engine->restartGame();
        ui->timerWidget->display(0);
        MainWidget::initMineBlockWidgets();
    }
    else {
        m_engine->startGame();
        m_gameStarted = true;
    }
}

void MainWidget::on_timeout()
{
    ui->timerWidget->display(m_engine->time());
}

void MainWidget::on_difficulty_changed(int col, int row)
{
    m_col = col;
    m_row = row;

    /*! \todo Need to reinitialise the layout and also handle the signal connections. */
}

void MainWidget::onMineBlockWidgetClicked(int id, Qt::MouseButton btn)
{
    if (m_gameStatus == ACTIVE) {
        if (!m_gameStarted) {
            m_engine->startGame();
            m_gameStarted = true;
        }
        if (btn == Qt::MouseButton::LeftButton)
            m_engine->revealBlock(id);
        else
            m_engine->markBlock(id);
    }
}

void MainWidget::on_mineZoneWidget_updated(Qt::MouseButton btn, QVector<int> ids)
{
    if (ids.first() == 0) return;
    else if (ids.first() == -1) {
        /*! \todo Pop up game over window. */
        return;
    }
    else {
        if (btn == Qt::MouseButton::LeftButton)
            MainWidget::reveal(ids);
        else {
            if (ids.first() != 0) {
                MainWidget::mark(ids.first());
                ui->flagNumberWidget->display(m_engine->flagsLeft());
            }
        }
    }
}

void MainWidget::on_win()
{
    m_gameStatus = FINISHED;

    std::cout << "You win!" << std::endl;
}

void MainWidget::on_gameOver()
{
    m_gameStatus = FINISHED;

    std::cout << "Game over." << std::endl;
}
