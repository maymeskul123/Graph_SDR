#include "mainwindow.h"
#include "data_mem.h"
#include <QApplication>
#include "mytimer.h"
#include "devicesdr.h"
#include <QDebug>
#include <thread>
#include <QThread>
#include <QScreen>
#include <algorithm>



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //app.widgetAt(500, 100);
    //QScreen *primaryScreen = QGuiApplication::primaryScreen();
    // qDebug() << "app" << QThread::currentThreadId();
    //qDebug() << "resolution" << primaryScreen->availableVirtualGeometry();
    //qDebug() << "size" << primaryScreen->availableVirtualSize();
    //QList<QScreen *> scr = app.screens();
    //qDebug() << "resolution" << scr[0]->geometry() << scr[1]->geometry();
    //QScreen *scr1
    MainWindow window;    
    window.show();    
    DeviceSDR device("device-1", 4000);
    Data_mem data_mem(device.getChank_size());

    //qDebug() << "Fmin" << fCentr - (rate/2);
    //qDebug() << "Fmax" << fCentr + (rate/2);

//    auto v = data_mem.linspace(0,1,11);
//    for (auto a : v) {
//        qDebug() << a << '\n';
//    }
    //data_mem.loadPtrWindow(&window);
    data_mem.start();
    window.loadData_mem(&data_mem);
    app.connect(&window, SIGNAL(startButton(Data_mem*)), &device, SLOT(receiveStart(Data_mem*)));
    app.connect(&window, SIGNAL(stopButton()), &device, SLOT(receiveStop()));
    //app.connect(&device, &DeviceSDR::send_value, &window, &MainWindow::receiveVal);
    app.connect(&device, &DeviceSDR::send_value, &data_mem, &Data_mem::receiveValue);
    app.connect(&device, &DeviceSDR::send_chunkFull, &data_mem, &Data_mem::chunkFull);
    app.connect(&window, SIGNAL(stopButton()), &data_mem, SLOT(receiveStopButton()));
    //MyTimer timer;
    return app.exec();
}
