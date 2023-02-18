#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <QSettings>
#include <QTextCodec>
#include <QValidator>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QFileDialog>
#include <QDebug>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_legend.h>

#include "serialport_decoder.h"
#include "report_generater.h"
#include "calculator.h"
#include "aboutdialog.h"

namespace Ui {
class MainWindow;
}

struct Board{
    QwtPlotCurve *oneSecCurve_Board01_CH1;
    QwtPlotCurve *oneSecCurve_Board01_CH2;
    QwtPlotCurve *oneSecCurve_Board01_CH3;


    QwtPlotCurve *tenSecCurve_Board01_CH1;
    QwtPlotCurve *tenSecCurve_Board01_CH2;
    QwtPlotCurve *tenSecCurve_Board01_CH3;

    QwtPlotCurve *hundredSecCurve_Board01_CH1;
    QwtPlotCurve *hundredSecCurve_Board01_CH2;
    QwtPlotCurve *hundredSecCurve_Board01_CH3;

    QwtPlotGrid *oneSecCurveGrid_Board01_CH1;
    QwtPlotGrid *oneSecCurveGrid_Board01_CH2;
    QwtPlotGrid *oneSecCurveGrid_Board01_CH3;


    QwtPlotGrid *tenSecCurveGrid_Board01_CH1;
    QwtPlotGrid *tenSecCurveGrid_Board01_CH2;
    QwtPlotGrid *tenSecCurveGrid_Board01_CH3;


    QwtPlotGrid *hundredSecCurveGrid_Board01_CH1;
    QwtPlotGrid *hundredSecCurveGrid_Board01_CH2;
    QwtPlotGrid *hundredSecCurveGrid_Board01_CH3;

    QPolygonF oneSec_Data_Board01_CH1;
    ulong     oneSec_Data_Count_Board01_CH1;
    QPolygonF oneSec_Data_Board01_CH2;
    ulong     oneSec_Data_Count_Board01_CH2;
    QPolygonF oneSec_Data_Board01_CH3;
    ulong     oneSec_Data_Count_Board01_CH3;
    QPolygonF tenSec_Data_Board01_CH1;
    ulong     tenSec_Data_Count_Board01_CH1;
    QPolygonF tenSec_Data_Board01_CH2;
    ulong     tenSec_Data_Count_Board01_CH2;
    QPolygonF tenSec_Data_Board01_CH3;
    ulong     tenSec_Data_Count_Board01_CH3;
    QPolygonF hundredSec_Data_Board01_CH1;
    ulong     hundredSec_Data_Count_Board01_CH1;
    QPolygonF hundredSec_Data_Board01_CH2;
    ulong     hundredSec_Data_Count_Board01_CH2;
    QPolygonF hundredSec_Data_Board01_CH3;
    ulong     hundredSec_Data_Count_Board01_CH3;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void sendrenew(unsigned int renew);

public slots:
    void attachOneSecCurveSamples(float * oneSecData);
    void attachTenSecCurveSamples(float * oneSecData);
    void attachciadd(float * oneSecData);
    void getToShowData(float*,float*,float*,float*,float*,float*);

//    void displayZeroBias_CH1(const double mean, const double zeroBias, const double biasStd);
//    void displayZeroBias_CH2(const double mean, const double zeroBias, const double biasStd);
//    void displayZeroBias_CH3(const double mean, const double zeroBias, const double biasStd);
//    void displayZeroBias_CH4(const double mean, const double zeroBias, const double biasStd);
//    void displayZeroBias_CH5(const double mean, const double zeroBias, const double biasStd);
//    void displayZeroBias_CH6(const double mean, const double zeroBias, const double biasStd);
//    void displayZeroBias_CH7(const double mean, const double zeroBias, const double biasStd);
//    void displayZeroBias_CH8(const double mean, const double zeroBias, const double biasStd);
//    void displayZeroBias_CH9(const double mean, const double zeroBias, const double biasStd);

//    void displayZeroBias_CH1_rm2(const double mean, const double zeroBias, const double biasStd);
//    void displayZeroBias_CH2_rm2(const double mean, const double zeroBias, const double biasStd);
//    void displayZeroBias_CH3_rm2(const double mean, const double zeroBias, const double biasStd);

private slots:
    void fogCalibration(void);
    void finishCalibration(void);
    void selectSaveDataFilePath(void);
    void on_comboBox_SerialPort_currentIndexChanged(const QString &arg1);
    void on_lineEdit_FogNum_CH1_textChanged(const QString &arg1);
    void on_lineEdit_FogNum_CH2_textChanged(const QString &arg1);
    void on_lineEdit_FogNum_CH3_textChanged(const QString &arg1);
    void on_lineEdit_Scale_CH1_textChanged(const QString &arg1);
    void on_lineEdit_Scale_CH2_textChanged(const QString &arg1);
    void on_lineEdit_Scale_CH3_textChanged(const QString &arg1);
    void on_tabWidget_currentChanged(int index);
    void on_tabWidget_01_currentChanged(int index);
    void on_tabWidget_02_currentChanged(int index);
    void on_tabWidget_03_currentChanged(int index);
    void on_tabWidget_04_currentChanged(int index);
    void on_tabWidget_05_currentChanged(int index);
    void on_tabWidget_06_currentChanged(int index);
    void on_tabWidget_07_currentChanged(int index);
    void on_tabWidget_08_currentChanged(int index);
    void updata_biasStd_Display(void);

    void on_lineEdit_editingFinished();

    void on_comboBox_SerialPort_5_currentIndexChanged(const QString &arg1);

private:
    void initApplication(void);
    void initConnections(void);
    void initCurveData(void);
    void addSerialPort(void);
    void drawOneSecLineChart(Board *,const float, const float, const float);
    void drawTenSecLineChart(Board *,const float, const float, const float);
    void drawHundredSecLineChart(Board *,const float , const float , const float);
    void boardDataReset(Board *board);
    void boardInitData(Board *board,QwtPlot** uiQwtPlot,int board_index);
    void switch_sub_tab_display(int,int);

    float *oneSecStdDeviation;
    float *tenSecStdDeviation;
    float *hundredSecStdDeviation;
    float *oneSecMean;
    float *tenSecMean;
    float *hundredSecMean;

    float oneSecData[24];
    float tenSecData[24];
    float hundredSecData[24];
    float listWidgetCh1;
    float listWidgetCh2;
    float listWidgetCh3;


private:
    Ui::MainWindow *ui;
    AboutDialog *aboutDlg;

    volatile int deviceTabIndex;
    volatile int chTabIndex;
    QString curCOMPort;
    QString curbundrate;
    QString saveFilePath;

    QString fogNum_CH1;
    QString fogNum_CH2;
    QString fogNum_CH3;
    QString fogNum_CH4;
    double  scale_CH1;
    double  scale_CH2;
    double  scale_CH3;
    double  scale_CH4;

    SerialPort_Decoder *serialDecoder;
    QValidator *validatorFogNumber;

//    Report_Generater *Report_CH1;
//    Report_Generater *Report_CH2;
//    Report_Generater *Report_CH3;



    //板子定义
    Board * boards[8];
    QTabWidget * tabWidget[8];

    //无修改
    double meanFog_Disp;
    double zeroBias_Disp;
    double biasStd_Disp;
    double meanFog_CH1;
    double zeroBias_CH1;
    double biasStd_CH1;
    double meanFog_CH2;
    double zeroBias_CH2;
    double biasStd_CH2;
    double meanFog_CH3;
    double zeroBias_CH3;
    double biasStd_CH3;
    double meanFog_CH4;
    double zeroBias_CH4;
    double biasStd_CH4;
    double meanFog_CH5;
    double zeroBias_CH5;
    double biasStd_CH5;
    double meanFog_CH6;
    double zeroBias_CH6;
    double biasStd_CH6;
    double meanFog_CH7;
    double zeroBias_CH7;
    double biasStd_CH7;
    double meanFog_CH8;
    double zeroBias_CH8;
    double biasStd_CH8;
    double meanFog_CH9;
    double zeroBias_CH9;
    double biasStd_CH9;

    double meanFog_Disp_rm2;
    double zeroBias_Disp_rm2;
    double biasStd_Disp_rm2;
    double meanFog_CH1_rm2;
    double zeroBias_CH1_rm2;
    double biasStd_CH1_rm2;
    double meanFog_CH2_rm2;
    double zeroBias_CH2_rm2;
    double biasStd_CH2_rm2;
    double meanFog_CH3_rm2;
    double zeroBias_CH3_rm2;
    double biasStd_CH3_rm2;
};

#endif // MAINWINDOW_H
