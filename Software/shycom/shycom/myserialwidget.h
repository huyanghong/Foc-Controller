#ifndef MYSERIALWIDGET_H
#define MYSERIALWIDGET_H

#include <QWidget>
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
#include <QTimer>
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
#include <QSerialPort>

class MySerialWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MySerialWidget(QWidget *parent = nullptr);

signals:
    void signalSerialReceiveBuf(const QByteArray &qba);


public slots:
    void slotSerialSend(const QByteArray &qba);
    void slotBtnClearClicked(void);
    void slotBtnSendClicked(void);
    void slotUpdateSerialList(void);
    void slotReadySerialRead(void);
    void slotOpenOrCloseSerial(void);
    void slot_cbb_baud_currentIndexChanged(void);
    void slot_cbb_com_activated(void);

public:
    QTimer *uTimer;
    QSerialPort *serial;
    QTextBrowser *tb_rx_buf;
    QTextEdit *te_tx_buf;
    QCheckBox *cb_hex_receive;
    QCheckBox *cb_hex_send;
    QCheckBox *cb_send_enter;
    QCheckBox *cb_auto_enter;
    QLabel *lab_txbyte;
    QLabel *lab_rxbyte;
    QPushButton *btn_send;
    QPushButton *btn_clear;
    QComboBox *cbb_com;
    QComboBox *cbb_baud;
    QPushButton *btn_serial_sw;
};

#endif // MYSERIALWIDGET_H
