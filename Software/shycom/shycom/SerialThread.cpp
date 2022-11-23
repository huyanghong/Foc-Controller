#include "SerialThread.h"
#include "mainwindow.h"

SerialThread::SerialThread(QObject *parent) : QObject(parent)
{
    thread = new QThread(this);
    this->moveToThread(thread);
    connect(thread, &QThread::finished, this, &SerialThread::deleteLater);
    thread->start();

    for(int i=0; i<plot_num; i++)
        param_len[i] = 4;
}
SerialThread::~SerialThread(){
    thread->quit();
    thread->wait();
}
void SerialThread::slotReceiveSerialBuf(const QByteArray &qba){
     serial_buf += qba;
     if(serial_buf.length() >= 8){
         for(int i=0; i<serial_buf.length()-8; i++){
             if(serial_buf.at(i) == (char)0xAA && serial_buf.at(i+1) == (char)0xAA){ //确定帧头
                 uint8_t byte_len = serial_buf.at(i+2);
                 if(byte_len+i <= serial_buf.length()){ //确定帧数据完整
                     if(serial_buf.at(i+byte_len-2)==(char)0xA0 && serial_buf.at(i+byte_len-1)==(char)0xA0){ //确定帧尾
                         int index = i+3;
                         while(index < i+byte_len-3){ //协议解析
                             if((uint8_t)serial_buf.at(index) < plot_num){ //曲线数据
                                 memcpy(&curve_value[(uint8_t)serial_buf.at(index)], serial_buf.data()+index+1,  4);
                                 curve_receive_status = 1;
                             }else{ //其他数据
                                 switch((uint8_t)serial_buf.at(index)){
                                 }
                             }
                             index += param_len[(uint8_t)serial_buf.at(index)] + 1;
                         }

                         if(curve_receive_status) {
                             curve_receive_status = 0;
                             QByteArray Curve(plot_num*4, 'a');
                             memcpy(Curve.data(), curve_value,  plot_num*4);
                             emit signalSendCurvePoint(Curve);
                         }

                         serial_buf.remove(0, i+byte_len-1);
                         i = 0;
                         if(serial_buf.length() <= 8)
                             return;
                     }
                 }
             }
         }
     }

    if(serial_buf.length() > 512)
        serial_buf.remove(0, serial_buf.length() - 512);
}
