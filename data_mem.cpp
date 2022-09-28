#include "data_mem.h"
#include <QDebug>
#include <vector>
#include <algorithm>
#include <iostream>
#include <math.h>

//typedef std::complex<float> Complex;
typedef std::valarray<Complex> CArray;

Data_mem::Data_mem(int size_data_)
{
    isAborted = false;
    dataPtr = new std::complex<float> [size_data_];
    realData = new float[size_data_];
    size_data = size_data_;
    chunkReceiveFull = false;
}

Data_mem::~Data_mem()
{

}

void Data_mem::run()
{
    //qDebug() << "data" << QThread::currentThreadId();
    while (!isAborted) {

    }
    //qDebug() << "Data mem isAborted";
    quit();
}

void Data_mem::receiveValue(std::complex<float> *data[])
{    
    memcpy(dataPtr, data, size_data);
    for (int i = 0; i < size_data; i++)
        {
            realData[i] = reinterpret_cast<float(&)[2]>(dataPtr[i])[0];
        }
    //qDebug() << "Size real" << size_t(realData);
}


void Data_mem::chunkFull(bool flag)
{

}


void Data_mem::setDataSession(float centrFreq_, float rate_, float gain_)
{
    rate = rate_;
    centrFreq = centrFreq_;
    gain = gain_;
}


void Data_mem::receiveStopButton()
{
    //qDebug() << "Receive Stop Button!";
    isAborted = true;
}


float* Data_mem::getDataReal()
{
    return (float *)realData;
}


void Data_mem::fft(CArray& x)
{
    const size_t N = x.size();
    if (N <= 1) return;

        // divide
    CArray even = x[std::slice(0, N/2, 2)];
    CArray  odd = x[std::slice(1, N/2, 2)];

        // conquer
    fft(even);
    fft(odd);

        // combine
    for (size_t k = 0; k < N/2; ++k)
    {
        //Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
        //Complex t = std::polar(1.0, -2 * 3.1415926 * k / N) * static_cast<std::complex<double>>(odd[k]);
        std::complex<double> t = std::polar(1.0, -2 * PI * k / N) * static_cast<std::complex<double>>(odd[k]);
        x[k    ] = even[k] + static_cast<std::complex<float>>(t);
        x[k+N/2] = even[k] - static_cast<std::complex<float>>(t);
    }
}


CArray& Data_mem::getFFT()
{
        CArray d(dataPtr, size_data);
        dataSpectr = d;
        CArray &x = dataSpectr;
//        CArray c(dataPtr, size_data);
//        CArray &y = c;
//        for (auto it = begin(x); it!=end(x); ++it)
//        {
//            qDebug() << "before" << it->real();
//        }
        fft(x);
        //x = abs(x);
        x = abs(20 * log10(x));
//        for (int j = 0; j < size_data; j++)
//        {
//            qDebug() << "before" << x[j].real()<< "after" << d[j].real();
//        }
        return dataSpectr;
}


int Data_mem::getDataSize()
{
    return size_data;
}


float Data_mem::getCentrFreq()
{
    return centrFreq;
}


float Data_mem::getRate()
{
    return rate;
}


float Data_mem::getGain()
{
    return gain;
}
