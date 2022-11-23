#ifndef MYMOTORWIDGET_H
#define MYMOTORWIDGET_H

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

class MyMotorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyMotorWidget(QWidget *parent = nullptr);

signals:
    void signalWriteParameter(const QByteArray &qba);

public slots:
    void slotUpdateSliderFormSpin();
    void slotUpdateSpinFormSlider();
    void slotLineEditValueChanged();

public:
    uint8_t modular_id, object_id;
    QLabel *lab_min, *lab_max, *lab_step, *lab_set;
    QLineEdit *le_min, *le_max, *le_step;
    QDoubleSpinBox  *sb_set;
    QSlider *hs_set;
    QLabel *lab_object_id;

    void initUi(QString name, uint8_t obj_id, uint8_t modu_id);
};
#endif // MYMOTORWIDGET_H


