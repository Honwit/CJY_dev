#ifndef COMSET1_H
#define COMSET1_H

#include <QWidget>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>



namespace Ui {
class comSet1;
}

class comSet1 : public QWidget
{
    Q_OBJECT

public:
    explicit comSet1(QWidget *parent = nullptr);
    Ui::comSet1 *ui;

    ~comSet1();

private slots:

    void on_pushButton_2_clicked();

private:

};

#endif // COMSET1_H
