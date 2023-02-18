#ifndef SERIALPORT_DECODER_H
#define SERIALPORT_DECODER_H

#include <QDebug>
#include <QSemaphore>
#include <QFile>
#include <QDir>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QTime>
#include "ex_qthread.h"
#include <math.h>
#include <iostream>

#include <data_processing.h>
using namespace std;

#define BUFFER_SIZE 65536

class Receiver;
class Decoder;
class SerialPort_Decoder : public QObject
{
    Q_OBJECT
public:
    SerialPort_Decoder();
    ~SerialPort_Decoder();

public:
    void setMainPort(QObject *main, const QString PortName,const QString BaudRate);
    void set_FilePath(const QString Filepath_Ch4);
    void stopRun(void);
//    void startRun(void);

  //  void getrenew(unsigned int rate);

private:
    void startRun(void);
    void creat_FilePath(void);
    void connectToMain(QObject *Main_Obj);






public:
    QSemaphore *emptyBufs;
    QSemaphore *fullBufs;
    uchar *Rec_Buffer_ptr;





    Receiver *receiver;
    Decoder *decoder;
    data_processing *dataProcessing;
};

#endif // SERIALPORT_DECODER_H
