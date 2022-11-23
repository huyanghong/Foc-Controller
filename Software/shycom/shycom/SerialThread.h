#ifndef SERIAL_THREAD_H
#define SERIAL_THREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QMessageBox>
#include <QTextBrowser>
#include <QByteArray>

class SerialThread : public QObject
{
    Q_OBJECT
public:
    explicit SerialThread(QObject *parent = nullptr);
    ~SerialThread();

signals:
    void signalSendModelPose(const float *q);
    void signalSendCurvePoint(const QByteArray &qba);
    void signalSendSquareWaveFreq(const uint16_t *f);

public slots:
    void slotReceiveSerialBuf(const QByteArray &qba);

public:
    QThread *thread;
    QByteArray serial_buf;
    uint8_t param_len[256];

    float curve_value[16];
    uint8_t curve_receive_status = 0;

};

#endif // SERIAL_THREAD_H
