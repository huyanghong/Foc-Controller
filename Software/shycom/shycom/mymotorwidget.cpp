#include "mymotorwidget.h"
#include "QDebug"

MyMotorWidget::MyMotorWidget(QWidget *parent) : QWidget(parent)
{


}
void MyMotorWidget::initUi(QString name, uint8_t obj_id, uint8_t modu_id){
    this->object_id = obj_id;
    this->modular_id = modu_id;

    lab_min = new QLabel("min:");
    lab_max = new QLabel("max:");
    lab_step = new QLabel("微调:");
    lab_set = new QLabel("设定:");

    le_max = new QLineEdit();
    le_min = new QLineEdit();
    le_step = new QLineEdit();
    le_min->setText(QString::number(0));
    le_max->setText(QString::number(1));
    le_step->setText(QString::number(0.001));
    le_max->setMaximumWidth(40);
    le_min->setMaximumWidth(40);
    le_step->setMaximumWidth(50);
    le_max->setMinimumWidth(40);
    le_min->setMinimumWidth(40);
    le_step->setMinimumWidth(50);
    le_max->setValidator(new QDoubleValidator(-2147483647, 2147483647,4, this));
    le_min->setValidator(new QDoubleValidator(-2147483647, 2147483647, 4, this));
    le_step->setValidator(new QDoubleValidator(-2147483647, 2147483647,4, this));

    lab_object_id = new QLabel();
    lab_object_id->setText(name + ": " + QString::number(this->object_id));
    lab_object_id->setStyleSheet("color:red;");

    sb_set = new QDoubleSpinBox();
    sb_set->setMinimum(le_min->text().toFloat());
    sb_set->setMaximum(le_max->text().toFloat());
    sb_set->setSingleStep(le_step->text().toFloat());
    sb_set->setMaximumWidth(80);
    sb_set->setMinimumWidth(70);
    sb_set->setValue(0);
    sb_set->setDecimals(4);

    hs_set = new QSlider();
    hs_set->setOrientation(Qt::Horizontal);
    hs_set->setMinimum(le_min->text().toFloat() * 10000);
    hs_set->setMaximum(le_max->text().toFloat() * 10000);
    hs_set->setValue(0);


    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addWidget(lab_object_id);
    hlayout->addStretch(1);
    hlayout->addWidget(lab_step);
    hlayout->addWidget(le_step);
    hlayout->addWidget(lab_set);
    hlayout->addWidget(sb_set);
    hlayout->addStretch();
    QGridLayout *glayout = new QGridLayout();


    glayout->addLayout(hlayout, 0, 0);
    glayout->addWidget(lab_max, 0, 1);
    glayout->addWidget(le_max, 0, 2);
    glayout->addWidget(lab_min, 1, 1);
    glayout->addWidget(le_min, 1, 2);
    glayout->addWidget(hs_set, 1, 0);


    setLayout(glayout);

    //connect(hs_set, &QSlider::actionTriggered, this, &MyMotorWidget::slotUpdateSpinFormSlider);
    connect(hs_set, &QSlider::valueChanged, this,  &MyMotorWidget::slotUpdateSpinFormSlider);
    connect(sb_set, SIGNAL(valueChanged(double)), this, SLOT(slotUpdateSliderFormSpin()));
    connect(le_max, &QLineEdit::editingFinished, this, &MyMotorWidget::slotLineEditValueChanged);
    connect(le_min, &QLineEdit::editingFinished, this, &MyMotorWidget::slotLineEditValueChanged);
    connect(le_step, &QLineEdit::editingFinished, this, &MyMotorWidget::slotLineEditValueChanged);
}
void MyMotorWidget::slotUpdateSliderFormSpin(void){
    float value = sb_set->text().toFloat();
    hs_set->setValue(value * 10000);

    uint8_t buf[13];
    buf[0] = 0xAA;  buf[1] = 0xAA;
    buf[2] = 13;
    buf[11] = 0xA0;
    buf[12] = 0xA0;
    buf[3] = 33;

    buf[4] = this->modular_id;
    buf[5] = object_id;
    memcpy(&buf[6], &value, 4);
    buf[10] = 0;
    for(int i=3; i <= 9; i++)
        buf[10] += buf[i];

    QByteArray qba_w(13, ' ');
    memcpy(qba_w.data(), buf, 13);
    emit signalWriteParameter(qba_w);
}

void MyMotorWidget::slotUpdateSpinFormSlider(void){
    int value = hs_set->value();
    sb_set->setValue(value / 10000.0);
}
void MyMotorWidget::slotLineEditValueChanged(void){
    sb_set->setMinimum(le_min->text().toFloat());
    sb_set->setMaximum(le_max->text().toFloat());
    hs_set->setMinimum(le_min->text().toFloat() * 10000);
    hs_set->setMaximum(le_max->text().toFloat() * 10000);
    sb_set->setSingleStep(le_step->text().toFloat());
}
