#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QThread>
#include <QDebug>
#include <cmath>

#define BS_Count 60480  //BS_Count a week  6*60*24*7 = 60480

class Calculator : public QThread
{
    Q_OBJECT
public:
    Calculator();
    ~Calculator();

    void insertData(double add_data);
    void setScale(double m_scale);
    void stop(void);

signals:
    void sendDisplay(double m_meanFog, double m_zeroBias, double m_biasStability);
    void sendDisplay_rm2(double m_meanFog, double m_zeroBias, double m_biasStability);

protected:
    void run(void);

private:
    double Data[BS_Count];

    quint32 insertIndex;
    double scale;
    double scale_DPH;
    double dataTemp;
    double meanFog;
    double zeroBias;
    double biasStability;

    void initData(void);
};

#endif // CALCULATOR_H
