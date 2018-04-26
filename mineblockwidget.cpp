#include "mineblockwidget.h"
#include "ui_mineblockwidget.h"

MineBlockWidget::MineBlockWidget(QWidget* parent, int id, int value) :
    QWidget (parent),
    ui      (new Ui::MineBlockWidget),
    m_id    (id),
    m_value (value),
    m_state (NONE)
{
    ui->setupUi(this);
    ui->mbValueWidget->setVisible(false);
    ui->mbFrame->setFrameShadow(QFrame::Shadow::Raised);
}

MineBlockWidget::~MineBlockWidget()
{
    delete ui;
}

void MineBlockWidget::reveal()
{
    if (m_state == NONE) {
        m_state = REVEALED;
        ui->mbFrame->setFrameStyle  (QFrame::Box);
        ui->mbFrame->setFrameShadow (QFrame::Shadow::Sunken);
        ui->mbFrame->setLineWidth   (1);
        ui->mbFrame->setMidLineWidth(0);
        ui->mbFrame->setStyleSheet  ("background: #e2e2e2");
        if (m_value != 0) {
            ui->mbValueWidget->setText      (QString::number(m_value));
            ui->mbValueWidget->setVisible   (true);
        }
    }
}

void MineBlockWidget::mark()
{
    if (m_state == NONE) {
        m_state = MARKED;
        ui->mbValueWidget->setText      (QChar(0xf024));
        ui->mbValueWidget->setStyleSheet("color: #bf0707;");
        ui->mbValueWidget->setVisible   (true);
    }
    else if (m_state == MARKED){
        m_state = NONE;
        ui->mbValueWidget->setVisible   (false);
        ui->mbValueWidget->setStyleSheet("");
        ui->mbValueWidget->setText      (QString::number(m_value));
    }
}

void MineBlockWidget::reset()
{
    ui->mbValueWidget->setVisible(false);
    ui->mbFrame->setFrameShadow (QFrame::Shadow::Raised);
    ui->mbFrame->setLineWidth   (2);
    ui->mbFrame->setMidLineWidth(2);
    ui->mbFrame->setStyleSheet  ("");
    m_state = NONE;
}

void MineBlockWidget::mousePressEvent(QMouseEvent* event)
{
    emit MineBlockWidget::clicked(m_id, event->button());
}
