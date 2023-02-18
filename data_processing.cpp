#include "data_processing.h"


data_processing::data_processing()
{
    oneSecStdDeviation = new float[24];
    tenSecStdDeviation = new float[24];
    hundredSecStdDeviation = new float[24];
    oneSecMean = new float[24];
    tenSecMean = new float[24];
    hundredSecMean = new float[24];
    tenData = new float[24];
    hundredData = new float[24];
    rawData = new float[24];
    Run_stopped = false;
    initData();

}

data_processing::~data_processing(){
    delete [] oneSecStdDeviation;
    delete [] tenSecStdDeviation;
    delete [] hundredSecStdDeviation;
    delete [] oneSecMean;
    delete [] tenSecMean;
    delete [] hundredSecMean;
    delete [] tenData;
    delete [] hundredData;
    delete [] rawData;
}

void data_processing::getOneSecAllData(float * rawData,bool calculatFlag){
    for(int i=0;i<24;i++){
        this->rawData[i] = rawData[i];
    }

    this->calculatFlag = calculatFlag;

}


void data_processing::initData()
{
    for (int i=0;i<24;i++){
        oneSecStdDeviation[i] = 0;
        tenSecStdDeviation[i] = 0;
        hundredSecStdDeviation[i] = 0;
        oneSecMean[i] = 0;
        tenSecMean[i] = 0;
        hundredSecMean[i] = 0;
        tenData[i] = 0;
        hundredData[i] = 0;
        rawData[i]=0;
        oneSecData[i].clear();
        tenSecData[i].clear();
        hundredSecData[i].clear();

    }
   calculatFlag = false;
   insertIndex = 0;

}

void data_processing::stop(){
    initData();
}

void data_processing::run() {
    QFile *hundredSecDataAllBoard = NULL;
    QFile *oneSecDataAllBoard = NULL;
    QFile *tenSecDataAllBoard = NULL;

    volatile bool hundredSecExist = false;
    volatile bool oneSecFileExist = false;
    volatile bool tenSecFileExist = false;
    if (exists_CH4)
    {
        oneSecDataAllBoard = new QFile(m_FilePath_CH4 + QTime::currentTime().toString("//hhmmss_") + "onesec.txt");
        tenSecDataAllBoard = new QFile(m_FilePath_CH4 + QTime::currentTime().toString("//hhmmss_") + "tensec.txt");
        hundredSecDataAllBoard = new QFile(m_FilePath_CH4 + QTime::currentTime().toString("//hhmmss_") + "hundredsec.txt");

        if (hundredSecDataAllBoard->open(QIODevice::WriteOnly))
            hundredSecExist = true;
        else
            hundredSecExist = false;

        if (oneSecDataAllBoard->open(QIODevice::WriteOnly))
            oneSecFileExist = true;
        else
            oneSecFileExist = false;

        if (tenSecDataAllBoard->open(QIODevice::WriteOnly))
            tenSecFileExist = true;
        else
            tenSecFileExist = false;
    }
    initData();


    while(!Run_stopped){
//        qDebug()<<"sdasd";
//        qDebug()<<"bbbbbbbbbb";
        if(calculatFlag){
            calculatFlag = false;
            insertIndex++;
            for(int i=0;i<24;i++){
                oneSecData[i].push_back(rawData[i]);
                tenData[i]+=rawData[i];
                oneSecMean[i] = std::accumulate(oneSecData[i].begin(),oneSecData[i].end(),0.0)/oneSecData[i].size();
                accum  = 0.0;
                std::for_each (std::begin(oneSecData[i]), std::end(oneSecData[i]), [&](const float d) {
                    accum  += (d-oneSecMean[i])*(d-oneSecMean[i]);});
                if(oneSecData[i].size()==1){
                    oneSecStdDeviation[i] = 0;
                }
                else{
                    oneSecStdDeviation[i] = sqrt(accum/(oneSecData[i].size()-1));
                }
            }
//            if(oneSecData[0].size()>20000){
//                for(int i=0;i<24;i++){
//                    oneSecData[i].erase(oneSecData[i].begin());
//                }
//            }
            emit sendToShowData(oneSecMean,oneSecStdDeviation,tenSecMean,tenSecStdDeviation,hundredSecMean,hundredSecStdDeviation);
            emit sendToPlotOneSec(rawData);
            oneSecDataAllBoard->write(QString("%1\t%2\t%3\t\t%4\t%5\t%6\t\t%7\t%8\t%9\t\t%10\t%11\t%12\t\t%13\t%14\t%15\t\t%16\t%17\t%18\t\t%19\t%20\t%21\t\t%22\t%23\t%24\t\r\n").arg(rawData[0]).arg(rawData[8]).arg(rawData[16]).
                    arg(rawData[1]).arg(rawData[9]).arg(rawData[17]).
                    arg(rawData[2]).arg(rawData[10]).arg(rawData[18]).
                    arg(rawData[3]).arg(rawData[11]).arg(rawData[19]).
                    arg(rawData[4]).arg(rawData[12]).arg(rawData[20]).
                    arg(rawData[5]).arg(rawData[13]).arg(rawData[21]).
                    arg(rawData[6]).arg(rawData[14]).arg(rawData[22]).
                    arg(rawData[7]).arg(rawData[15]).arg(rawData[23]).toUtf8());

            if(insertIndex%10==0){

                for(int i=0;i<24;i++){
                    tenSecData[i].push_back(tenData[i]);
                    hundredData[i]+=tenData[i];
                    tenSecMean[i] = std::accumulate(tenSecData[i].begin(),tenSecData[i].end(),0.0)/tenSecData[i].size();
                    accum  = 0.0;
                    std::for_each (std::begin(tenSecData[i]), std::end(tenSecData[i]), [&](const float d) {
                        accum  += (d-tenSecMean[i])*(d-tenSecMean[i]);});
                    tenData_[i]=tenData[i];

                    tenData[i]=0;


                    if(tenSecData[i].size()==1){
                        tenSecStdDeviation[i] = 0;
                    }
                    else{
                        tenSecStdDeviation[i] = sqrt(accum/(tenSecData[i].size()-1));
                    }
                }
//                if(tenSecData[0].size()>10000){
//                    for(int i=0;i<24;i++){
//                        tenSecData[i].erase(tenSecData[i].begin());
//                    }
//                }
                emit sendToPlotTenSec(tenData_);
                tenSecDataAllBoard->write(QString("%1\t%2\t%3\t\t%4\t%5\t%6\t\t%7\t%8\t%9\t\t%10\t%11\t%12\t\t%13\t%14\t%15\t\t%16\t%17\t%18\t\t%19\t%20\t%21\t\t%22\t%23\t%24\t\r\n").arg(tenData_[0]).arg(tenData_[8]).arg(tenData_[16]).
                        arg(tenData_[1]).arg(tenData_[9]).arg(tenData_[17]).
                        arg(tenData_[2]).arg(tenData_[10]).arg(tenData_[18]).
                        arg(tenData_[3]).arg(tenData_[11]).arg(tenData_[19]).
                        arg(tenData_[4]).arg(tenData_[12]).arg(tenData_[20]).
                        arg(tenData_[5]).arg(tenData_[13]).arg(tenData_[21]).
                        arg(tenData_[6]).arg(tenData_[14]).arg(tenData_[22]).
                        arg(tenData_[7]).arg(tenData_[15]).arg(tenData_[23]).toUtf8());
                //qDebug()<<"tenSecMean"<<tenSecMean[0]<<"tenSecStdDeviation"<<tenSecStdDeviation[0];

            }
            if(insertIndex%100==0){
                for(int i=0;i<24;i++){
                    hundredSecData[i].push_back(hundredData[i]);

                    hundredSecMean[i] = std::accumulate(hundredSecData[i].begin(),hundredSecData[i].end(),0.0)/hundredSecData[i].size();
                    accum  = 0.0;
                    std::for_each (std::begin(hundredSecData[i]), std::end(hundredSecData[i]), [&](const float d) {
                        accum  += (d-hundredSecMean[i])*(d-hundredSecMean[i]);});
                    if(hundredSecData[i].size()==1){
                        hundredSecStdDeviation[i] = 0;
                    }
                    else{
                        hundredSecStdDeviation[i] = sqrt(accum/(hundredSecData[i].size()-1));
                    }
                    hundredData_[i]=hundredData[i];
                    hundredData[i]=0;

                }
                if(hundredSecData[0].size()>2000){
                    for(int i=0;i<24;i++){
                        hundredSecData[i].erase(hundredSecData[i].begin());
                    }
                }
                hundredSecDataAllBoard->write(QString("%1\t%2\t%3\t\t%4\t%5\t%6\t\t%7\t%8\t%9\t\t%10\t%11\t%12\t\t%13\t%14\t%15\t\t%16\t%17\t%18\t\t%19\t%20\t%21\t\t%22\t%23\t%24\t\r\n").arg(hundredData_[8]).arg(hundredData_[16]).
                        arg(hundredData_[1]).arg(hundredData_[9]).arg(hundredData_[17]).
                        arg(hundredData_[2]).arg(hundredData_[10]).arg(hundredData_[18]).
                        arg(hundredData_[3]).arg(hundredData_[11]).arg(hundredData_[19]).
                        arg(hundredData_[4]).arg(hundredData_[12]).arg(hundredData_[20]).
                        arg(hundredData_[5]).arg(hundredData_[13]).arg(hundredData_[21]).
                        arg(hundredData_[6]).arg(hundredData_[14]).arg(hundredData_[22]).
                        arg(hundredData_[7]).arg(hundredData_[15]).arg(hundredData_[23]).toUtf8());
                emit sendToPlotHundredSec(hundredData_);
                //qDebug()<<"tenSecMean"<<hundredSecMean[0]<<"tenSecStdDeviation"<<hundredSecStdDeviation[0];

            }

        }
    }
    if (hundredSecExist)
    {
        hundredSecDataAllBoard->flush();
        hundredSecDataAllBoard->close();
        delete hundredSecDataAllBoard;
    }
    if (oneSecFileExist)
    {
        oneSecDataAllBoard->flush();
        oneSecDataAllBoard->close();
        delete oneSecDataAllBoard;
    }

    if (tenSecFileExist)
    {
        tenSecDataAllBoard->flush();
        tenSecDataAllBoard->close();
        delete tenSecDataAllBoard;
    }
    qDebug()<<hundredSecExist<<oneSecFileExist<<tenSecFileExist;

    Run_stopped=true;
}
