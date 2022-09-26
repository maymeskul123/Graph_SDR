#ifndef DATA_MEM_H
#define DATA_MEM_H
#include <complex>
#include <QThread>
#include <iostream>
#include <valarray>

const double PI = 3.141592653589793238460;
typedef std::complex<float> Complex;
typedef std::valarray<Complex> CArray;

class Data_mem : public QThread
{
    Q_OBJECT
public:   
    explicit Data_mem(int size_data, float rate, float cent_freq);
    ~Data_mem();
    //void set_data(std::complex<float> *ptrArray[]);
    void run();
    //void loadPtrWindow(MainWindow *window);
    float* getDataReal();
    //void fft(CArray& x);
    void fft(CArray& x);
    int getDataSize();
    CArray& getFFT();
    bool chunkReceiveFull;

public slots:
    void receiveValue(std::complex<float> *data[]);
    void chunkFull(bool);
    void receiveStopButton();

private:
    std::complex<float> *dataPtr;
    float centFreq;
    float rate;
    bool isAborted;
    float *realData;
    int size_data;
    CArray dataSpectr;
};

#endif // DATA_MEM_H
