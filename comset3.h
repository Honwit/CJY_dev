#ifndef COMSET3_H
#define COMSET3_H

#include <QWidget>

namespace Ui {
class comSet3;
}

class comSet3 : public QWidget
{
    Q_OBJECT

public:
    explicit comSet3(QWidget *parent = nullptr);
    ~comSet3();

private:

public:
    Ui::comSet3 *ui;
private slots:
    void on_pushButton_clicked();
};

#endif // COMSET3_H
