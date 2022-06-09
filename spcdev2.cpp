#include "spcdev2.h"
#include "ui_spcdev2.h"

spcDev2::spcDev2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::spcDev2)
{
    ui->setupUi(this);
}

spcDev2::~spcDev2()
{
    delete ui;
}

void spcDev2::on_spc_btn1_clicked()
{
    this->hide();
}
