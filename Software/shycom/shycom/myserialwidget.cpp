#include "myserialwidget.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QLineEdit>
#include <QComboBox>
MySerialWidget::MySerialWidget(QWidget *parent) : QWidget(parent)
{
    uTimer = new QTimer(this);
    serial = new QSerialPort(this);

    tb_rx_buf = new QTextBrowser(this);
    te_tx_buf = new QTextEdit(this);
    cb_hex_receive = new QCheckBox("16进制接收");
    cb_hex_receive->setChecked(true);
    cb_hex_send = new QCheckBox("16进制发送");
    cb_send_enter = new QCheckBox("发送新行");
    cb_auto_enter = new QCheckBox("自动换行");
    cb_auto_enter->setChecked(true);
    lab_txbyte= new QLabel("0");
    lab_rxbyte = new QLabel("0");
    btn_send = new QPushButton("发送");
    btn_clear = new QPushButton("清除接收");
    cbb_com = new QComboBox(this);
    cbb_baud = new QComboBox(this);
    btn_serial_sw = new QPushButton("打开串口");

    QLabel *lab_com = new QLabel("串口号:");
    QLabel *lab_baud = new QLabel("波特率:");
    QLabel *RX = new QLabel("RX: ");
    QLabel *TX = new QLabel("TX: ");
    QLabel *RX_DATA = new QLabel("接收窗口");
    QLabel *TX_DATA = new QLabel("发送窗口");

    //**************控件赋值*******************//
    cbb_com->clear();
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        cbb_com->addItem(info.portName());  //串口号下拉菜单，增加一个条目
    cbb_baud->insertItem(0, "9600");
    cbb_baud->insertItem(1, "115200");
    cbb_baud->insertItem(2, "256000");
    cbb_baud->insertItem(3, "921600");
    cbb_baud->insertItem(4, "1000000");
    cbb_baud->insertItem(5, "1500000");
    cbb_baud->setCurrentIndex(5);

    //初始化按钮失能
    btn_send->setDisabled(true);
    te_tx_buf->setDisabled(true);
    tb_rx_buf->document()->setMaximumBlockCount(40);
    tb_rx_buf->setFont(QFont("Ubuntu MOno", 10));
    te_tx_buf->setMaximumHeight(50);
    tb_rx_buf->setMinimumHeight(100);

    //**************UI设计*******************//
    QHBoxLayout *hlayout1 = new QHBoxLayout();
    hlayout1->addWidget(RX_DATA);
    hlayout1->addStretch();
    hlayout1->addWidget(RX);
    hlayout1->addWidget(lab_rxbyte);
    hlayout1->addWidget(cb_hex_receive);
    hlayout1->addWidget(cb_auto_enter);
    hlayout1->addWidget(btn_clear);

    QHBoxLayout *hlayout2 = new QHBoxLayout();
    hlayout2->addWidget(TX_DATA);
    hlayout2->addStretch();
    hlayout2->addWidget(TX);
    hlayout2->addWidget(lab_txbyte);
    hlayout2->addWidget(cb_hex_send);
    hlayout2->addWidget(cb_send_enter);
    hlayout2->addWidget(btn_send);

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addWidget(tb_rx_buf,2);
    vlayout->addLayout(hlayout1,3);
    vlayout->addWidget(te_tx_buf,4);
    vlayout->addLayout(hlayout2,5);

    QGridLayout *glayout = new QGridLayout();
    glayout->addWidget(lab_com, 0, 0);
    glayout->addWidget(cbb_com, 0, 1);
    glayout->addWidget(lab_baud, 1, 0);
    glayout->addWidget(cbb_baud, 1, 1);
    glayout->addWidget(btn_serial_sw, 4, 1);

    QVBoxLayout *vlayout2 = new QVBoxLayout();
    vlayout2->addLayout(glayout);
    vlayout2->addStretch();

    QHBoxLayout *seriallayout = new QHBoxLayout();
    seriallayout->addLayout(vlayout);
    seriallayout->addLayout(vlayout2);

    setLayout(seriallayout);

    //**************信号-槽连接*****************//
    connect(btn_serial_sw, &QPushButton::clicked, this, &MySerialWidget::slotOpenOrCloseSerial);
    connect(serial, &QSerialPort::readyRead, this, &MySerialWidget::slotReadySerialRead);
    connect(btn_clear, &QPushButton::clicked, this, &MySerialWidget::slotBtnClearClicked);
    connect(btn_send, &QPushButton::clicked, this, &MySerialWidget::slotBtnSendClicked);
    connect(uTimer, &QTimer::timeout, this, &MySerialWidget::slotUpdateSerialList);
    uTimer->start(1000);

    connect(cbb_baud, &QComboBox::currentTextChanged, this, &MySerialWidget::slot_cbb_baud_currentIndexChanged);
    //connect(cbb_com, &QComboBox::currentTextChanged, this, &MySerialWidget::slot_cbb_com_activated);
}

void MySerialWidget::slotOpenOrCloseSerial(void){
    if(btn_serial_sw->text() == "打开串口"){
        serial->setPortName(cbb_com->currentText());
        serial->setBaudRate(cbb_baud->currentText().toInt());
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        if(!serial->open(QIODevice::ReadWrite)){
            QMessageBox::warning(NULL, "提示", "串口打开失败");
            return;
        }
        serial->clear(QSerialPort::AllDirections);
        btn_serial_sw->setText("关闭串口");
        btn_send->setEnabled(true);
        te_tx_buf->setEnabled(true);
        cbb_com->setEnabled(false);
        //cbb_baud->setEnabled(false);
        //cbb_databit->setEnabled(false);
        //cbb_stopbit->setEnabled(false);
    } else{
        serial->close();
        btn_serial_sw->setText("打开串口");
        btn_send->setDisabled(true);
        te_tx_buf->setDisabled(true);
        cbb_com->setEnabled(true);
        //cbb_baud->setEnabled(true);
        //cbb_databit->setEnabled(true);
        //cbb_stopbit->setEnabled(true);
    }
}
void MySerialWidget::slot_cbb_com_activated(void){
    //QString str = arg1;
    serial->close(); btn_serial_sw->setText("打开串口");
    /*if(btn_serial_sw->text() == "关闭串口"){
        serial->setPortName(cbb_com->currentText());
        serial->setBaudRate(cbb_baud->currentText().toInt());
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        if(!serial->open(QIODevice::ReadWrite)){
            QMessageBox::warning(NULL, "提示", "串口打开失败");
            btn_serial_sw->setText("打开串口");
            return;
        }
        serial->clear(QSerialPort::AllDirections);
    }*/
}

void MySerialWidget::slotReadySerialRead(void){
      QByteArray rx_buf = this->serial->readAll();
      emit signalSerialReceiveBuf(rx_buf);

      QString rx_buf_tmp;
      if(cb_hex_receive->isChecked()){
           QString ret(rx_buf.toHex().toUpper());
           int len = ret.length();
           for(int i=0; i<len/2; i++)
               ret.insert(len - 2*i, " ");
           rx_buf_tmp = ret;
      } else rx_buf_tmp = QString::fromLocal8Bit(rx_buf); //转换为中文格式

      if(cb_auto_enter->isChecked())
          tb_rx_buf->append(rx_buf_tmp);
      else
          tb_rx_buf->insertPlainText(rx_buf_tmp);
      tb_rx_buf->moveCursor(QTextCursor::End);

      int len = lab_rxbyte->text().toInt() + rx_buf.length();
      lab_rxbyte->setText(QString::number(len));
}

void MySerialWidget::slotBtnClearClicked(void){
    tb_rx_buf->clear();
    lab_rxbyte->setText("0");
}
void MySerialWidget::slotBtnSendClicked(void){
    QByteArray tx_buf_tmp;
    QString tx_buf = te_tx_buf->toPlainText();
    tx_buf.remove(QRegExp("\\s"));

    if(cb_hex_send->isChecked()){
        if(tx_buf.length() % 2){
            QMessageBox::warning(NULL, "错误提示", "数据长度有误");
            return;
        }
        for(int index=0; index<tx_buf.length()/2; index++){
            QString  str = tx_buf.mid(2*index, 2);
            if(!((str[0] >='0' &&  str[0] <='9') || (str[0] >='a' &&  str[0] <='f') || (str[0] >='A' &&  str[0] <='F'))){
                QMessageBox::warning(NULL, "错误提示", "有非法字符");
                return;
            }
            if(!((str[1] >='0' &&  str[1] <='9') || (str[1] >='a' &&  str[1] <='f') || (str[1] >='A' &&  str[1] <='F'))){
                QMessageBox::warning(NULL, "错误提示", "有非法字符");
                return;
            }
            char tmp = static_cast<char>(str.toUInt(NULL, 16));
            tx_buf_tmp += tmp;
        }
    } else tx_buf_tmp = tx_buf.toLocal8Bit();   //转换为标准字符，支持中文

    if(cb_send_enter->isChecked())
        tx_buf_tmp += "\n";
    serial->write(tx_buf_tmp);

    int len = lab_txbyte->text().toInt() + tx_buf_tmp.length();
    lab_txbyte->setText(QString::number(len)); 
}

void MySerialWidget::slotUpdateSerialList(){
    QString str = cbb_com->currentText();
    cbb_com->clear();
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
        cbb_com->addItem(info.portName());
    }
    cbb_com->setCurrentText(str);
}
void MySerialWidget::slot_cbb_baud_currentIndexChanged(void){
    if(btn_serial_sw->text() == "关闭串口"){
        serial->setBaudRate(cbb_baud->currentText().toInt());
    }
}
void MySerialWidget::slotSerialSend(const QByteArray &qba){
    if(serial->isOpen())
        serial->write(qba);
   // else QMessageBox::warning(NULL, "错误提示", "没有连接设备");
}
