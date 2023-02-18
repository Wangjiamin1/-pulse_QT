#include "serialport_decoder.h"


class Receiver : public EX_QThread
{
public:
    void run() Q_DECL_OVERRIDE
    {
        volatile bool currentPortNameChanged = true;
        volatile bool currentBaudRateChanged = true;

        QSerialPort *serial = new QSerialPort();
        char *Rec_Temp = new char[9192];

        int Rec_len = 0;
        Run_stopped = false;

        while (!Run_stopped)
        {
            if (currentPortNameChanged||currentBaudRateChanged)
            {
                serial->close();
                serial->setPortName(m_PortName);
                qDebug()<<m_PortName;
                serial->setBaudRate(m_BaudRate.toInt());
                qDebug()<<m_BaudRate.toInt();
               // serial->setBaudRate(460800);
                serial->setParity(QSerialPort::NoParity);
                serial->setDataBits(QSerialPort::Data8);
                serial->setStopBits(QSerialPort::OneStop);
                serial->setReadBufferSize(BUFFER_SIZE);

                if (!serial->open(QIODevice::ReadWrite))
                {
                    delete serial;
                    delete [] Rec_Temp;
                    return;
                }

                currentPortNameChanged = false;
                currentBaudRateChanged = false;
            }
            else
            {
//                if(buff[0]==0x7E)
//                {
//                    //serial->write(buff,5);
//                }
                if (serial->waitForReadyRead(1))
                {
                    Rec_len = serial->read(Rec_Temp, 9192);
                    //cout<<"Rec_len:"<<Rec_len<<endl;


                    if (m_emptyBufs->tryAcquire(Rec_len))
                    {
                        for (int i=0; i<Rec_len;i++)
                        {

                            m_Rec_Buffer[Writer_Ptr++] = (uchar)Rec_Temp[i];
                        }
                         m_fullBufs->release(Rec_len);

//                        qDebug()<<"Writer_ptr:"<<Writer_Ptr;
                    }
                    else
                    {
                        usleep(1);

                        if (Run_stopped)
                            break;
                    }
                }

                usleep(1);
            }
        }

        serial->close();
        delete serial;
        delete [] Rec_Temp;
        Run_stopped = true;
    }
};



    class Decoder : public EX_QThread
    {
    public:
        void run() Q_DECL_OVERRIDE
        {

            uchar Pre_Decoder[53] = {0};
            int badFrame=0;


            float oneSecAllData[24]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            float oneSecAllData1[24]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};



            qint32 oneSecCnt = 0;


            quint8 checkSum = 0;
            quint8 preCheckSum = 0;

            Run_stopped = false;
            flagCheck = true;

            while (!Run_stopped)
            {
                //qDebug()<<Writer_Ptr<<Reader_Ptr;

                if (m_fullBufs->tryAcquire(53))
                {
//                    qDebug()<<"Reader_Ptr:"<<Reader_Ptr;

                    Pre_reader_Ptr = Reader_Ptr;

                    Pre_Decoder[0] = m_Rec_Buffer[Pre_reader_Ptr++];

                    if (Pre_Decoder[0] == (uchar)0xAA)
                    {
                        Pre_Decoder[1] = m_Rec_Buffer[Pre_reader_Ptr++];

                        if((Pre_Decoder[1] == (uchar)0x55))
                        {
                            // qDebug()<<"TIME4"<< QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
                            for(int s=2; s<53;s++)
                            {
                                Pre_Decoder[s] = m_Rec_Buffer[Pre_reader_Ptr++];
                            }
                            checkSum = Pre_Decoder[52];

                            if(flagCheck){
                                preCheckSum = checkSum-1;

                            }
                            flagCheck=false;

//                            if(true)
                            if (checkSum==quint8(preCheckSum+1))//校验和
                           {
                               preCheckSum++;
                               for(int i=0;i<8;i++){
                                   oneSecAllData[i]+=(qint16(Pre_Decoder[3+2*i]<<8)+qint16(Pre_Decoder[2+2*i]));
                                   oneSecAllData[i+8]+=(qint16(Pre_Decoder[19+2*i]<<8)+qint16(Pre_Decoder[18+2*i]));
                                   oneSecAllData[i+16]+=(qint16(Pre_Decoder[35+2*i]<<8)+qint16(Pre_Decoder[34+2*i]));
                               }


                               oneSecCnt++;
                               //qDebug()<<oneSecCnt;
                               if (oneSecCnt== 1000){
                                   for(int i=0;i<24;i++){
                                       oneSecAllData1[i] = oneSecAllData[i];
                                   }
                                   emit sendOneSecAllDate(oneSecAllData1,true);

                                   oneSecCnt = 0;
//                                   tenSecCnt++;

                                   for (int i=0;i<24;i++) {
                                       oneSecAllData[i]=0;
                                   }



                               }

                               Reader_Ptr = Pre_reader_Ptr;
                               m_emptyBufs->release(53);


                           }
                           else
                           {
                               qDebug()<<"bad frame:"<<badFrame++;
                               for(int i=0;i<53;i++){
                                   cout<<hex<<(int)Pre_Decoder[i]<<" ";
                               }
                               cout<<endl;
                               preCheckSum = checkSum;
                               Reader_Ptr+=2;

                               m_fullBufs->release(51);//52
                               m_emptyBufs->release(2);//1
                           }



                        }
                        else {
//                            qDebug()<<"bad frame:"<<badFrame++;
                            Reader_Ptr++;
                            m_fullBufs->release(52);
                            m_emptyBufs->release(1);
                        }

                    }
                    else
                    {
//                        qDebug()<<"bad frame:"<<badFrame++;
                        Reader_Ptr++;

                        m_fullBufs->release(52);//1
                        m_emptyBufs->release(1);//28
                    }
                }
            }
            Run_stopped = false;
        }
    };






SerialPort_Decoder::SerialPort_Decoder()
{
    Rec_Buffer_ptr = new uchar[BUFFER_SIZE];

    emptyBufs = new QSemaphore(BUFFER_SIZE);
    fullBufs = new QSemaphore(0);

    receiver = new Receiver();
    receiver->set_Rec_Buffer_ptr(Rec_Buffer_ptr);
    receiver->set_emptyBufs_ptr(emptyBufs);
    receiver->set_fullBufs_ptr(fullBufs);

    decoder = new Decoder();
    decoder->set_Rec_Buffer_ptr(Rec_Buffer_ptr);
    decoder->set_emptyBufs_ptr(emptyBufs);
    decoder->set_fullBufs_ptr(fullBufs);

    dataProcessing = new data_processing();
}

SerialPort_Decoder::~SerialPort_Decoder()
{
    stopRun();

    delete receiver;
    delete decoder;
    delete dataProcessing;
    delete emptyBufs;
    delete fullBufs;
    delete [] Rec_Buffer_ptr;
}

void SerialPort_Decoder::startRun()
{
//    receiver->start(QThread::TimeCriticalPriority);
//    decoder->start(QThread::TimeCriticalPriority);
//    dataProcessing->start(QThread::TimeCriticalPriority);
    receiver->start();
    decoder->start();
    dataProcessing->start();
}

void SerialPort_Decoder::creat_FilePath()
{
    QDir *dir = new QDir();

    if (dir->mkpath(dataProcessing->m_FilePath_CH4))
        dataProcessing->exists_CH4 = true;
    else
        dataProcessing->exists_CH4 = false;
    delete dir;

    this->startRun();
}

void SerialPort_Decoder::connectToMain(QObject *Main_Obj)
{

    QObject::connect(Main_Obj, SIGNAL(sendrenew(unsigned int)),
                    decoder, SLOT(getrenew(unsigned int)),Qt::QueuedConnection);
    QObject::connect(decoder, SIGNAL(sendOneSecAllDate(float*,bool)),
                    dataProcessing, SLOT(getOneSecAllData(float*,bool)),Qt::QueuedConnection);
    QObject::connect(dataProcessing, SIGNAL(sendToShowData(float*,float*,float*,float*,float*,float*)),
                    Main_Obj, SLOT(getToShowData(float*,float*,float*,float*,float*,float*)),Qt::QueuedConnection);
    QObject::connect(dataProcessing, SIGNAL(sendToPlotOneSec(float*)),
                    Main_Obj, SLOT(attachOneSecCurveSamples(float*)),Qt::QueuedConnection);
    QObject::connect(dataProcessing, SIGNAL(sendToPlotTenSec(float*)),
                    Main_Obj, SLOT(attachTenSecCurveSamples(float*)),Qt::QueuedConnection);
    QObject::connect(dataProcessing, SIGNAL(sendToPlotHundredSec(float*)),
                    Main_Obj, SLOT(attachciadd(float*)),Qt::QueuedConnection);
}

void SerialPort_Decoder::stopRun()
{
    qDebug()<<"three";
    receiver->Run_stopped = true;
    qDebug()<<"four";
    receiver->wait();
    qDebug()<<"five";
    decoder->Run_stopped = true;
    qDebug()<<"six";
    decoder->wait();
    qDebug()<<"seven";
    dataProcessing->Run_stopped = true;
    dataProcessing->quit();
    dataProcessing->wait(500);

}

//void SerialPort_Decoder::getrenew(unsigned int rate)
//{
//    renew_rate = rate;
//    qDebug()<<"renew_rate"<<renew_rate;
//}

void SerialPort_Decoder::setMainPort(QObject *main, const QString PortName, const QString BaudRate)
{
    receiver->m_PortName.clear();
    receiver->m_PortName = PortName;

    receiver->m_BaudRate.clear();
    receiver->m_BaudRate = BaudRate;

    this->connectToMain(main);
    this->creat_FilePath();
}

void SerialPort_Decoder::set_FilePath(const QString FilePath_CH4)
{
//    decoder->m_FilePath_CH1.clear();
//    decoder->m_FilePath_CH2.clear();
//    decoder->m_FilePath_CH3.clear();
    dataProcessing->m_FilePath_CH4.clear();

//    decoder->m_FilePath_CH1 = FilePath_CH1;
//    decoder->m_FilePath_CH2 = FilePath_CH2;
//    decoder->m_FilePath_CH3 = FilePath_CH3;
    dataProcessing->m_FilePath_CH4 = FilePath_CH4;
}
