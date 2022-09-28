#include "mainwindow.h"
#include "data_mem.h"
#include <QApplication>
#include "devicesdr.h"
#include <QDebug>
#include <thread>
#include <QThread>
#include <QScreen>
#include <algorithm>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);    
    MainWindow window;    
    window.show();    
    DeviceSDR device("device-1", 4000);
    Data_mem data_mem(device.getChank_size());
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
