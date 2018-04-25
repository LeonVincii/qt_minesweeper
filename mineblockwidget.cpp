#include "mineblockwidget.h"
#include "ui_mineblockwidget.h"

MineBlockWidget::MineBlockWidget(QWidget* parent, int id, int value) :
    QWidget (parent),
    ui      (new Ui::MineBlockWidget),
    m_id    (id),
    m_value (value),
    m_marked(false)
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
    ui->mbFrame->setFrameShadow     (QFrame::Shadow::Plain);
    ui->mbFrame->setLineWidth       (1);
    ui->mbFrame->setMidLineWidth    (1);
    ui->mbValueWidget->setText      (m_value);
    ui->mbValueWidget->setVisible   (true);
}

void MineBlockWidget::mark()
{
    if (!m_marked) {
        m_marked = true;
        ui->mbValueWidget->setText      (QChar(0xf024));
        ui->mbValueWidget->setVisible   (true);
    }
    else {
        m_marked = false;
        ui->mbValueWidget->setVisible   (false);
        ui->mbValueWidget->setText      (m_value);
    }
}

void MineBlockWidget::mousePressEvent(QMouseEvent* event)
{
    emit MineBlockWidget::clicked(m_id, event->button());
}
