#ifndef MYTIMER_H
#define MYTIMER_H

#include <QObject>
#include <QTimer>

class MyTimer : public QObject
{
    Q_OBJECT
public:
    //explicit MyTimer(QObject *parent = nullptr);
    MyTimer();
    QTimer *timer;

//signals:
public slots:
    void MyTimerSlot();
};

#endif // MYTIMER_H
