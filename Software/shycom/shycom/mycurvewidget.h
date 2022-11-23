#ifndef MYCURVEWIDGET_H
#define MYCURVEWIDGET_H

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
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_legend.h>
#include <qwt_point_data.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_zoomer.h>

#define plot_num 10

class MyCurveWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyCurveWidget(QWidget *parent = nullptr);

signals:

public slots:
    void slotBtnCurveShow(void);
    void slotCurvePlotShow(void);
    void slotCurveClear(void);
    void slotReceiveCurvePoint(const QByteArray &qba);

public:
    QwtPlot *curvePlot;
    QCheckBox *cb_curve[plot_num];
    QCheckBox *cb_auto_adaption;
    QPushButton *btn_curve_show;
    QPushButton *btn_curve_clear;
    QLineEdit *te_curve_size_X;
    QVector<QPointF> curve_vector[plot_num];
    int frame_cnt = 0;
    QwtPlotCurve curve[plot_num];
    QPen curve_color[plot_num];
    float window_min_Y, window_max_Y;
};

#endif // MYCURVEWIDGET_H
