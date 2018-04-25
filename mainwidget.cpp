#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "minezonelayoutitem.h"

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
    MainWidget::initMineBlockWidgets();

    // Connect signals and slots.
    connect(m_engine, &Engine::timeout,            this, &MainWidget::on_timeout);
    connect(m_engine, &Engine::updateMineZoneView, this, &MainWidget::on_mineZoneWidget_updated);
}

MainWidget::~MainWidget()
{
    delete ui;
    delete m_engine;
}

void MainWidget::reveal(QVector<int> ids)
{
    MineZoneLayoutItem* mbWidgetItem;
    for (int id : ids) {
        mbWidgetItem = ui->minezoneLayout->itemAt(id - 1);
        mbWidgetItem->getMBWidget()->reveal();
    }
}

void MainWidget::mark(int id)
{
    MineZoneLayoutItem* mbWidgetItem = ui->minezoneLayout->itemAt(id - 1);
    mbWidgetItem->getMBWidget()->mark();
}

void MainWidget::initMineBlockWidgets()
{
    for (int row = 0; row < m_row; row ++)
        for (int col = 0; col < m_col; col ++) {
            MineBlockWidget* mbWidget = new MineBlockWidget(this, row*m_col + col+1);
            MineZoneLayoutItem* mbWidgetItem = new MineZoneLayoutItem(NULL, mbWidget);
            ui->minezoneLayout->addItem(mbWidgetItem, row, col);
            // Connect mine block widget signals to main widget.
            MainWidget::connect(mbWidget, &MineBlockWidget::clicked,
                                this,     &MainWidget::on_mineBlockWidget_clicked);
        }
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

void MainWidget::on_difficulty_changed(int col, int row)
{
    m_col = col;
    m_row = row;

    /*! \todo Need to reinitialise the layout and also handle the signal connections. */
}

void MainWidget::on_mineBlockWidget_clicked(int id, Qt::MouseButton btn)
{
    if (m_game_started) {
        if (btn == Qt::MouseButton::LeftButton)
            m_engine->revealBlock(id);
        else
            m_engine->markBlock(id);
    }
    else
        std::cout << "Game hasn't started yet!" << std::endl;
}

void MainWidget::on_mineZoneWidget_updated(Qt::MouseButton btn, QVector<int> ids)
{
    if (ids.first() == 0) return;
    else if (ids.first() == -1) return; /*! \todo Pop up game over window. */
    else {
        if (btn == Qt::MouseButton::LeftButton)
            MainWidget::reveal(ids);
        else MainWidget::mark(ids.first());
    }
}
