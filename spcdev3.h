#ifndef SPCDEV3_H
#define SPCDEV3_H

#include <QWidget>

namespace Ui {
class spcDev3;
}

class spcDev3 : public QWidget
{
    Q_OBJECT

public:
    explicit spcDev3(QWidget *parent = nullptr);
    ~spcDev3();

private:

public:
    Ui::spcDev3 *ui;
private slots:
    void on_spc_btn1_clicked();
};

#endif // SPCDEV3_H
