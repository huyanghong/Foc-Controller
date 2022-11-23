#ifndef MYDOCKWIDGET_H
#define MYDOCKWIDGET_H

#include <QDockWidget>

class MyDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit MyDockWidget(QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *event);

signals:
    void signalDockwidgetClose();


public:
    bool isOpen;
};
#endif // MYDOCKWIDGET_H
