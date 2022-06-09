#include "widget.h"
#include "ui_widget.h"

#include <QString>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //文件初始化
    // 我们都放D：//测径仪数据  文件夹里面吧
    QString strDir1 = QString("%1/%2").arg("D://测径仪数据").arg("机器1");
    QString strDir2 = QString("%1/%2").arg("D://测径仪数据").arg("机器2");
    QString strDir3 = QString("%1/%2").arg("D://测径仪数据").arg("机器3");
    // 先检查有没有文件夹存在，没有就让程序创建文件夹先
    QDir dirCSV;
    if (!dirCSV.exists(strDir1))
        dirCSV.mkpath(strDir1);
    if (!dirCSV.exists(strDir2))
        dirCSV.mkpath(strDir2);
    if (!dirCSV.exists(strDir3))
        dirCSV.mkpath(strDir3);


    createChart();//创建控制图
    createBar();//创建直方图

    connect(timer1,&QTimer::timeout,[=](){
        getData1();
    });
    connect(timer2,&QTimer::timeout,[=](){
        getData2();
    });
    connect(timer3,&QTimer::timeout,[=](){
        getData3();
    });
}
void Widget::on_com1_setting_clicked()
{
    comSetWindow1->show();

}

void Widget::on_com2_setting_clicked()
{
    comSetWindow2->show();
}

void Widget::on_com3_setting_clicked()
{
    comSetWindow3->show();
}

void Widget::on_spc_btn1_clicked()
{
    spcDevWindow1->show();
}

void Widget::on_spc_btn1_2_clicked()
{
    spcDevWindow2->show();
}

void Widget::on_spc_btn1_3_clicked()
{
    spcDevWindow3->show();
}


Widget::~Widget()
{
    delete ui;
}

//打开串口1
void Widget::on_com1_open_clicked()
{
    if(ui->com1_open->text() == tr("打开串口"))
    {
        serial1 = new QSerialPort;
        //设置串口名
        serial1->setPortName(comSetWindow1->ui->PortBox1->currentText());
        //打开串口
        serial1->open(QIODevice::ReadWrite);
        //设置波特率
        if(comSetWindow1->ui->PortBox2->currentText() == "9600")
            serial1->setBaudRate(QSerialPort::Baud9600);//设置波特率为9600
        else if(comSetWindow1->ui->PortBox2->currentText() == "115200")
            serial1->setBaudRate(QSerialPort::Baud115200);//设置波特率为115200
        //设置数据位数

        serial1->setDataBits(QSerialPort::Data8);//设置数据位8

        //设置校验位

        serial1->setParity(QSerialPort::NoParity);

        //设置停止位

        serial1->setStopBits(QSerialPort::OneStop);//停止位设置为1

        //设置流控制
        serial1->setFlowControl(QSerialPort::NoFlowControl);//设置为无流控制
        //关闭设置菜单使能
        ui->com1_setting->setEnabled(false);
        ui->com1_open->setText(tr("关闭串口"));

        //连接信号槽
        QObject::connect(serial1,&QSerialPort::readyRead,this,&Widget::ReadData1);//接收到数据之后调用数据读取
        timer1->start(comSetWindow1->ui->PortBox6->currentText().toInt());

    }
    else
    {
        //关闭串口
        timer1->stop();


        serial1->clear();
        serial1->close();
        serial1->deleteLater();

        //恢复设置使能
        ui->com1_setting->setEnabled(true);
        ui->com1_open->setText(tr("打开串口"));

    }
}


//打开串口2
void Widget::on_com2_open_clicked()
{
    if(ui->com2_open->text() == tr("打开串口"))
    {
        serial2 = new QSerialPort;
        //设置串口名
        serial2->setPortName(comSetWindow2->ui->PortBox1->currentText());
        //打开串口
        serial2->open(QIODevice::ReadWrite);
        //设置波特率
        if(comSetWindow2->ui->PortBox2->currentText() == "9600")
            serial2->setBaudRate(QSerialPort::Baud9600);//设置波特率为9600
        else if(comSetWindow2->ui->PortBox2->currentText() == "115200")
            serial2->setBaudRate(QSerialPort::Baud115200);//设置波特率为115200
        //设置数据位数

        serial2->setDataBits(QSerialPort::Data8);//设置数据位8

        //设置校验位

        serial2->setParity(QSerialPort::NoParity);

        //设置停止位

        serial2->setStopBits(QSerialPort::OneStop);//停止位设置为1

        //设置流控制
        serial2->setFlowControl(QSerialPort::NoFlowControl);//设置为无流控制
        //关闭设置菜单使能
        ui->com2_setting->setEnabled(false);
        ui->com2_open->setText(tr("关闭串口"));

        //连接信号槽
        QObject::connect(serial2,&QSerialPort::readyRead,this,&Widget::ReadData2);

        timer2->start(comSetWindow2->ui->PortBox6->currentText().toInt());

    }
    else
    {
        //关闭串口
        timer2->stop();


        serial2->clear();
        serial2->close();
        serial2->deleteLater();

        //恢复设置使能
        ui->com2_setting->setEnabled(true);
        ui->com2_open->setText(tr("打开串口"));
    }
}

//打开串口3
void Widget::on_com3_open_clicked()
{
    if(ui->com3_open->text() == tr("打开串口"))
    {
        serial3 = new QSerialPort;
        //设置串口名
        serial3->setPortName(comSetWindow3->ui->PortBox1->currentText());
        //打开串口
        serial3->open(QIODevice::ReadWrite);
        //设置波特率
        if(comSetWindow3->ui->PortBox2->currentText() == "9600")
            serial3->setBaudRate(QSerialPort::Baud9600);//设置波特率为9600
        else if(comSetWindow3->ui->PortBox2->currentText() == "115200")
            serial3->setBaudRate(QSerialPort::Baud115200);//设置波特率为115200
        //设置数据位数

        serial3->setDataBits(QSerialPort::Data8);//设置数据位8

        //设置校验位

        serial3->setParity(QSerialPort::NoParity);

        //设置停止位

        serial3->setStopBits(QSerialPort::OneStop);//停止位设置为1

        //设置流控制
        serial3->setFlowControl(QSerialPort::NoFlowControl);//设置为无流控制
        //关闭设置菜单使能
        ui->com3_setting->setEnabled(false);
        ui->com3_open->setText(tr("关闭串口"));

        //连接信号槽
        QObject::connect(serial3,&QSerialPort::readyRead,this,&Widget::ReadData3);
        timer3->start(comSetWindow3->ui->PortBox6->currentText().toInt());
    }
    else
    {
        //关闭串口
        timer3->stop();


        serial3->clear();
        serial3->close();
        serial3->deleteLater();

        //恢复设置使能
        ui->com3_setting->setEnabled(true);
        ui->com3_open->setText(tr("打开串口"));
    }
}

//串口读取数据
void Widget::getData1()
{
    QByteArray btr;
    btr.append(0x01);
    btr.append(0x03);
    btr.append(0x01);

    serial1->write(btr);
}
void Widget::getData2()
{
    QByteArray btr;
    btr.append(0x01);
    btr.append(0x41);
    serial2->write(btr);
}
void Widget::getData3()
{
    QByteArray btr;
    btr.append(0x01);
    btr.append(0x41);
    serial3->write(btr);
}

bool updata_flag1 = false;
void Widget::ReadData1()
{
    static int i=0,j=0;
    QByteArray buf;
    buf = serial1->readAll();
    float tem_diameter[5]={0,0,0,0,0};
    if(!buf.isEmpty())
    {
        if(buf.at(0)==0x01 && buf.at(1)==0x41)
        {
            int diameter = buf.at(2)*16*16+buf.at(3)*16+buf.at(4);
            tem_diameter[j] = diameter / 1000.0;

            current_date_time1 = QDateTime::currentDateTime();
            current_time_sam1[j] = current_date_time1.toString("yyyy-MM-dd hh:mm:ss");//记录子组时间
            j++;
            i++;
            if(j==5)
            {
                //轮换赋值
                for(int k=1;k<20;k++)
                {
                    Diameters1[k-1][0]=Diameters1[k][0];
                    Diameters1[k-1][1]=Diameters1[k][1];
                    Diameters1[k-1][2]=Diameters1[k][2];
                    Diameters1[k-1][3]=Diameters1[k][3];
                    Diameters1[k-1][4]=Diameters1[k][4];
                }
                //最后子组赋新值
                Diameters1[19][0]=tem_diameter[0];
                Diameters1[19][1]=tem_diameter[1];
                Diameters1[19][2]=tem_diameter[2];
                Diameters1[19][3]=tem_diameter[3];
                Diameters1[19][4]=tem_diameter[4];

                j=0;
                if(i>=100)
                {
                    updata_flag1 = true;
                    i=100;
                }
                if(updata_flag1)
                    updateData1();

            }


        }
    }
    buf.clear();
}
bool updata_flag2 = false;
void Widget::ReadData2()
{
    static int i=0,j=0;
    QByteArray buf;
    buf = serial2->readAll();
    float tem_diameter[5]={0,0,0,0,0};
    if(!buf.isEmpty())
    {
        if(buf.at(0)==0x01 && buf.at(1)==0x41)
        {
            int diameter = buf.at(2)*16*16+buf.at(3)*16+buf.at(4);
            tem_diameter[j] = diameter / 1000.0;

            current_date_time2 = QDateTime::currentDateTime();
            current_time_sam2[j] = current_date_time2.toString("yyyy-MM-dd hh:mm:ss");//记录子组时间
            j++;
            i++;
            if(j==5)
            {
                //轮换赋值
                for(int k=1;k<20;k++)
                {
                    Diameters2[k-1][0]=Diameters2[k][0];
                    Diameters2[k-1][1]=Diameters2[k][1];
                    Diameters2[k-1][2]=Diameters2[k][2];
                    Diameters2[k-1][3]=Diameters2[k][3];
                    Diameters2[k-1][4]=Diameters2[k][4];
                }
                //最后子组赋新值
                Diameters2[19][0]=tem_diameter[0];
                Diameters2[19][1]=tem_diameter[1];
                Diameters2[19][2]=tem_diameter[2];
                Diameters2[19][3]=tem_diameter[3];
                Diameters2[19][4]=tem_diameter[4];

                j=0;
                if(i>=100)
                {
                    updata_flag2 = true;
                    i=100;
                }
                if(updata_flag2)
                    updateData2();
            }

        }
    }
    buf.clear();
}
bool updata_flag3 = false;
void Widget::ReadData3()
{
    static int i=0,j=0;
    QByteArray buf;
    buf = serial3->readAll();
    float tem_diameter[5]={0,0,0,0,0};
    if(!buf.isEmpty())
    {
        if(buf.at(0)==0x01 && buf.at(1)==0x41)
        {
            int diameter = buf.at(2)*16*16+buf.at(3)*16+buf.at(4);
            tem_diameter[j] = diameter / 1000.0;

            current_date_time3 = QDateTime::currentDateTime();
            current_time_sam3[j] = current_date_time3.toString("yyyy-MM-dd hh:mm:ss");//记录子组时间
            j++;
            i++;
            if(j==5)
            {
                //轮换赋值
                for(int k=1;k<20;k++)
                {
                    Diameters3[k-1][0]=Diameters3[k][0];
                    Diameters3[k-1][1]=Diameters3[k][1];
                    Diameters3[k-1][2]=Diameters3[k][2];
                    Diameters3[k-1][3]=Diameters3[k][3];
                    Diameters3[k-1][4]=Diameters3[k][4];
                }
                //最后子组赋新值
                Diameters3[19][0]=tem_diameter[0];
                Diameters3[19][1]=tem_diameter[1];
                Diameters3[19][2]=tem_diameter[2];
                Diameters3[19][3]=tem_diameter[3];
                Diameters3[19][4]=tem_diameter[4];

                j=0;
                if(i>=100)
                {
                    updata_flag3 = true;
                    i=100;
                }
                if(updata_flag3)
                    updateData3();
            }

        }
    }
    buf.clear();
}


//一个子组5个数据  20子组为一大组，计算cpk， 1s更新一个数据，5s更新一次图，5s写入一次表格，一次写入5行数据，也就是滚动式计算
void Widget::updateData1()
{

    QLineSeries *seriesUSL1 = (QLineSeries *)ui->chartView1->chart()->series().at(0);
    QLineSeries *seriesLSL1 = (QLineSeries *)ui->chartView1->chart()->series().at(1);
    QLineSeries *seriesSetData1 = (QLineSeries *)ui->chartView1->chart()->series().at(2);
    QLineSeries *seriesRealData1 = (QLineSeries *)ui->chartView1->chart()->series().at(3);

    QLineSeries *seriesUSLS1 = (QLineSeries *)spcDevWindow1->ui->chartViewX->chart()->series().at(0);
    QLineSeries *seriesLSLS1 = (QLineSeries *)spcDevWindow1->ui->chartViewX->chart()->series().at(1);
    QLineSeries *seriesSetDataS1 = (QLineSeries *)spcDevWindow1->ui->chartViewX->chart()->series().at(2);
    QLineSeries *seriesRealDataS1 = (QLineSeries *)spcDevWindow1->ui->chartViewX->chart()->series().at(3);

    QValueAxis *axisY1 = (QValueAxis *)ui->chartView1->chart()->axisY();
    QValueAxis *axisSY1 = (QValueAxis *)spcDevWindow1->ui->chartViewX->chart()->axisY();

    seriesUSL1->clear();
    seriesLSL1->clear();
    seriesSetData1->clear();
    seriesRealData1->clear();

    seriesUSLS1->clear();
    seriesLSLS1->clear();
    seriesSetDataS1->clear();
    seriesRealDataS1->clear();


    //计算必须数据
    float total_min=0,total_max=0,total_sum=0.00;
    float sub_min=0,sub_max=0,sub_sum=0.00;

    for(quint8 i=0; i<totalNum1; i++)
    {
        for(quint8 j=0; j<subNum1; j++)
        {
           if(sub_min>Diameters1[i][j])
               sub_min = Diameters1[i][j];//求出子组的最小值
           if(sub_max<Diameters1[i][j])
               sub_max = Diameters1[i][j];//求出子组的最大值
           sub_sum +=  Diameters1[i][j];//计算子组的和
           total_sum += Diameters1[i][j];//计算总体的和

        }

        if(total_max<sub_max)
            total_max=sub_max;//求出总体的最大值
        if(total_min>sub_min)
            total_min=sub_min;//求出总体的最小值

        sub_avg1[i] = sub_sum/subNum1;//子组平均值
        sub_r1[i] = sub_max-sub_min;//计算子组极差
        total_r1+=sub_r1[i];//计算整体极差的和
    }
    X_bar1 = total_sum/subNum1/totalNum1;//求出整体均值
    R_bar1 = total_r1/totalNum1;//计算平均极差
    USLx1 = X_bar1 + A2[subNum1]* R_bar1;
    LSLx1 = X_bar1 - A2[subNum1]* R_bar1;

    USLr1 = D4[subNum1]*R_bar1;
    LSLr1 = D3[subNum1]*R_bar1;

    float lx = LSLx1-abs(LSLx1)*0.333;
    float ux = USLx1+abs(USLx1)*0.333;
    axisY1->setRange(lx,ux);
    axisSY1->setRange(lx,ux);
    //求σ
    sigma1 = R_bar1 / D2[subNum1];

    //求S
    float sum_diff_xbar = 0.00;
    for(quint8 i=0; i<totalNum1; i++)
    {
        for(quint8 j=0; j<subNum1; j++)
        {
            sum_diff_xbar += pow((Diameters1[i][j]-X_bar1),2);
        }
    }
    S1 = sqrt(sum_diff_xbar/(totalNum1-1));

    //计算cp的值
    Cp1 = (USLx1-LSLx1)/6/sigma1;
    Pp1 = (USLr1-LSLr1)/6/S1;
    //计算cpk的值
    Cpk1 = fmin(USLx1-X_bar1,X_bar1-LSLx1)/3/sigma1;
    Ppk1 = fmin(USLr1-R_bar1,R_bar1-LSLr1)/3/S1;

    //画出第一个机器的控制线
    for(quint8 i=1; i<totalNum1+1; i++)
    {
        seriesUSL1->append(i,USLx1);
        seriesLSL1->append(i,LSLx1);
        seriesSetData1->append(i,X_bar1);
        seriesRealData1->append(i,sub_avg1[i]);//画出X的点

        seriesUSLS1->append(i,USLx1);
        seriesLSLS1->append(i,LSLx1);
        seriesSetDataS1->append(i,X_bar1);
        seriesRealDataS1->append(i,sub_avg1[i]);//画出X的点
    }



//每五个数据写入表格一次

}
void Widget::updateData2()
{
    QLineSeries *seriesUSL2 = (QLineSeries *)ui->chartView2->chart()->series().at(0);
    QLineSeries *seriesLSL2 = (QLineSeries *)ui->chartView2->chart()->series().at(1);
    QLineSeries *seriesSetData2 = (QLineSeries *)ui->chartView2->chart()->series().at(2);
    QLineSeries *seriesRealData2 = (QLineSeries *)ui->chartView2->chart()->series().at(3);

    QLineSeries *seriesUSLS2 = (QLineSeries *)spcDevWindow2->ui->chartViewX->chart()->series().at(0);
    QLineSeries *seriesLSLS2 = (QLineSeries *)spcDevWindow2->ui->chartViewX->chart()->series().at(1);
    QLineSeries *seriesSetDataS2 = (QLineSeries *)spcDevWindow2->ui->chartViewX->chart()->series().at(2);
    QLineSeries *seriesRealDataS2 = (QLineSeries *)spcDevWindow2->ui->chartViewX->chart()->series().at(3);

    QValueAxis *axisY2 = (QValueAxis *)ui->chartView2->chart()->axisY();
    QValueAxis *axisSY2 = (QValueAxis *)spcDevWindow2->ui->chartViewX->chart()->axisY();

    seriesUSL2->clear();
    seriesLSL2->clear();
    seriesSetData2->clear();
    seriesRealData2->clear();

    seriesUSLS2->clear();
    seriesLSLS2->clear();
    seriesSetDataS2->clear();
    seriesRealDataS2->clear();


    //计算必须数据
    float total_min=0,total_max=0,total_sum=0.00;
    float sub_min=0,sub_max=0,sub_sum=0.00;

    for(quint8 i=0; i<totalNum2; i++)
    {
        for(quint8 j=0; j<subNum2; j++)
        {
           if(sub_min>Diameters2[i][j])
               sub_min = Diameters2[i][j];//求出子组的最小值
           if(sub_max<Diameters2[i][j])
               sub_max = Diameters2[i][j];//求出子组的最大值
           sub_sum +=  Diameters2[i][j];//计算子组的和
           total_sum += Diameters2[i][j];//计算总体的和

        }

        if(total_max<sub_max)
            total_max=sub_max;//求出总体的最大值
        if(total_min>sub_min)
            total_min=sub_min;//求出总体的最小值

        sub_avg2[i] = sub_sum/subNum2;//子组平均值
        sub_r2[i] = sub_max-sub_min;//计算子组极差
        total_r2+=sub_r2[i];//计算整体极差的和
    }
    X_bar2 = total_sum/subNum2/totalNum2;//求出整体均值
    R_bar2 = total_r2/totalNum2;//计算平均极差
    USLx2 = X_bar2 + A2[subNum1]* R_bar2;
    LSLx2 = X_bar2 - A2[subNum1]* R_bar2;

    USLr2 = D4[subNum1]*R_bar2;
    LSLr2 = D3[subNum1]*R_bar2;

    float lx = LSLx2-abs(LSLx2)*0.333;
    float ux = USLx2+abs(USLx2)*0.333;
    axisY2->setRange(lx,ux);
    axisSY2->setRange(lx,ux);
    //求σ
    sigma2 = R_bar2 / D2[subNum2];

    //求S
    float sum_diff_xbar = 0.00;
    for(quint8 i=0; i<totalNum2; i++)
    {
        for(quint8 j=0; j<subNum2; j++)
        {
            sum_diff_xbar += pow((Diameters2[i][j]-X_bar2),2);
        }
    }
    S2 = sqrt(sum_diff_xbar/(totalNum2-1));

    //计算cp的值
    Cp2 = (USLx2-LSLx2)/6/sigma2;
    Pp2 = (USLr2-LSLr2)/6/S2;
    //计算cpk的值
    Cpk2 = fmin(USLx2-X_bar2,X_bar2-LSLx2)/3/sigma2;
    Ppk2 = fmin(USLr2-R_bar2,R_bar2-LSLr2)/3/S2;

    //画出第一个机器的控制线
    for(quint8 i=1; i<totalNum2+1; i++)
    {
        seriesUSL2->append(i,USLx2);
        seriesLSL2->append(i,LSLx2);
        seriesSetData2->append(i,X_bar2);
        seriesRealData2->append(i,sub_avg2[i]);//画出X的点

        seriesUSLS2->append(i,USLx2);
        seriesLSLS2->append(i,LSLx2);
        seriesSetDataS2->append(i,X_bar2);
        seriesRealDataS2->append(i,sub_avg2[i]);//画出X的点
    }

}
void Widget::updateData3()
{
    QLineSeries *seriesUSL3 = (QLineSeries *)ui->chartView3->chart()->series().at(0);
    QLineSeries *seriesLSL3 = (QLineSeries *)ui->chartView3->chart()->series().at(1);
    QLineSeries *seriesSetData3 = (QLineSeries *)ui->chartView3->chart()->series().at(2);
    QLineSeries *seriesRealData3 = (QLineSeries *)ui->chartView3->chart()->series().at(3);

    QLineSeries *seriesUSLS3 = (QLineSeries *)spcDevWindow3->ui->chartViewX->chart()->series().at(0);
    QLineSeries *seriesLSLS3 = (QLineSeries *)spcDevWindow3->ui->chartViewX->chart()->series().at(1);
    QLineSeries *seriesSetDataS3 = (QLineSeries *)spcDevWindow3->ui->chartViewX->chart()->series().at(2);
    QLineSeries *seriesRealDataS3 = (QLineSeries *)spcDevWindow3->ui->chartViewX->chart()->series().at(3);

    QValueAxis *axisY3 = (QValueAxis *)ui->chartView3->chart()->axisY();
    QValueAxis *axisSY3 = (QValueAxis *)spcDevWindow3->ui->chartViewX->chart()->axisY();

    seriesUSL3->clear();
    seriesLSL3->clear();
    seriesSetData3->clear();
    seriesRealData3->clear();

    seriesUSLS3->clear();
    seriesLSLS3->clear();
    seriesSetDataS3->clear();
    seriesRealDataS3->clear();


    //计算必须数据
    float total_min=0,total_max=0,total_sum=0.00;
    float sub_min=0,sub_max=0,sub_sum=0.00;

    for(quint8 i=0; i<totalNum3; i++)
    {
        for(quint8 j=0; j<subNum3; j++)
        {
           if(sub_min>Diameters3[i][j])
               sub_min = Diameters3[i][j];//求出子组的最小值
           if(sub_max<Diameters3[i][j])
               sub_max = Diameters3[i][j];//求出子组的最大值
           sub_sum +=  Diameters3[i][j];//计算子组的和
           total_sum += Diameters3[i][j];//计算总体的和

        }

        if(total_max<sub_max)
            total_max=sub_max;//求出总体的最大值
        if(total_min>sub_min)
            total_min=sub_min;//求出总体的最小值

        sub_avg3[i] = sub_sum/subNum3;//子组平均值
        sub_r3[i] = sub_max-sub_min;//计算子组极差
        total_r3+=sub_r3[i];//计算整体极差的和
    }
    X_bar3 = total_sum/subNum3/totalNum3;//求出整体均值
    R_bar3 = total_r3/totalNum3;//计算平均极差
    USLx3 = X_bar3 + A2[subNum3]* R_bar3;
    LSLx3 = X_bar3 - A2[subNum3]* R_bar3;

    USLr3 = D4[subNum3]*R_bar3;
    LSLr3 = D3[subNum3]*R_bar3;

    float lx = LSLx3-abs(LSLx3)*0.333;
    float ux = USLx3+abs(USLx3)*0.333;
    axisY3->setRange(lx,ux);
    axisSY3->setRange(lx,ux);
    //求σ
    sigma3 = R_bar3 / D2[subNum3];

    //求S
    float sum_diff_xbar = 0.00;
    for(quint8 i=0; i<totalNum3; i++)
    {
        for(quint8 j=0; j<subNum3; j++)
        {
            sum_diff_xbar += pow((Diameters3[i][j]-X_bar3),2);
        }
    }
    S3 = sqrt(sum_diff_xbar/(totalNum3-1));

    //计算cp的值
    Cp3 = (USLx3-LSLx3)/6/sigma3;
    Pp3 = (USLr3-LSLr3)/6/S3;
    //计算cpk的值
    Cpk3 = fmin(USLx3-X_bar3,X_bar3-LSLx3)/3/sigma3;
    Ppk3 = fmin(USLr3-R_bar3,R_bar3-LSLr3)/3/S3;

    //画出第一个机器的控制线
    for(quint8 i=1; i<totalNum3+1; i++)
    {
        seriesUSL3->append(i,USLx3);
        seriesLSL3->append(i,LSLx3);
        seriesSetData3->append(i,X_bar3);
        seriesRealData3->append(i,sub_avg3[i]);//画出X的点

        seriesUSLS3->append(i,USLx3);
        seriesLSLS3->append(i,LSLx3);
        seriesSetDataS3->append(i,X_bar3);//整体均值
        seriesRealDataS3->append(i,sub_avg3[i]);//画出X的点
    }

}



void Widget::createChart()
{
    //主界面
    QChart *chartMain1 = new QChart();
    QChart *chartMain2 = new QChart();
    QChart *chartMain3 = new QChart();

    //SPC界面
    QChart *chart1 = new QChart();
    QChart *chart2 = new QChart();
    QChart *chart3 = new QChart();

    //总界面
    chartMain1->setTitle("机器1控制图");
    chartMain2->setTitle("机器2控制图");
    chartMain3->setTitle("机器3控制图");

    //SPC界面
    chart1->setTitle("机器1控制图");
    chart2->setTitle("机器2控制图");
    chart3->setTitle("机器3控制图");




    //主界面控制图的四根线
    QLineSeries *seriesUSL1 = new QLineSeries;
    QLineSeries *seriesLSL1 = new QLineSeries;
    QLineSeries *seriesSetData1 = new QLineSeries;
    QLineSeries *seriesRealData1 = new QLineSeries;

    QLineSeries *seriesUSL2 = new QLineSeries;
    QLineSeries *seriesLSL2 = new QLineSeries;
    QLineSeries *seriesSetData2 = new QLineSeries;
    QLineSeries *seriesRealData2 = new QLineSeries;

    QLineSeries *seriesUSL3 = new QLineSeries;
    QLineSeries *seriesLSL3 = new QLineSeries;
    QLineSeries *seriesSetData3 = new QLineSeries;
    QLineSeries *seriesRealData3 = new QLineSeries;

    //SPC界面
    QLineSeries *seriesUSLS1 = new QLineSeries;
    QLineSeries *seriesLSLS1 = new QLineSeries;
    QLineSeries *seriesSetDataS1 = new QLineSeries;
    QLineSeries *seriesRealDataS1 = new QLineSeries;

    QLineSeries *seriesUSLS2 = new QLineSeries;
    QLineSeries *seriesLSLS2 = new QLineSeries;
    QLineSeries *seriesSetDataS2 = new QLineSeries;
    QLineSeries *seriesRealDataS2 = new QLineSeries;

    QLineSeries *seriesUSLS3 = new QLineSeries;
    QLineSeries *seriesLSLS3 = new QLineSeries;
    QLineSeries *seriesSetDataS3 = new QLineSeries;
    QLineSeries *seriesRealDataS3 = new QLineSeries;

    // 设置线颜色
    QPen pen1;
    //pen1.setStyle(Qt::DashLine);
    pen1.setWidth(2);
    pen1.setColor(Qt::darkGreen);

    QPen pen2;
    pen2.setStyle(Qt::DashLine);
    pen2.setWidth(2);
    pen2.setColor(Qt::darkYellow);

    QPen pen3;
    //pen3.setStyle(Qt::DashLine);
    pen3.setWidth(1);
    pen3.setColor(Qt::cyan);



    //主界面设置四根线
    seriesUSL1->setName("USL");
    seriesLSL1->setName("LSL");
    seriesSetData1->setName("整体均值");
    seriesRealData1->setName("实际值");

    seriesUSL2->setName("USL");
    seriesLSL2->setName("LSL");
    seriesSetData2->setName("整体均值");
    seriesRealData2->setName("实际值");

    seriesUSL3->setName("USL");
    seriesLSL3->setName("LSL");
    seriesSetData3->setName("整体均值");
    seriesRealData3->setName("实际值");
    //spc
    seriesUSLS1->setName("USL");
    seriesLSLS1->setName("LSL");
    seriesSetDataS1->setName("整体均值");
    seriesRealDataS1->setName("实际值");

    seriesUSLS2->setName("USL");
    seriesLSLS2->setName("LSL");
    seriesSetDataS2->setName("整体均值");
    seriesRealDataS2->setName("实际值");

    seriesUSLS3->setName("USL");
    seriesLSLS3->setName("LSL");
    seriesSetDataS3->setName("整体均值");
    seriesRealDataS3->setName("实际值");

    //主界面线设置
    seriesUSL1->setPen(pen1);
    seriesLSL1->setPen(pen1);
    seriesSetData1->setPen(pen2);
    seriesRealData1->setPen(pen3);
    seriesUSL2->setPen(pen1);
    seriesLSL2->setPen(pen1);
    seriesSetData2->setPen(pen2);
    seriesRealData2->setPen(pen3);
    seriesUSL3->setPen(pen1);
    seriesLSL3->setPen(pen1);
    seriesSetData3->setPen(pen2);
    seriesRealData3->setPen(pen3);
    //spc
    seriesUSLS1->setPen(pen1);
    seriesLSLS1->setPen(pen1);
    seriesSetDataS1->setPen(pen2);
    seriesRealDataS1->setPen(pen3);
    seriesUSLS2->setPen(pen1);
    seriesLSLS2->setPen(pen1);
    seriesSetDataS2->setPen(pen2);
    seriesRealDataS2->setPen(pen3);
    seriesUSLS3->setPen(pen1);
    seriesLSLS3->setPen(pen1);
    seriesSetDataS3->setPen(pen2);
    seriesRealDataS3->setPen(pen3);




    //主界面三个图添加四根线
    chartMain1->addSeries(seriesUSL1);
    chartMain1->addSeries(seriesLSL1);
    chartMain1->addSeries(seriesSetData1);
    chartMain1->addSeries(seriesRealData1);

    chartMain2->addSeries(seriesUSL2);
    chartMain2->addSeries(seriesLSL2);
    chartMain2->addSeries(seriesSetData2);
    chartMain2->addSeries(seriesRealData2);

    chartMain3->addSeries(seriesUSL3);
    chartMain3->addSeries(seriesLSL3);
    chartMain3->addSeries(seriesSetData3);
    chartMain3->addSeries(seriesRealData3);

    //SPC添加四根线
    chart1->addSeries(seriesUSLS1);
    chart1->addSeries(seriesLSLS1);
    chart1->addSeries(seriesSetDataS1);
    chart1->addSeries(seriesRealDataS1);

    chart2->addSeries(seriesUSLS2);
    chart2->addSeries(seriesLSLS2);
    chart2->addSeries(seriesSetDataS2);
    chart2->addSeries(seriesRealDataS2);

    chart3->addSeries(seriesUSLS3);
    chart3->addSeries(seriesLSLS3);
    chart3->addSeries(seriesSetDataS3);
    chart3->addSeries(seriesRealDataS3);

    //主界面chart1
    QValueAxis *axisX1 = new QValueAxis;
    QValueAxis *axisY1 = new QValueAxis;
    axisX1->setRange(1,totalNum1);
    axisY1->setRange(LSLx1-abs(LSLx1)*0.333,USLx1+abs(USLx1)*0.333);
    axisX1->setTickCount(20);//格子数
    axisY1->setTickCount(9);//格子数
    //主界面chart2
    QValueAxis *axisX2 = new QValueAxis;
    QValueAxis *axisY2 = new QValueAxis;
    axisX2->setRange(1,totalNum2);
    axisY2->setRange(LSLx2-abs(LSLx2)*0.333,USLx2+abs(USLx2)*0.333);
    axisX2->setTickCount(20);//格子数
    axisY2->setTickCount(9);//格子数
    //主界面chart3
    QValueAxis *axisX3 = new QValueAxis;
    QValueAxis *axisY3 = new QValueAxis;
    axisX3->setRange(1,totalNum3);
    axisY3->setRange(LSLx3-abs(LSLx3)*0.333,USLx3+abs(USLx3)*0.333);
    axisX3->setTickCount(20);//格子数
    axisY3->setTickCount(9);//格子数

    //主界面chart1
    QValueAxis *axisSX1 = new QValueAxis;
    QValueAxis *axisSY1 = new QValueAxis;
    axisSX1->setRange(1,totalNum1);
    axisSY1->setRange(LSLx1-abs(LSLx1)*0.333,USLx1+abs(USLx1)*0.333);
    axisSX1->setTickCount(20);//格子数
    axisSY1->setTickCount(9);//格子数
    //主界面chart2
    QValueAxis *axisSX2 = new QValueAxis;
    QValueAxis *axisSY2 = new QValueAxis;
    axisSX2->setRange(1,totalNum2);
    axisSY2->setRange(LSLx2-abs(LSLx2)*0.333,USLx2+abs(USLx2)*0.333);
    axisSX2->setTickCount(20);//格子数
    axisSY2->setTickCount(9);//格子数
    //主界面chart3
    QValueAxis *axisSX3 = new QValueAxis;
    QValueAxis *axisSY3 = new QValueAxis;
    axisSX3->setRange(1,totalNum3);
    axisSY3->setRange(LSLx3-abs(LSLx3)*0.333,USLx3+abs(USLx3)*0.333);
    axisSX3->setTickCount(20);//格子数
    axisSY3->setTickCount(9);//格子数





    //总界面1
    chartMain1->setAxisX(axisX1,seriesUSL1);
    chartMain1->setAxisX(axisX1,seriesLSL1);
    chartMain1->setAxisX(axisX1,seriesSetData1);
    chartMain1->setAxisX(axisX1,seriesRealData1);

    chartMain1->setAxisY(axisY1,seriesUSL1);
    chartMain1->setAxisY(axisY1,seriesLSL1);
    chartMain1->setAxisY(axisY1,seriesSetData1);
    chartMain1->setAxisY(axisY1,seriesRealData1);

    //总界面2
    chartMain2->setAxisX(axisX2,seriesUSL2);
    chartMain2->setAxisX(axisX2,seriesLSL2);
    chartMain2->setAxisX(axisX2,seriesSetData2);
    chartMain2->setAxisX(axisX2,seriesRealData2);

    chartMain2->setAxisY(axisY2,seriesUSL2);
    chartMain2->setAxisY(axisY2,seriesLSL2);
    chartMain2->setAxisY(axisY2,seriesSetData2);
    chartMain2->setAxisY(axisY2,seriesRealData2);

    //总界面3
    chartMain3->setAxisX(axisX3,seriesUSL3);
    chartMain3->setAxisX(axisX3,seriesLSL3);
    chartMain3->setAxisX(axisX3,seriesSetData3);
    chartMain3->setAxisX(axisX3,seriesRealData3);

    chartMain3->setAxisY(axisY3,seriesUSL3);
    chartMain3->setAxisY(axisY3,seriesLSL3);
    chartMain3->setAxisY(axisY3,seriesSetData3);
    chartMain3->setAxisY(axisY3,seriesRealData3);

    //SPC1
    chart1->setAxisX(axisSX1,seriesUSLS1);
    chart1->setAxisX(axisSX1,seriesLSLS1);
    chart1->setAxisX(axisSX1,seriesSetDataS1);
    chart1->setAxisX(axisSX1,seriesRealDataS1);

    chart1->setAxisY(axisSY1,seriesUSLS1);
    chart1->setAxisY(axisSY1,seriesLSLS1);
    chart1->setAxisY(axisSY1,seriesSetDataS1);
    chart1->setAxisY(axisSY1,seriesRealDataS1);

    //SPC2
    chart2->setAxisX(axisSX2,seriesUSLS2);
    chart2->setAxisX(axisSX2,seriesLSLS2);
    chart2->setAxisX(axisSX2,seriesSetDataS2);
    chart2->setAxisX(axisSX2,seriesRealDataS2);

    chart2->setAxisY(axisSY2,seriesUSLS2);
    chart2->setAxisY(axisSY2,seriesLSLS2);
    chart2->setAxisY(axisSY2,seriesSetDataS2);
    chart2->setAxisY(axisSY2,seriesRealDataS2);

    //SPC3
    chart3->setAxisX(axisSX3,seriesUSLS3);
    chart3->setAxisX(axisSX3,seriesLSLS3);
    chart3->setAxisX(axisSX3,seriesSetDataS3);
    chart3->setAxisX(axisSX3,seriesRealDataS3);

    chart3->setAxisY(axisSY3,seriesUSLS3);
    chart3->setAxisY(axisSY3,seriesLSLS3);
    chart3->setAxisY(axisSY3,seriesSetDataS3);
    chart3->setAxisY(axisSY3,seriesRealDataS3);



    //主界面只显示X_bar图
    ui->chartView1->setChart(chartMain1);
    ui->chartView2->setChart(chartMain2);
    ui->chartView3->setChart(chartMain3);

    spcDevWindow1->ui->chartViewX->setChart(chart1);
    spcDevWindow2->ui->chartViewX->setChart(chart2);
    spcDevWindow3->ui->chartViewX->setChart(chart3);


    ui->chartView1->setRenderHint(QPainter::Antialiasing);
    ui->chartView2->setRenderHint(QPainter::Antialiasing);
    ui->chartView3->setRenderHint(QPainter::Antialiasing);
    spcDevWindow1->ui->chartViewX->setRenderHint(QPainter::Antialiasing);
    spcDevWindow2->ui->chartViewX->setRenderHint(QPainter::Antialiasing);
    spcDevWindow3->ui->chartViewX->setRenderHint(QPainter::Antialiasing);


}




void Widget::createBar()
{
    QChart  *chart1 = new QChart;
    QChart  *chart2 = new QChart;
    QChart  *chart3 = new QChart;
    chart1->setAnimationOptions(QChart::SeriesAnimations);
    chart2->setAnimationOptions(QChart::SeriesAnimations);
    chart3->setAnimationOptions(QChart::SeriesAnimations);


    // 设置线颜色
//    QPen pen1;
//    pen1.setStyle(Qt::DotLine);
//    pen1.setWidth(1);
//    pen1.setColor(Qt::green);

    QPen pen1;
    pen1.setStyle(Qt::SolidLine);
    pen1.setWidth(2);
    pen1.setColor(Qt::darkRed);



    QBarSet *set1 = new QBarSet("直方图");
    QBarSeries *seriesBar1 = new QBarSeries;
    seriesBar1->append(set1);

    QBarSet *set2 = new QBarSet("直方图");
    QBarSeries *seriesBar2 = new QBarSeries;
    seriesBar2->append(set2);

    QBarSet *set3 = new QBarSet("直方图");
    QBarSeries *seriesBar3 = new QBarSeries;
    seriesBar3->append(set3);


    QLineSeries *control1 = new QLineSeries;
    QLineSeries *control2 = new QLineSeries;
    QLineSeries *control3 = new QLineSeries;



    control1->setPen(pen1);
    control2->setPen(pen1);
    control3->setPen(pen1);
    control1->setName("控制线");
    control2->setName("控制线");
    control3->setName("控制线");

    chart1->addSeries(control1);
    chart1->addSeries(seriesBar1);

    chart2->addSeries(control2);
    chart2->addSeries(seriesBar2);

    chart3->addSeries(control3);
    chart3->addSeries(seriesBar3);


    QValueAxis *axisX1 = new QValueAxis;
    QValueAxis *axisY1 = new QValueAxis;
    QValueAxis *axisX2 = new QValueAxis;
    QValueAxis *axisY2 = new QValueAxis;
    QValueAxis *axisX3 = new QValueAxis;
    QValueAxis *axisY3 = new QValueAxis;


    axisX1->setRange(1,10);
    //axisX1->setTickCount(10);
    axisY1->setRange(1,20);

    axisX2->setRange(1,10);
    //axisX2->setTickCount(10);
    axisY2->setRange(1,20);

    axisX3->setRange(1,10);
    //axisX3->setTickCount(10);
    axisY3->setRange(1,20);


    chart1->setAxisX(axisX1,control1);
    chart1->setAxisX(axisX1,seriesBar1);

    chart2->setAxisX(axisX2,control2);
    chart2->setAxisX(axisX2,seriesBar2);

    chart3->setAxisX(axisX3,control3);
    chart3->setAxisX(axisX3,seriesBar3);

    spcDevWindow1->ui->chartViewBar->setChart(chart1);
    spcDevWindow1->ui->chartViewBar->setRenderHint(QPainter::Antialiasing);
    spcDevWindow2->ui->chartViewBar->setChart(chart2);
    spcDevWindow2->ui->chartViewBar->setRenderHint(QPainter::Antialiasing);
    spcDevWindow3->ui->chartViewBar->setChart(chart3);
    spcDevWindow3->ui->chartViewBar->setRenderHint(QPainter::Antialiasing);

}
