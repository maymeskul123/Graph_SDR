#ifndef DEVICESDR_H
#define DEVICESDR_H
#include <SoapySDR/Device.hpp>
#include <SoapySDR/Device.hpp>
#include <SoapySDR/Types.hpp>
#include <SoapySDR/Formats.hpp>
#include "data_mem.h"
#include <QThread>
#include <complex>
#include <vector>


class DeviceSDR : public QThread
{    
    Q_OBJECT
public:
    explicit DeviceSDR(QString threadName, int chankSize);
    bool isAborted;
    ;
    Data_mem *data;
    SoapySDR::Device *sdr;
    SoapySDR::Stream *rx_stream;    
    //std::vector<std::complex <float>> *buff;

    ~DeviceSDR();
    void run();
    void receive_signal();
    void stop_rcv();
    void setup_SDR();
    int getChank_size();
    float getRate();
    float getCentrFreq();
    //void load_data(Data_mem data);
private slots:
    void finished();
public slots:
    void receiveStart(Data_mem *ptrDataMem);
    void receiveStop();
signals:
    void send_value(std::complex <float> *sendBuff[]);
    void send_chunkFull(bool);
private:
    QString name;
    int chank_size;
    float rate;
    float centrFreq;
    float gain;
};

#endif // DEVICESDR_H
