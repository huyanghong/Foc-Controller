#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include <string>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_legend.h>
#include <qwt_point_data.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_zoomer.h>
#include "myserialwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Designed by HuYangHong");

    initToolBar();

    uTimer = new QTimer(this);
    uTimer->start(1000);
    initGuiSerialBase();

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::initToolBar(void){
    QToolBar *toolBar = addToolBar("toolBar");

    //***********串口工具栏****************//
    serialAction = new QAction("serial");
    toolBar->addAction(serialAction);
    connect(serialAction, &QAction::triggered, this, &MainWindow::initGuiSerialBase);
    dock_serial_base_gui = new MyDockWidget();
    connect(dock_serial_base_gui, &MyDockWidget::signalDockwidgetClose, this, &MainWindow::slotSerialActionDockwidgetClose);
    //***********绘图工具栏****************//
    toolBar->addSeparator();
    curveAction = new QAction("绘图");
    toolBar->addAction(curveAction);
    connect(curveAction, &QAction::triggered, this, &MainWindow::initGuiCurveBase);
    dock_curve_base_gui = new MyDockWidget();
    connect(dock_curve_base_gui, &MyDockWidget::signalDockwidgetClose, this, &MainWindow::slotCurveActionDockwidgetClose);

    //***********MOTOR工具栏****************//
    for(int i=0; i<4; i++){
        toolBar->addSeparator();
        motorAction[i] = new QAction(modular_name[i]);
        toolBar->addAction(motorAction[i]);
        dock_motor_base_gui[i] = new MyDockWidget();
    }
    connect(motorAction[0], &QAction::triggered, this, &MainWindow::initGuiMotorBase0);
    connect(motorAction[1], &QAction::triggered, this, &MainWindow::initGuiMotorBase1);
    connect(motorAction[2], &QAction::triggered, this, &MainWindow::initGuiMotorBase2);
    connect(motorAction[3], &QAction::triggered, this, &MainWindow::initGuiMotorBase3);
    connect(dock_motor_base_gui[0], &MyDockWidget::signalDockwidgetClose, this, &MainWindow::slotMotorActionDockwidgetClose0);
    connect(dock_motor_base_gui[1], &MyDockWidget::signalDockwidgetClose, this, &MainWindow::slotMotorActionDockwidgetClose1);
    connect(dock_motor_base_gui[2], &MyDockWidget::signalDockwidgetClose, this, &MainWindow::slotMotorActionDockwidgetClose2);
    connect(dock_motor_base_gui[3], &MyDockWidget::signalDockwidgetClose, this, &MainWindow::slotMotorActionDockwidgetClose3);

    toolBar->setIconSize(QSize(32,32));

}

void MainWindow::initGuiMotorBase(uint8_t id){
    //***********初始化控件****************//
    if(motorAction[id]->isChecked())
        return;
    motorAction[id]->setEnabled(false);

    if(dock_motor_base_gui[id]->isOpen){
        //**************生成窗口*******************//
        btn_add_motor[id] = new QPushButton("新增一个调试窗口");
        if(id == 0) connect(btn_add_motor[id], &QPushButton::clicked, this, &MainWindow::slotAddMotorItem0);
        else if(id == 1) connect(btn_add_motor[id], &QPushButton::clicked, this, &MainWindow::slotAddMotorItem1);
        else if(id == 2) connect(btn_add_motor[id], &QPushButton::clicked, this, &MainWindow::slotAddMotorItem2);
        else if(id == 3) connect(btn_add_motor[id], &QPushButton::clicked, this, &MainWindow::slotAddMotorItem3);

        QHBoxLayout *h = new QHBoxLayout();
        h->addStretch();
        h->addWidget(btn_add_motor[id]);

        motorWidget[id] = new QWidget(dock_motor_base_gui[id]);
        motorLayout[id] = new QVBoxLayout(motorWidget[id]);
        motorLayout[id]->addLayout(h);

        myMotorWidget[id] = new MyMotorWidget(this);
        motorLayout[id]->addWidget(myMotorWidget[id]);
        motorLayout[id]->addStretch();

        dock_motor_base_gui[id]->setWindowTitle(modular_name[id]);
        dock_motor_base_gui[id]->setWidget(motorWidget[id]);
        dock_motor_base_gui[id]->setFeatures(QDockWidget::AllDockWidgetFeatures);
        dock_motor_base_gui[id]->setAllowedAreas(Qt::AllDockWidgetAreas);
        this->addDockWidget(Qt::RightDockWidgetArea, dock_motor_base_gui[id]);
        connect(myMotorWidget[id], &MyMotorWidget::signalWriteParameter, myserialwidget, &MySerialWidget::slotSerialSend);

        addMotorItem("Kp", modular_id[id]);
        addMotorItem("Ki", modular_id[id]);
        addMotorItem("Kd", modular_id[id]);
        addMotorItem("target", modular_id[id]);

    }else {
        dock_motor_base_gui[id]->show();
        dock_motor_base_gui[id]->isOpen = true;
    }
}

void MainWindow::initGuiCurveBase(void){
    //***********初始化控件****************//
    if(curveAction->isChecked())
        return;
    curveAction->setEnabled(false);

    if(dock_curve_base_gui->isOpen){
        //**************生成窗口*******************//
        mycurvewidget = new MyCurveWidget();
        dock_curve_base_gui->setWindowTitle("绘图");
        dock_curve_base_gui->setWidget(mycurvewidget);
        dock_curve_base_gui->setFeatures(QDockWidget::AllDockWidgetFeatures);
        dock_curve_base_gui->setAllowedAreas(Qt::AllDockWidgetAreas);
        this->addDockWidget(Qt::BottomDockWidgetArea, dock_curve_base_gui);
        connect(serial_thread, &SerialThread::signalSendCurvePoint, mycurvewidget, &MyCurveWidget::slotReceiveCurvePoint);
    }else {
        dock_curve_base_gui->show();
        dock_curve_base_gui->isOpen = true;
    }
}

void MainWindow::initGuiSerialBase(void){
    //***********初始化控件****************//
    if(serialAction->isChecked())
        return;
    serialAction->setEnabled(false);

    if(dock_serial_base_gui->isOpen){
        //**************生成窗口*******************//
        serial_thread = new SerialThread();
        myserialwidget = new MySerialWidget();
        dock_serial_base_gui->setWindowTitle("串口收发");
        dock_serial_base_gui->setWidget(myserialwidget);
        dock_serial_base_gui->setFeatures(QDockWidget::AllDockWidgetFeatures);
        dock_serial_base_gui->setAllowedAreas(Qt::AllDockWidgetAreas);
        this->addDockWidget(Qt::TopDockWidgetArea, dock_serial_base_gui);
        this->setCentralWidget(dock_serial_base_gui);

        connect(myserialwidget, &MySerialWidget::signalSerialReceiveBuf, serial_thread, &SerialThread::slotReceiveSerialBuf);
    }else {
        dock_serial_base_gui->show();
        dock_serial_base_gui->isOpen = true;
    }
}

void MainWindow::slotSerialActionDockwidgetClose(void){
    serialAction->setEnabled(true);
}
void MainWindow::slotCurveActionDockwidgetClose(void){
    curveAction->setEnabled(true);
}
void MainWindow::slotMotorActionDockwidgetClose(uint8_t id){
    motorAction[id]->setEnabled(true);
}

void MainWindow::addMotorItem(QString name, uint8_t modu_id){
    myMotorWidget[modu_id] = new MyMotorWidget();
    myMotorWidget[modu_id]->initUi(name, motorLayout[modu_id]->count()-3, modu_id);

    QPalette pal(myMotorWidget[modu_id]->palette());
    pal.setColor(QPalette::Background, Qt::white);
    myMotorWidget[modu_id]->setAutoFillBackground(true);

    myMotorWidget[modu_id]->setPalette(pal);

    motorLayout[modu_id]->removeItem(motorLayout[modu_id]->itemAt(motorLayout[modu_id]->count()-1));
    motorLayout[modu_id]->addWidget(myMotorWidget[modu_id]);
    motorLayout[modu_id]->addStretch();
    connect(myMotorWidget[modu_id], &MyMotorWidget::signalWriteParameter, myserialwidget, &MySerialWidget::slotSerialSend);
}
