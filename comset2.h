#ifndef COMSET2_H
#define COMSET2_H

#include <QWidget>

namespace Ui {
class comSet2;
}

class comSet2 : public QWidget
{
    Q_OBJECT

public:
    explicit comSet2(QWidget *parent = nullptr);
    ~comSet2();

private:


public:
    Ui::comSet2 *ui;
private slots:
    void on_pushButton_2_clicked();
};

#endif // COMSET2_H
