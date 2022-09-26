#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "data_mem.h"
#include "qtextedit.h"
#include <QMainWindow>
#include <complex>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initChart();
    void drawLine();
    //QLineSeries* addSeries(std::complex<float> *data[], QLineSeries *series);
    QTextEdit *textEdit;
    QLineSeries *seriesAmplitude;
    QLineSeries *seriesFourier;
    Data_mem *dataPtr;
    QLineEdit *frequency;
    QLineEdit *rate;
    QLineEdit *gain;
    QList<QPointF> dataXY;

    int x, y, cur_x, cur_spectr_x;
    void startTimer();
    void loadData_mem(Data_mem *data);
    std::vector<float> linspace(float start, float end, int count);

//public slots:
//    void receive_complex(std::complex<float>);

private slots:
    void on_startButton_clicked();
    void on_stopButton_clicked();

public slots:
    //void receiveVal(std::complex<float> *data[]);

signals:
    void startButton();
    void stopButton();

private:
    Ui::MainWindow *ui;
    QChart *chartAmplitude;
    QChart *chartFourier;
    QChartView *chartViewAmpl;
    QChartView *chartViewSpectr;
    QTimer *timerAmplitude;
};
#endif // MAINWINDOW_H
