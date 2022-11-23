#include "mycurvewidget.h"

MyCurveWidget::MyCurveWidget(QWidget *parent) : QWidget(parent)
{
    curvePlot = new QwtPlot();
    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setPen(QPen(Qt::gray));
    grid->attach(curvePlot);
    curvePlot->setCanvasBackground(QColor(100, 100, 100));

    window_min_Y = 0;
    window_max_Y = 1;

    for(int i=0; i<plot_num; i++)
        cb_curve[i] = new QCheckBox("数据"+QString::number(i));

    cb_curve[0]->setStyleSheet("QCheckBox {color:red}");
    cb_curve[1]->setStyleSheet("QCheckBox {color:green}");
    cb_curve[2]->setStyleSheet("QCheckBox {color:blue}");
    cb_curve[3]->setStyleSheet("QCheckBox {color:yellow}");
    cb_curve[4]->setStyleSheet("QCheckBox {color:darkRed}");
    cb_curve[5]->setStyleSheet("QCheckBox {color:darkGreen}");
    cb_curve[6]->setStyleSheet("QCheckBox {color:darkBlue}");
    cb_curve[7]->setStyleSheet("QCheckBox {color:darkCyan}");
    cb_curve[8]->setStyleSheet("QCheckBox {color:darkMagenta}");
    cb_curve[9]->setStyleSheet("QCheckBox {color:darkYellow}");

    curve_color[0] = QPen(Qt::red);
    curve_color[1] = QPen(Qt::green);
    curve_color[2] = QPen(Qt::blue);
    curve_color[3] = QPen(Qt::yellow);
    curve_color[4] = QPen(Qt::darkRed);
    curve_color[5] = QPen(Qt::darkGreen);
    curve_color[6] = QPen(Qt::darkBlue);
    curve_color[7] = QPen(Qt::darkCyan);
    curve_color[8] = QPen(Qt::darkMagenta);
    curve_color[9] = QPen(Qt::darkYellow);

    btn_curve_show = new QPushButton("开始显示");
    btn_curve_clear = new QPushButton("清空缓存");
    te_curve_size_X = new QLineEdit("500");
    QLabel *lab_curve_X = new QLabel("显示长度:");
    cb_auto_adaption = new QCheckBox("自适应高度");
    cb_auto_adaption->setChecked(true);
    te_curve_size_X->setMaximumWidth(60);
    curvePlot->setMinimumHeight(100);

    //**************UI设计*******************//
    QGridLayout *glayout = new QGridLayout();
    for(int i=0; i<plot_num; i++){
        glayout->addWidget(cb_curve[i], 0, i);
    }

    QHBoxLayout *hlayout1 = new QHBoxLayout();
    hlayout1->addLayout(glayout);
    hlayout1->addStretch();

    QHBoxLayout *hlayout2 = new QHBoxLayout();
    hlayout2->addStretch();
    hlayout2->addWidget(lab_curve_X);
    hlayout2->addWidget(te_curve_size_X);
    hlayout2->addWidget(cb_auto_adaption);
    hlayout2->addWidget(btn_curve_clear);
    hlayout2->addWidget(btn_curve_show);

    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addWidget(curvePlot);
    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout2);

    setLayout(vlayout);

    slotCurvePlotShow();

    //**************信号-槽连接*****************//
    connect(btn_curve_show, &QPushButton::clicked, this, &MyCurveWidget::slotBtnCurveShow);
    connect(btn_curve_clear, &QPushButton::clicked, this, &MyCurveWidget::slotCurveClear);
    connect(te_curve_size_X, &QLineEdit::textChanged, this, &MyCurveWidget::slotCurvePlotShow);
    for(int i=0; i<plot_num; i++)
        connect(cb_curve[i], &QCheckBox::clicked, this, &MyCurveWidget::slotCurvePlotShow);

    curvePlot->setMouseTracking(true);
    QwtPlotMagnifier *magnif = new QwtPlotMagnifier(curvePlot->canvas()); //使用滚轮放大/缩小
    magnif->setMouseButton(Qt::MidButton);
    QwtPlotPanner *panner = new QwtPlotPanner(curvePlot->canvas());                                   //默认的左键移动功能
    panner->setMouseButton( Qt::RightButton );        //设置哪个按钮移动画布  如果不设置(注册掉当前行)按钮默认为左键为移动

    QwtPlotZoomer *zoomer = new QwtPlotZoomer(curvePlot->canvas());                     //选择图形局部放大
    zoomer->setRubberBandPen( QColor( Qt::blue ) ); //勾选扩大区域边界颜色
    zoomer->setMousePattern( QwtEventPattern::MouseSelect2, Qt::MidButton, Qt::ControlModifier );//ctrl+右键==回复到原始状态
    zoomer->setMousePattern( QwtEventPattern::MouseSelect3, Qt::MidButton );

}

void MyCurveWidget::slotCurveClear(void){
    frame_cnt = 0;
    for(int i=0;i<plot_num;i++){
        curve_vector[i].clear();
        QwtPointSeriesData *series = new QwtPointSeriesData(curve_vector[i]);
        curve[i].setData(series);
        curve[i].attach(curvePlot);
    }
    window_min_Y = 0;
    window_max_Y = 1;
    slotCurvePlotShow();
}
void MyCurveWidget::slotBtnCurveShow(void){
    if(btn_curve_show->text() == "开始显示"){
            btn_curve_show->setText("暂停显示");
    }else {
        btn_curve_show->setText("开始显示");
    }
}

void MyCurveWidget::slotCurvePlotShow(void){
    for(int i=0;i<plot_num;i++){
        if(cb_curve[i]->isChecked()){
            QwtPointSeriesData *series = new QwtPointSeriesData(curve_vector[i]);
            curve[i].setData(series);
            curve[i].attach(curvePlot);
            curve[i].setPen(curve_color[i]);
        }else {
            QVector<QPointF> temp;
            QwtPointSeriesData *series = new QwtPointSeriesData(temp);
            curve[i].setData(series);
            curve[i].attach(curvePlot);
            curve[i].setPen(curve_color[i]);
        }
    }

    int len = te_curve_size_X->text().toInt();
    int start_X, stop_X;
    if(frame_cnt > len){
        start_X = frame_cnt - len;
        stop_X = frame_cnt;
    }else {
        start_X = 0;
        stop_X = len;
    }

    window_max_Y = -1000000000;
    window_min_Y =  1000000000;
    int s;
    if(cb_auto_adaption->isChecked()) s = start_X;
    else s = 0;
    for(int i=0;i<plot_num;i++){
        if(cb_curve[i]->isChecked()){
            for(int j=s; j < curve_vector[i].length(); j++){
                if(window_max_Y < curve_vector[i][j].ry()) window_max_Y = curve_vector[i][j].ry();
                if(window_min_Y > curve_vector[i][j].ry()) window_min_Y = curve_vector[i][j].ry();
            }
        }
    }
    if(window_min_Y > window_max_Y){
        window_min_Y = 0;
        window_max_Y = 1;
	}
    else if(window_min_Y == window_max_Y){
        window_min_Y -= 1;
        window_max_Y += 1;
	}
    float step_Y;
    unsigned int step_X;
    int w = curvePlot->width();
    int h = curvePlot->height();
    if(h == 0) h = 1;
    step_X = 60 * (stop_X - start_X) / w;
    step_Y = 20 * (window_max_Y - window_min_Y) / h;
int y = 1000 * step_Y;
step_Y = y / 1000;
    curvePlot->setAxisScale(QwtPlot::yLeft, window_min_Y, window_max_Y, step_Y);
    curvePlot->setAxisScale(QwtPlot::xBottom, start_X, stop_X, step_X) ;
    curvePlot->replot();
    //curvePlot->show();
}
void MyCurveWidget::slotReceiveCurvePoint(const QByteArray &qba){
    if(btn_curve_show->text() == "开始显示") return;
    float temp[plot_num];
    memcpy(temp, qba.data(), 40);
    for(int k=0;k<plot_num;k++){
         QPointF point;
         point.setX(frame_cnt);
         point.setY(temp[k]);
         curve_vector[k].append(point);
     }
     frame_cnt++;
     slotCurvePlotShow();
}
