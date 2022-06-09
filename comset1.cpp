#include "comset1.h"
#include "ui_comset1.h"
#include <QString>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

comSet1::comSet1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::comSet1)
{
    ui->setupUi(this);
    // 添加链接的串口编号
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->PortBox1->addItem(serial.portName());
            serial.close();
        }
    }


}

comSet1::~comSet1()
{
    delete ui;
}
void comSet1::on_pushButton_2_clicked()
{
    this->hide();
}
