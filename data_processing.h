#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H
#include <QThread>
#include <QDebug>
#include <cmath>
#include <vector>
#include <QFile>
#include <QTime>
#include <iostream>

using namespace std;

class data_processing : public QThread
{
    Q_OBJECT
public:
    data_processing();
    ~data_processing();

    void initData();
    void stop();
    void run() Q_DECL_OVERRIDE;


public:
    float *oneSecStdDeviation;
    float *tenSecStdDeviation;
    float *hundredSecStdDeviation;
    float *oneSecMean;
    float *tenSecMean;
    float *hundredSecMean;
    float *rawData;
    float* tenData;
    float * hundredData;
    float hundredData_[24];
    float tenData_[24];
    bool exists_CH4;
    QString m_FilePath_CH4;

    quint32 insertIndex;
    bool calculatFlag;
    bool Run_stopped;
    vector<float> oneSecData[24];
    vector<float> tenSecData[24];
    vector<float> hundredSecData[24];
    float accum;

public slots:
    void getOneSecAllData(float*,bool);
signals:
    void sendToShowData(float*,float*,float*,float*,float*,float*);
    void sendToPlotOneSec(float *);
    void sendToPlotTenSec(float *);
    void sendToPlotHundredSec(float *);


};

#endif // DATA_PROCESSING_H
