#include "mytimer.h"
#include <QDebug>

MyTimer::MyTimer()
{
    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()),
            this, SLOT(MyTimerSlot()));
    timer->start(100);
}

void MyTimer::MyTimerSlot()
{
    qDebug() << "Timer ...";
}
