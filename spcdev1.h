#ifndef SPCDEV1_H
#define SPCDEV1_H

#include <QWidget>


namespace Ui {
class spcDev1;
}

class spcDev1 : public QWidget
{
    Q_OBJECT

public:
    explicit spcDev1(QWidget *parent = nullptr);
    ~spcDev1();

private:


public:
    Ui::spcDev1 *ui;
private slots:
    void on_spc_btn1_clicked();
};

#endif // SPCDEV1_H
