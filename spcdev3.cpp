#include "spcdev3.h"
#include "ui_spcdev3.h"

spcDev3::spcDev3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::spcDev3)
{
    ui->setupUi(this);
}

spcDev3::~spcDev3()
{
    delete ui;
}

void spcDev3::on_spc_btn1_clicked()
{
    this->hide();
}
