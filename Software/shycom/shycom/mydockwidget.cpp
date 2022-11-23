#include "mydockwidget.h"
#include <QDebug>

MyDockWidget::MyDockWidget(QWidget *parent): QDockWidget(parent)
{
    isOpen = true;
}

void MyDockWidget::closeEvent(QCloseEvent *event){
    isOpen = false;
    emit signalDockwidgetClose();
}
