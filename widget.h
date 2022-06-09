#ifndef WIDGET_H
#define WIDGET_H


#include <QDebug>
#include <QtCharts>

QT_CHARTS_USE_NAMESPACE
#include <QChartView>

#include <QSplineSeries>

#include <QVBoxLayout>
#include <QPushButton>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTreeView>
#include <QTableView>
#include <QHeaderView>
#include <QValueAxis>


#include <QtCharts>
#include <QPainter>
#include <QPainterPath>
#include <QtMath>
#include <QImage>
#include <QPen>

#include <QString>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


#include "comset1.h"
#include "ui_comset1.h"
#include "comset2.h"
#include "ui_comset2.h"
#include "comset3.h"
#include "ui_comset3.h"
#include "spcdev1.h"
#include "ui_spcdev1.h"
#include "spcdev2.h"
#include "ui_spcdev2.h"
#include "spcdev3.h"
#include "ui_spcdev3.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE



class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public:
    QSerialPort *serial1;
    QSerialPort *serial2;
    QSerialPort *serial3;
    QTimer * timer1 = new QTimer(this);
    QTimer * timer2 = new QTimer(this);
    QTimer * timer3 = new QTimer(this);




private slots:
    //窗体调用按钮
    void on_com1_setting_clicked();
    void on_com2_setting_clicked();
    void on_com3_setting_clicked();
    void on_spc_btn1_clicked();
    void on_spc_btn1_2_clicked();
    void on_spc_btn1_3_clicked();
    void on_com1_open_clicked();
    void on_com2_open_clicked();
    void on_com3_open_clicked();

    void ReadData1();
    void ReadData2();
    void ReadData3();

    void updateData1();
    void updateData2();
    void updateData3();

    void createChart();
    void createBar();

    void getData1();
    void getData2();
    void getData3();



private:
    Ui::Widget *ui;

    //创建窗体
    comSet1 *comSetWindow1 = new comSet1;
    comSet2 *comSetWindow2 = new comSet2;
    comSet3 *comSetWindow3 = new comSet3;

    spcDev1 *spcDevWindow1 = new spcDev1;
    spcDev2 *spcDevWindow2 = new spcDev2;
    spcDev3 *spcDevWindow3 = new spcDev3;

    //数据采样点
    float Diameters1[20][5] = {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},
                             {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},
                             {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},
                              {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},};
    float Diameters2[20][5] = {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},
                             {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},
                             {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},
                              {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},};
    float Diameters3[20][5] = {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},
                             {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},
                             {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},
                              {0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},};
    //记录时间
    QDateTime current_date_time1;
    QString current_time_sam1[5];

    QDateTime current_date_time2;
    QString current_time_sam2[5];

    QDateTime current_date_time3;
    QString current_time_sam3[5];

//画控制图需要的变量
    //常数
    const float A2[11]={0,0,1.880,1.023,0.729,0.577,0.483,0.419,0.373,0.337,0.308};
    const float D2[11]={0,0,1.128,1.693,2.059,2.326,2.543,2.704,2.847,2.970,3.078};
    const float D3[11]={0,0,0.000,0.000,0.000,0.000,0.000,0.076,0.136,0.184,0.223};
    const float D4[11]={0,0,3.267,2.571,2.282,2.114,2.004,1.924,1.864,1.816,1.777};

    const float A3[11]={0,0,2.659,1.954,1.628,1.427,1.287,1.182,1.099,1.032,0.975};
    const float C4[11]={0,0,0.7979,0.8862,0.9213,0.9400,0.9515,0.9594,0.9650,0.9693,0.9727};
    const float B3[11]={0,0,0,0,0,0,0.030,0.118,0.185,0.239,0.284};
    const float B4[11]={0,0,3.276,2.568,2.266,2.089,1.970,1.882,1.815,1.761,1.716};
//SPC变量 机器1
    //常量
    const int subNum1 = 5;
    const int totalNum1 = 20;
    float target1 = 0.00;
    float USLx1 = 9.00;
    float LSLx1 = 9.00;

    float USLr1 = 9.00;
    float LSLr1 = 9.00;

    //计算值
    float sub_avg1[20];//子组均值
    float sub_r1[20];//子组极差
    float X_bar1=0.00;//总体均值
    float total_r1=0.00;//极差和
    float R_bar1=0.00;//平均极差

    float sigma1 = 0.00;//组内标准差
    float S1 = 0.00;//整体标准差

    float standDevIn1 = 0.00;
    float standDevOut1 = 0.00;
    float standDevInOut1 = 0.00;
    float standDevTotal1 = 0.00;
    float standDevPos31 = 0.00;
    float standDevNeg31= 0.00;
    //工序能力（组内）
    float Cpk1 = 0.00;
    float Cp1 = 0.00;
    float CpL1 = 0.00;
    float CpU1 = 0.00;
    float CpM1 = 0.00;
    //工序能力（组外）
    float Ppk1 = 0.00;
    float Pp1 = 0.00;
    float PpL1 = 0.00;
    float PpU1 = 0.00;
    float PpM1 = 0.00;
    //其他值
    float Ca1 = 0.00;
    //实测性能
    float PPM1 = 0.00;
//SPC变量 机器2
    //常量
    const int subNum2 = 5;
    const int totalNum2 = 20;
    float target2 = 0.00;
    float USLx2 = 9.00;
    float LSLx2 = 9.00;

    float USLr2 = 9.00;
    float LSLr2 = 9.00;

    //计算值
    float sub_avg2[20];//子组均值
    float sub_r2[20];//子组极差
    float X_bar2=0.00;//总体均值
    float total_r2=0.00;//极差和
    float R_bar2=0.00;//平均极差

    float sigma2 = 0.00;//组内标准差
    float S2 = 0.00;//整体标准差
    float standDevIn2 = 0.00;
    float standDevOut2 = 0.00;
    float standDevInOut2 = 0.00;
    float standDevTotal2 = 0.00;
    float standDevPos32 = 0.00;
    float standDevNeg32 = 0.00;
    //工序能力（组内）
    float Cpk2 = 0.00;
    float Cp2 = 0.00;
    float CpL2 = 0.00;
    float CpU2 = 0.00;
    float CpM2 = 0.00;
    //工序能力（组外）
    float Ppk2 = 0.00;
    float Pp2 = 0.00;
    float PpL2 = 0.00;
    float PpU2 = 0.00;
    float PpM2 = 0.00;
    //其他值
    float Ca2 = 0.00;
    //实测性能
    float PPM2 = 0.00;
//SPC变量 机器3
    //常量
    const int subNum3 = 5;
    const int totalNum3 = 20;
    float target3 = 0.00;
    float USLx3 = 9.00;
    float LSLx3 = 9.00;

    float USLr3 = 9.00;
    float LSLr3 = 9.00;

    //计算值
    float sub_avg3[20];//子组均值
    float sub_r3[20];//子组极差
    float X_bar3=0.00;//总体均值
    float total_r3=0.00;//极差和
    float R_bar3=0.00;//平均极差

    float sigma3 = 0.00;//组内标准差
    float S3 = 0.00;//整体标准差
    float standDevIn3 = 0.00;
    float standDevOut3 = 0.00;
    float standDevInOut3 = 0.00;
    float standDevTotal3 = 0.00;
    float standDevPos33 = 0.00;
    float standDevNeg33 = 0.00;
    //工序能力（组内）
    float Cpk3 = 0.00;
    float Cp3 = 0.00;
    float CpL3 = 0.00;
    float CpU3 = 0.00;
    float CpM3 = 0.00;
    //工序能力（组外）
    float Ppk3 = 0.00;
    float Pp3 = 0.00;
    float PpL3 = 0.00;
    float PpU3 = 0.00;
    float PpM3 = 0.00;
    //其他值
    float Ca3 = 0.00;
    //实测性能
    float PPM3 = 0.00;



};
#endif // WIDGET_H
