#include "ex_qthread.h"

EX_QThread::EX_QThread()
{
    Run_stopped = false;

    m_emptyBufs = NULL;
    m_fullBufs = NULL;
    m_Rec_Buffer = NULL;

    Writer_Ptr = 0;
    Reader_Ptr = 0;
    Pre_reader_Ptr = 0;

    m_FilePath_CH1.clear();
    m_FilePath_CH2.clear();
    m_FilePath_CH3.clear();

    m_PortName.clear();
    m_BaudRate.clear();

    exists_CH1 = false;
    exists_CH2 = false;
    exists_CH3 = false;
}

EX_QThread::~EX_QThread()
{
}

void EX_QThread::set_Rec_Buffer_ptr(uchar *x_Rec_Buffer)
{
    m_Rec_Buffer = x_Rec_Buffer;
}

void EX_QThread::set_emptyBufs_ptr(QSemaphore *emptyBufs)
{
    m_emptyBufs = emptyBufs;
}

void EX_QThread::set_fullBufs_ptr(QSemaphore *fullBufs)
{
    m_fullBufs = fullBufs;
}

void EX_QThread::getrenew(unsigned int rate)
{
    renew_rate = rate;
    qDebug()<<"renew_rate"<<renew_rate;
}
