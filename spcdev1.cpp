#include "spcdev1.h"
#include "ui_spcdev1.h"

spcDev1::spcDev1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::spcDev1)
{
    ui->setupUi(this);
}

spcDev1::~spcDev1()
{
    delete ui;
}

void spcDev1::on_spc_btn1_clicked()
{
    this->hide();
}
