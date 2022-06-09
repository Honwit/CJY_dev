#ifndef SPCDEV2_H
#define SPCDEV2_H

#include <QWidget>

namespace Ui {
class spcDev2;
}

class spcDev2 : public QWidget
{
    Q_OBJECT

public:
    explicit spcDev2(QWidget *parent = nullptr);
    ~spcDev2();

private:

public:
    Ui::spcDev2 *ui;
private slots:
    void on_spc_btn1_clicked();
};

#endif // SPCDEV2_H
