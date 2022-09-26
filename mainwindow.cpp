#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <unistd.h>
#include <QThread>
#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui (new Ui::MainWindow)
{    
    ui->setupUi(this);
    textEdit=ui->textEdit;
    frequency = ui->lineFrequency;
    rate = ui->lineRate;
    gain = ui->lineGain;
    initChart();
    cur_x = 0;
    cur_spectr_x = 0;
    for (int j = 0; j<500; j++)
    {
        *seriesAmplitude << QPointF(j, 0);
        *seriesFourier << QPointF(j, 0);
    }
    timerAmplitude = new QTimer(this);
    connect(timerAmplitude, &QTimer::timeout, [=]() {
        //const Complex test[] = {1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0 };
        CArray& data = dataPtr->getFFT();
//        for (int j = 0; j < dataPtr->getDataSize(); j++)
//        {
//            qDebug() << "data" << data[j].real();
//        }
        float* arrReal = dataPtr->getDataReal();
        //dataPtr->fft(data);
        //data = dataPtr->getFFT();
        int count = 0;
        while (count < 500)
        {
            //series->replace(cur_x, cur_x, arrReal[cur_x]);
            seriesAmplitude->replace(count, count, arrReal[count]);
            seriesFourier->replace(count, count, data[count].real());
            //qDebug() << "data " << res[count].real();
            count++;
        }
    });
}


void MainWindow::initChart()
{
    seriesAmplitude = new QLineSeries();
    seriesAmplitude->setUseOpenGL(true);
    seriesAmplitude->setPen(QPen(Qt::black, 2, Qt::DashLine));
    chartAmplitude = new QChart();
    chartAmplitude->setTitle("Amplitude");
    chartAmplitude->setAnimationOptions(QChart::AllAnimations);
    chartViewAmpl = new QChartView(chartAmplitude);
    chartViewAmpl->setRenderHint(QPainter::Antialiasing);
    chartViewAmpl->setRubberBand(QChartView::RectangleRubberBand);
    ui->verticalLayout->addWidget(chartViewAmpl);
    ui->verticalLayout->setContentsMargins(0,0,0,0);
    chartAmplitude->legend()->hide();
    chartAmplitude->addSeries(seriesAmplitude);
    chartAmplitude->createDefaultAxes();
    chartAmplitude->axisX() ->setRange(0., 500.0);
    chartAmplitude->axisY() ->setRange(-0.05, 0.05);    

    seriesFourier = new QLineSeries();
    seriesFourier->setUseOpenGL(true);
    seriesFourier->setPen(QPen(Qt::yellow, 2, Qt::DashLine));
    seriesFourier->setUseOpenGL(true);
    chartFourier = new QChart();
    chartFourier->setTitle("Spectr");
    chartFourier->setAnimationOptions(QChart::AllAnimations);
    chartViewSpectr = new QChartView(chartFourier);
    chartViewSpectr->setRenderHint(QPainter::Antialiasing);
    chartViewSpectr->setRubberBand(QChartView::RectangleRubberBand);
    chartViewSpectr->setBackgroundBrush(QBrush(Qt::black));
    chartFourier->setBackgroundBrush(QBrush(Qt::black));
    chartFourier->setBackgroundPen(QPen(Qt::white));
    chartFourier->setTitleBrush(QBrush(Qt::white));
    chartFourier->setPlotAreaBackgroundPen(QPen(Qt::white));
    chartFourier->setPlotAreaBackgroundBrush(QBrush(Qt::white));
    ui->verticalLayout->addWidget(chartViewSpectr);
    ui->verticalLayout->setContentsMargins(0,0,0,0);
    //chartFourier->legend()->hide();
    chartFourier->addSeries(seriesFourier);
    chartFourier->createDefaultAxes();
    chartFourier->axisX() ->setRange(0., 500.0);
    chartFourier->axisY() ->setRange(0, 0.5);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startButton_clicked()
{    
    emit startButton();
    startTimer();
}


void MainWindow::on_stopButton_clicked()
{
    emit stopButton();
    timerAmplitude->stop();
}


void MainWindow::startTimer()
{
    timerAmplitude->start(50);
}


void MainWindow::loadData_mem(Data_mem *data)
{
    dataPtr = data;
}
