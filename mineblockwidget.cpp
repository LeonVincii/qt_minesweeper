#include "mineblockwidget.h"
#include "ui_mineblockwidget.h"

MineBlockWidget::MineBlockWidget(QWidget* parent, int id) :
    QWidget (parent),
    ui      (new Ui::MineBlockWidget),
    m_id    (id)
{
    ui->setupUi(this);
    ui->mbValueWidget->setVisible(false);
    ui->mbFrame->setFrameShadow(QFrame::Shadow::Raised);
}

MineBlockWidget::~MineBlockWidget()
{
    delete ui;
}
