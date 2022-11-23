#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPlainTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QSpacerItem>
#include <QFormLayout>
#include <QLineEdit>
#include <QWidget>
#include <QTextBrowser>
#include <QCheckBox>
#include <QTime>
#include <QComboBox>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>
#include <QTextCodec>   //中文支持
#include <QDir>
#include <QThread>
#include <QToolBar>
#include <QComboBox>
#include <QLineEdit>
#include "SerialThread.h"
#include "QByteArray"
#include "QPen"

#include "qwt_point_data.h"
#include "qwt_plot_curve.h"
#include "qwt_plot.h"

#include "mycurvewidget.h"
#include "myserialwidget.h"
#include "mydockwidget.h"
#include "mymotorwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initToolBar();
    void initGuiSerialBase();
    void initGuiCurveBase();
    void initGuiMotorBase(uint8_t id);

    void addMotorItem(QString name, uint8_t modu_id);
signals:

public slots:
    void slotSerialActionDockwidgetClose();
    void slotCurveActionDockwidgetClose();
    void slotMotorActionDockwidgetClose(uint8_t id);
    void slotAddMotorItem0(){addMotorItem("other", 0);};
    void slotAddMotorItem1(){addMotorItem("other", 1);};
    void slotAddMotorItem2(){addMotorItem("other", 2);};
    void slotAddMotorItem3(){addMotorItem("other", 3);};
    void initGuiMotorBase0(){initGuiMotorBase(0);};
    void initGuiMotorBase1(){initGuiMotorBase(1);};
    void initGuiMotorBase2(){initGuiMotorBase(2);};
    void initGuiMotorBase3(){initGuiMotorBase(3);};
    void slotMotorActionDockwidgetClose0(){slotMotorActionDockwidgetClose(0);};
    void slotMotorActionDockwidgetClose1(){slotMotorActionDockwidgetClose(1);};
    void slotMotorActionDockwidgetClose2(){slotMotorActionDockwidgetClose(2);};
    void slotMotorActionDockwidgetClose3(){slotMotorActionDockwidgetClose(3);};
private:
    Ui::MainWindow *ui;
    QTimer *uTimer;

    //*******串口THREAD***********//
    SerialThread *serial_thread;

    //*******串口GUI组件***********//
    MyDockWidget *dock_serial_base_gui;
    QAction *serialAction;
    MySerialWidget *myserialwidget;

    //*******CURVE-GUI组件***********//
    QAction *curveAction;
    MyDockWidget *dock_curve_base_gui;
    MyCurveWidget *mycurvewidget;

    //*******MOTOR-GUI组件***********/
    MyDockWidget *dock_motor_base_gui[4];
    QAction *motorAction[4];
    MyMotorWidget *myMotorWidget[4];
    QWidget *motorWidget[4];
    QVBoxLayout *motorLayout[4];
    QPushButton *btn_add_motor[4];
    uint8_t modular_id[4] = {0, 1, 2, 3};
    QString modular_name[4] = {"电流环", "速度环", "位置环", "其他"};

};
#endif // MAINWINDOW_H
