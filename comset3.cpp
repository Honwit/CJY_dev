#include "comset3.h"
#include "ui_comset3.h"

comSet3::comSet3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::comSet3)
{
    ui->setupUi(this);
}

comSet3::~comSet3()
{
    delete ui;
}

void comSet3::on_pushButton_clicked()
{
    this->hide();
}
