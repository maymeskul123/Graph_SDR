#include <QDebug>
#include <QThread>
#include <unistd.h>
#include <QString>
#include <typeinfo>
#include "devicesdr.h"
#include <complex>


DeviceSDR::DeviceSDR(QString threadName, int chankSize) :
    name(threadName)
{    
    chank_size = chankSize;    
    isAborted = false;
}


void DeviceSDR::setup_SDR()
{
    SoapySDR::KwargsList results = SoapySDR::Device::enumerate();
    SoapySDR::Kwargs::iterator it;

        for( int i = 0; i < results.size(); ++i)
        {
            printf("Found device #%d: ", i);
            for( it = results[i].begin(); it != results[i].end(); ++it)
            {
                printf("%s = %s\n", it->first.c_str(), it->second.c_str());
            }
            printf("\n");
        }
//         1. create device instance

//            1.1 set arguments
//                args can be user defined or from the enumeration result
//                We use first results as args here:
        SoapySDR::Kwargs args = results[0];

        //	1.2 make device
        sdr = SoapySDR::Device::make(args);        
        sdr->setFrequency(SOAPY_SDR_RX, 0, centrFreq);
        sdr->setSampleRate(SOAPY_SDR_RX, 0, rate);
        sdr->setAntenna(SOAPY_SDR_RX, 0, "LNAL");
        sdr->setGain(SOAPY_SDR_RX, 0, gain);
        rx_stream = sdr->setupStream( SOAPY_SDR_RX, SOAPY_SDR_CF32);
        sdr->activateStream(rx_stream);
}


void DeviceSDR::run()
{
    //qDebug() << "thread in run" << QThread::currentThreadId();
    receive_signal();
}


void DeviceSDR::stop_rcv()
{

}


void DeviceSDR::receive_signal()
{
    isAborted = true;
    std::complex <float> *buff[chank_size];
    void *buffs[] = {buff};
    int flags;
    long long time_ns;
    //qDebug() << "device" << QThread::currentThreadId();
    while (isAborted)
    {
        int ret = sdr->readStream(rx_stream, buffs, chank_size, flags, time_ns, 1e6);
        //printf("ret = %d, flags = %d, time_ns = %lld\n", ret, flags, time_ns);

        //emit send_value(reinterpret_cast<float(&)[2]>(buff[0])[0]);
       //usleep(5000);
        //minmax = std::minmax_element(std::begin())

//        for (int i = 0; i < ret; i++)
//        {
//            //qDebug() << reinterpret_cast<float(&)[2]>(buff[i])[0] << reinterpret_cast<float(&)[2]>(buff[i])[1];
          //usleep(3000);
        // << reinterpret_cast<float(&)[2]>(buff[0])[0];
        emit send_value(buff);
        //buffs[0] = {};
    }    
    sdr->deactivateStream(rx_stream, 0, 0);	//stop streaming
    sdr->closeStream(rx_stream);
    SoapySDR::Device::unmake(sdr);    
    quit();
}


DeviceSDR::~DeviceSDR()
{
    delete data;
    delete sdr;
    //delete rx_stream;
}


void DeviceSDR::receiveStart(Data_mem *ptrDataMem)
{
    //qDebug() << "START RECEIVE";
    centrFreq = ptrDataMem->getCentrFreq();
    gain = ptrDataMem->getGain();
    rate = ptrDataMem->getRate();
    setup_SDR();
    start();
}


void DeviceSDR::receiveStop()
{
    //qDebug() << "STOP!!!";
    isAborted = false;
}


void DeviceSDR::finished()
{
    qDebug() << "I am finished!";
}


int DeviceSDR::getChank_size()
{
    return chank_size;
}


float DeviceSDR::getRate()
{
    return rate;
}


float DeviceSDR::getCentrFreq()
{
    return centrFreq;
}

