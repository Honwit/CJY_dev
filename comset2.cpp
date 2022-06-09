#include "comset2.h"
#include "ui_comset2.h"

comSet2::comSet2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::comSet2)
{
    ui->setupUi(this);
}

comSet2::~comSet2()
{
    delete ui;
}

void comSet2::on_pushButton_2_clicked()
{
    this->hide();
}
