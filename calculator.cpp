#include "calculator.h"
#include <QTime>

Calculator::Calculator()
{
    this->initData();
}

Calculator::~Calculator()
{

}

void Calculator::insertData(double add_data)
{
    dataTemp = add_data;

    if (insertIndex < BS_Count)
    {
        Data[insertIndex] = dataTemp;
        insertIndex++;

        this->run();
    }
    else
    {
        emit sendDisplay(888.88888, 888.88888, 888.88888);
    }
}

void Calculator::setScale(double m_scale)
{
    scale = m_scale;
    scale_DPH = scale;
}

void Calculator::stop()
{
    dataTemp = 0;
    insertIndex = 0;

    meanFog = 0;
    zeroBias = 0;
    biasStability = 0;
}

void Calculator::run()
{
    long double sum = 0;

    for (int i=0; i<(int)insertIndex; i++)
    {
        sum += Data[i];
    }

    meanFog = sum / insertIndex;

    //meanFog = sum;
    zeroBias = meanFog / scale_DPH;
    //zeroBias = sum / scale_DPH;
    double subtract = 0;
    double subtract_Sum = 0;

    for (int i = 0; i < (int)insertIndex; i++)
    {
        subtract = Data[i] - meanFog;
        subtract *= subtract;

        subtract_Sum += subtract;
    }

    if (insertIndex > 1)
    {
        subtract = subtract_Sum / (insertIndex-1);
        subtract = sqrt(subtract);
        biasStability = subtract / scale_DPH;
    }
    else
    {
        biasStability = 0.00;
    }

    //emit sendDisplay(meanFog, zeroBias, biasStability);
    emit sendDisplay(meanFog,subtract , biasStability);
    //emit sendDisplay(sum, zeroBias, biasStability);
    // ********** Calculate rm2 ************
    if (12 < insertIndex)
    {
        sum = 0;

        for (int i=12; i<(int)insertIndex; i++)
        {
            sum += Data[i];
            //sum = Data[i];
        }

        int count = insertIndex - 12;

        meanFog = sum / count;
        //meanFog = sum;
        zeroBias = meanFog / scale_DPH;
        //zeroBias = sum / scale_DPH;

        subtract = 0;
        subtract_Sum = 0;

        for (int i=12; i < (int)insertIndex; i++)
        {
            subtract = Data[i] - meanFog;
            subtract *= subtract;

            subtract_Sum += subtract;
        }

        if (count > 1)
        {
            subtract = subtract_Sum / (count-1);
            subtract = sqrt(subtract);
            biasStability = subtract / scale_DPH;
        }
        else
        {
            biasStability = 0.00;
        }

       // emit sendDisplay_rm2(meanFog, zeroBias, biasStability);
        emit sendDisplay(meanFog,subtract , biasStability);
         //emit sendDisplay(sum, zeroBias, biasStability);
    }
    else
    {
        emit sendDisplay_rm2(888.88888, 888.88888, 888.88888);
    }
}

void Calculator::initData()
{
    dataTemp = 0;
    insertIndex = 0;

    meanFog = 0;
    zeroBias = 0;
    biasStability = 0;

    scale = 1;
    scale_DPH = scale;
}

