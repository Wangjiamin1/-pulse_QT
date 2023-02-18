#ifndef EX_QTHREAD_H
#define EX_QTHREAD_H

#include <QThread>
#include <QSemaphore>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>

class EX_QThread : public QThread
{
    Q_OBJECT

public:
    EX_QThread();
    ~EX_QThread();

    void set_Rec_Buffer_ptr(uchar *x_Rec_Buffer);
    void set_emptyBufs_ptr(QSemaphore *);
    void set_fullBufs_ptr(QSemaphore *);

public slots:
     void getrenew(unsigned int rate);

signals:
    void sendOneSecData(qint16 oneSec_CH1, qint16 oneSec_CH2, qint16 oneSec_CH3);
    void sendTenSecData(float tenSec_CH1, float tenSec_CH2, float tenSec_CH3);
    void sendciadd(float oneSec_CH1, float oneSec_CH2, float oneSec_CH3);
    void sendOneSecAllDate(float*,bool);
   // void sendPre_Decoder(uchar *pack);
public:
    volatile bool Run_stopped;
    volatile bool flagCheck;
    unsigned int renew_rate=1000;

    QString m_FilePath_CH1;
    QString m_FilePath_CH2;
    QString m_FilePath_CH3;
    QString m_FilePath_CH4;


    volatile bool exists_CH1;
    volatile bool exists_CH2;
    volatile bool exists_CH3;
    volatile bool exists_CH4;

    QSemaphore *m_emptyBufs;
    QSemaphore *m_fullBufs;
    uchar *m_Rec_Buffer;

    quint16 Writer_Ptr;
    quint16 Reader_Ptr;
    quint16 Pre_reader_Ptr;

    QString m_PortName;
    QString m_BaudRate;
};

#endif // EX_QTHREAD_H
