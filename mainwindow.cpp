#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->initApplication();
}

MainWindow::~MainWindow()
{
    QSettings settings("Tweak_Multi", "ZKHX");
    settings.setValue("file_Path", saveFilePath);

    delete [] oneSecStdDeviation;
    delete [] tenSecStdDeviation;
    delete [] hundredSecStdDeviation;
    delete [] oneSecMean;
    delete [] tenSecMean;
    delete [] hundredSecMean;
    for(int i=0;i<8;i++){
        delete boards[i];
    }


    delete validatorFogNumber;
    delete aboutDlg;
    delete ui;
}

void MainWindow::drawOneSecLineChart(Board *board,const float oneSec_CH1, const float oneSec_CH2, const float oneSec_CH3){
    board->oneSec_Data_Board01_CH1 << QPointF(board->oneSec_Data_Count_Board01_CH1, oneSec_CH1);
    board->oneSec_Data_Board01_CH2 << QPointF(board->oneSec_Data_Count_Board01_CH2, oneSec_CH2);
    board->oneSec_Data_Board01_CH3 << QPointF(board->oneSec_Data_Count_Board01_CH3, oneSec_CH3);

    board->oneSecCurve_Board01_CH1->setSamples(board->oneSec_Data_Board01_CH1);
    board->oneSecCurve_Board01_CH2->setSamples(board->oneSec_Data_Board01_CH2);
    board->oneSecCurve_Board01_CH3->setSamples(board->oneSec_Data_Board01_CH3);

    board->oneSec_Data_Count_Board01_CH1 += 1;
    board->oneSec_Data_Count_Board01_CH2 += 1;
    board->oneSec_Data_Count_Board01_CH3 += 1;
}

void MainWindow::drawTenSecLineChart(Board *board,const float tenSec_CH1, const float tenSec_CH2, const float tenSec_CH3){
    board->tenSec_Data_Board01_CH1 << QPointF(board->tenSec_Data_Count_Board01_CH1, tenSec_CH1);
    board->tenSec_Data_Board01_CH2 << QPointF(board->tenSec_Data_Count_Board01_CH2, tenSec_CH2);
    board->tenSec_Data_Board01_CH3 << QPointF(board->tenSec_Data_Count_Board01_CH3, tenSec_CH3);

    board->tenSecCurve_Board01_CH1->setSamples(board->tenSec_Data_Board01_CH1);
    board->tenSecCurve_Board01_CH2->setSamples(board->tenSec_Data_Board01_CH2);
    board->tenSecCurve_Board01_CH3->setSamples(board->tenSec_Data_Board01_CH3);

    board->tenSec_Data_Count_Board01_CH1 += 1;
    board->tenSec_Data_Count_Board01_CH2 += 1;
    board->tenSec_Data_Count_Board01_CH3 += 1;
}

void MainWindow::drawHundredSecLineChart(Board *board,const float hundredSec_CH1, const float hundredSec_CH2, const float hundredSec_CH3){
    board->hundredSec_Data_Board01_CH1 << QPointF(board->hundredSec_Data_Count_Board01_CH1, hundredSec_CH1);
    board->hundredSec_Data_Board01_CH2 << QPointF(board->hundredSec_Data_Count_Board01_CH2, hundredSec_CH2);
    board->hundredSec_Data_Board01_CH3 << QPointF(board->hundredSec_Data_Count_Board01_CH3, hundredSec_CH3);

    board->hundredSecCurve_Board01_CH1->setSamples(board->hundredSec_Data_Board01_CH1);
    board->hundredSecCurve_Board01_CH2->setSamples(board->hundredSec_Data_Board01_CH2);
    board->hundredSecCurve_Board01_CH3->setSamples(board->hundredSec_Data_Board01_CH3);

    board->hundredSec_Data_Count_Board01_CH1 += 1;
    board->hundredSec_Data_Count_Board01_CH2 += 1;
    board->hundredSec_Data_Count_Board01_CH3 += 1;
}

void MainWindow::attachOneSecCurveSamples(float * oneSecData)//X轴
{
    for(int i=0;i<24;i++){
        this->oneSecData[i] = oneSecData[i];
    }
    //qDebug()<<"attachOneSecCurveSamples"<<this->oneSecData[0];
    //ui->listWidget->addItem(QString("%1__%2__%3").arg(oneSecData).arg(oneSec_CH2).arg(oneSec_CH3));
    for(int i=0;i<8;i++){
        drawOneSecLineChart(boards[i],this->oneSecData[i],this->oneSecData[i+8],this->oneSecData[i+16]);
    }
    this->updata_biasStd_Display();
}

void MainWindow::attachTenSecCurveSamples(float * tenSecData)
{
    for(int i=0;i<24;i++){
        this->tenSecData[i] = tenSecData[i];
    }
    for(int i=0;i<8;i++){
        drawTenSecLineChart(boards[i],this->tenSecData[i],this->tenSecData[i+8],this->tenSecData[i+16]);
    }
}

void MainWindow::attachciadd(float * hundredSecData)
{
    for(int i=0;i<24;i++){
        this->hundredSecData[i] = hundredSecData[i];
    }

    for(int i=0;i<8;i++){
        drawHundredSecLineChart(boards[i],this->hundredSecData[i],this->hundredSecData[i+8],this->hundredSecData[i+16]);
    }
}

void MainWindow::getToShowData(float* oneSecMean,float* oneSecStdDeviation,float* tenSecMean,float* tenSecStdDeviation,float* hundredSecMean,float* hundredSecStdDeviation){
    for(int i=0;i<24;i++){
        this->oneSecMean[i]=oneSecMean[i];
            this->oneSecStdDeviation[i]=oneSecStdDeviation[i];
            this->tenSecMean[i]=tenSecMean[i];
            this->tenSecStdDeviation[i]=tenSecStdDeviation[i];
            this->hundredSecMean[i]=hundredSecMean[i];
            this->hundredSecStdDeviation[i]=hundredSecStdDeviation[i];
    }
}

void MainWindow::boardDataReset(Board *board){
    board->oneSec_Data_Count_Board01_CH1 = 0;
    board->oneSec_Data_Count_Board01_CH2 = 0;
    board->oneSec_Data_Count_Board01_CH3 = 0;

    board->tenSec_Data_Count_Board01_CH1 = 0;
    board->tenSec_Data_Count_Board01_CH2 = 0;
    board->tenSec_Data_Count_Board01_CH3 = 0;

    board->hundredSec_Data_Count_Board01_CH1 = 0;
    board->hundredSec_Data_Count_Board01_CH2 = 0;
    board->hundredSec_Data_Count_Board01_CH3 = 0;
    board->oneSec_Data_Board01_CH1.clear();
    board->oneSec_Data_Board01_CH2.clear();
    board->oneSec_Data_Board01_CH3.clear();
    board->oneSecCurve_Board01_CH1->setSamples(board->oneSec_Data_Board01_CH1);
    board->oneSecCurve_Board01_CH2->setSamples(board->oneSec_Data_Board01_CH2);
    board->oneSecCurve_Board01_CH3->setSamples(board->oneSec_Data_Board01_CH3);

    board->tenSec_Data_Board01_CH1.clear();
    board->tenSec_Data_Board01_CH2.clear();
    board->tenSec_Data_Board01_CH3.clear();
    board->tenSecCurve_Board01_CH1->setSamples(board->tenSec_Data_Board01_CH1);
    board->tenSecCurve_Board01_CH2->setSamples(board->tenSec_Data_Board01_CH2);
    board->tenSecCurve_Board01_CH3->setSamples(board->tenSec_Data_Board01_CH3);

    board->hundredSec_Data_Board01_CH1.clear();
    board->hundredSec_Data_Board01_CH2.clear();
    board->hundredSec_Data_Board01_CH3.clear();
    board->hundredSecCurve_Board01_CH1->setSamples(board->hundredSec_Data_Board01_CH1);
    board->hundredSecCurve_Board01_CH2->setSamples(board->hundredSec_Data_Board01_CH2);
    board->hundredSecCurve_Board01_CH3->setSamples(board->hundredSec_Data_Board01_CH3);
}

void MainWindow::fogCalibration()
{
    if (curCOMPort.operator !=("N/A"))
    {
        for(int i=0;i<8;i++){
            boardDataReset(boards[i]);
        }

        meanFog_Disp = 0;
        zeroBias_Disp = 0;
        biasStd_Disp = 0;
        meanFog_CH1 = 0;
        zeroBias_CH1 = 0;
        biasStd_CH1 = 0;
        meanFog_CH2 = 0;
        zeroBias_CH2 = 0;
        biasStd_CH2 = 0;
        meanFog_CH3 = 0;
        zeroBias_CH3 = 0;
        biasStd_CH3 = 0;
        meanFog_CH4 = 0;
        zeroBias_CH4 = 0;
        biasStd_CH4 = 0;
        meanFog_CH5 = 0;
        zeroBias_CH5 = 0;
        biasStd_CH5 = 0;
        meanFog_CH6 = 0;
        zeroBias_CH6 = 0;
        biasStd_CH6= 0;
        meanFog_CH7 = 0;
        zeroBias_CH7 = 0;
        biasStd_CH7 = 0;
        meanFog_CH8 = 0;
        zeroBias_CH8 = 0;
        biasStd_CH8 = 0;
        meanFog_CH9 = 0;
        zeroBias_CH9 = 0;
        biasStd_CH9 = 0;

        meanFog_Disp_rm2 = 0;
        zeroBias_Disp_rm2 = 0;
        biasStd_Disp_rm2 = 0;
        meanFog_CH1_rm2 = 0;
        zeroBias_CH1_rm2 = 0;
        biasStd_CH1_rm2 = 0;
        meanFog_CH2_rm2 = 0;
        zeroBias_CH2_rm2 = 0;
        biasStd_CH2_rm2 = 0;
        meanFog_CH3_rm2 = 0;
        zeroBias_CH3_rm2 = 0;
        biasStd_CH3_rm2 = 0;

        deviceTabIndex = 0;
        chTabIndex = 0;



        this->updata_biasStd_Display();

        QString filePath_CH4 = saveFilePath + "//" + fogNum_CH4 + "//";


        serialDecoder = new SerialPort_Decoder();
        serialDecoder->set_FilePath(filePath_CH4);
        serialDecoder->setMainPort(this, curCOMPort,curbundrate);

        ui->action_filePath->setEnabled(false);
        ui->action_start->setEnabled(false);
        ui->action_stop->setEnabled(true);

        ui->statusBar->showMessage("OK");
    }
    else
    {
        ui->statusBar->showMessage(QStringLiteral("串口号无效"));
    }
}

void MainWindow::finishCalibration()
{

    delete serialDecoder;

    ui->action_filePath->setEnabled(true);
    ui->action_start->setEnabled(true);
    ui->action_stop->setEnabled(false);
}

void MainWindow::initApplication()
{
    deviceTabIndex = 0;
    chTabIndex = 0;

    fogNum_CH1 = "Pulse_CH1";
    fogNum_CH2 = "Pulse_CH2";
    fogNum_CH3 = "Pulse_CH3";
    fogNum_CH4 = "AllDataCH123";
    scale_CH1 = 10.00;
    scale_CH2 = 10.00;
    scale_CH3 = 10.00;
    scale_CH4 = 10.00;

    meanFog_Disp = 0;
    zeroBias_Disp = 0;
    biasStd_Disp = 0;
    meanFog_CH1 = 0;
    zeroBias_CH1 = 0;
    biasStd_CH1 = 0;
    meanFog_CH2 = 0;
    zeroBias_CH2 = 0;
    biasStd_CH2 = 0;
    meanFog_CH3 = 0;
    zeroBias_CH3 = 0;
    biasStd_CH3 = 0;

    meanFog_Disp_rm2 = 0;
    zeroBias_Disp_rm2 = 0;
    biasStd_Disp_rm2 = 0;
    meanFog_CH1_rm2 = 0;
    zeroBias_CH1_rm2 = 0;
    biasStd_CH1_rm2 = 0;
    meanFog_CH2_rm2 = 0;
    zeroBias_CH2_rm2 = 0;
    biasStd_CH2_rm2 = 0;
    meanFog_CH3_rm2 = 0;
    zeroBias_CH3_rm2 = 0;
    biasStd_CH3_rm2 = 0;

    curCOMPort = "N/A";

    aboutDlg = new AboutDialog();

    for(int i=0;i<8;i++)
    {
         boards[i] = new Board();
    }




    oneSecStdDeviation = new float[24];
    tenSecStdDeviation = new float[24];
    hundredSecStdDeviation = new float[24];
    oneSecMean = new float[24];
    tenSecMean = new float[24];
    hundredSecMean = new float[24];

    for(int i=0;i<24;i++){
        hundredSecData[i]=0;
        tenSecData[i]=0;
        oneSecData[i]=0;
    }
    QRegExp fogNumber("[0-9, A-Z, a-z]{0,15}");
    validatorFogNumber = new QRegExpValidator(fogNumber, this);

    QDoubleValidator *scale = new QDoubleValidator(0, 10000000.00, 6,this);


    QSettings settings("Tweak_Multi", "ZKHX");
    saveFilePath.clear();
    saveFilePath = settings.value("file_Path").toString();

    ui->mainToolBar->setMovable(false);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    this->initCurveData();
    this->initConnections();
    this->addSerialPort();

    ui->action_start->setEnabled(false);
    ui->action_stop->setEnabled(false);
}

void MainWindow::initConnections()
{
    connect(ui->action_about, SIGNAL(triggered()), aboutDlg, SLOT(show()));
    connect(ui->action_start, SIGNAL(triggered()), this, SLOT(fogCalibration()));
    connect(ui->action_stop, SIGNAL(triggered()), this, SLOT(finishCalibration()));
    connect(ui->action_filePath, SIGNAL(triggered()), this, SLOT(selectSaveDataFilePath()));
}

void MainWindow::boardInitData(Board *board,QwtPlot** uiQwtPlot,int board_index){

    board->oneSecCurve_Board01_CH1 = NULL;
    board->oneSecCurve_Board01_CH2 = NULL;
    board->oneSecCurve_Board01_CH3 = NULL;
    board->hundredSecCurve_Board01_CH1 = NULL;
    board->hundredSecCurve_Board01_CH2 = NULL;
    board->hundredSecCurve_Board01_CH3 = NULL;

    board->tenSecCurve_Board01_CH1 = NULL;
    board->tenSecCurve_Board01_CH2 = NULL;
    board->tenSecCurve_Board01_CH3 = NULL;

    board->oneSec_Data_Count_Board01_CH1 = 0;
    board->oneSec_Data_Count_Board01_CH2 = 0;
    board->oneSec_Data_Count_Board01_CH3 = 0;

    board->tenSec_Data_Count_Board01_CH1 = 0;
    board->tenSec_Data_Count_Board01_CH2 = 0;
    board->tenSec_Data_Count_Board01_CH3 = 0;

    board->hundredSec_Data_Count_Board01_CH1 =0;
    board->hundredSec_Data_Count_Board01_CH2 =0;
    board->hundredSec_Data_Count_Board01_CH3 =0;

    board->oneSecCurve_Board01_CH1 = new QwtPlotCurve();
    board->oneSecCurve_Board01_CH1->setPen(Qt::blue, 0),
            board->oneSecCurve_Board01_CH1->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    board->oneSecCurve_Board01_CH1->attach(uiQwtPlot[board_index*9]);
    board->oneSecCurve_Board01_CH2 = new QwtPlotCurve();
    board->oneSecCurve_Board01_CH2->setPen(Qt::blue, 0),
            board->oneSecCurve_Board01_CH2->setRenderHint(QwtPlotItem::RenderAntialiased, true);
    board->oneSecCurve_Board01_CH2->attach(uiQwtPlot[board_index*9+1]);
    board->oneSecCurve_Board01_CH3 = new QwtPlotCurve();
    board->oneSecCurve_Board01_CH3->setPen(Qt::blue, 0),
            board->oneSecCurve_Board01_CH3->setRenderHint(QwtPlotItem::RenderAntialiased, true);
    board->oneSecCurve_Board01_CH3->attach(uiQwtPlot[board_index*9+2]);



    board->tenSecCurve_Board01_CH1 = new QwtPlotCurve();
    board->tenSecCurve_Board01_CH1->setPen(Qt::blue, 0),
            board->tenSecCurve_Board01_CH1->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    board->tenSecCurve_Board01_CH1->attach(uiQwtPlot[board_index*9+3]);
    board->tenSecCurve_Board01_CH2 = new QwtPlotCurve();
    board->tenSecCurve_Board01_CH2->setPen(Qt::blue, 0),
            board->tenSecCurve_Board01_CH2->setRenderHint(QwtPlotItem::RenderAntialiased, true);
    board->tenSecCurve_Board01_CH2->attach(uiQwtPlot[board_index*9+4]);
    board->tenSecCurve_Board01_CH3 = new QwtPlotCurve();
    board->tenSecCurve_Board01_CH3->setPen(Qt::blue, 0),
            board->tenSecCurve_Board01_CH3->setRenderHint(QwtPlotItem::RenderAntialiased, true);
    board->tenSecCurve_Board01_CH3->attach(uiQwtPlot[board_index*9+5]);




    board->hundredSecCurve_Board01_CH1 = new QwtPlotCurve();
    board->hundredSecCurve_Board01_CH1->setPen(Qt::blue, 0),
            board->hundredSecCurve_Board01_CH1->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    board->hundredSecCurve_Board01_CH1->attach(uiQwtPlot[board_index*9+6]);
   board-> hundredSecCurve_Board01_CH2 = new QwtPlotCurve();
    board->hundredSecCurve_Board01_CH2->setPen(Qt::blue, 0),
            board->hundredSecCurve_Board01_CH2->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    board->hundredSecCurve_Board01_CH2->attach(uiQwtPlot[board_index*9+7]);
    board->hundredSecCurve_Board01_CH3 = new QwtPlotCurve();
    board->hundredSecCurve_Board01_CH3->setPen(Qt::blue, 0),
            board->hundredSecCurve_Board01_CH3->setRenderHint( QwtPlotItem::RenderAntialiased, true );
   board->hundredSecCurve_Board01_CH3->attach(uiQwtPlot[board_index*9+8]);

    board->oneSecCurveGrid_Board01_CH1 = new QwtPlotGrid();
    board->oneSecCurveGrid_Board01_CH1->enableXMin( true );
    board->oneSecCurveGrid_Board01_CH1->enableYMin( true );
    board->oneSecCurveGrid_Board01_CH1->setMajorPen(Qt::lightGray, 0, Qt::SolidLine);
    board->oneSecCurveGrid_Board01_CH1->setMinorPen(Qt::lightGray, 0 , Qt::DotLine);
    board->oneSecCurveGrid_Board01_CH1->attach(uiQwtPlot[board_index*9]);
    board->oneSecCurveGrid_Board01_CH2 = new QwtPlotGrid();
    board->oneSecCurveGrid_Board01_CH2->enableXMin( true );
    board->oneSecCurveGrid_Board01_CH2->enableYMin( true );
    board->oneSecCurveGrid_Board01_CH2->setMajorPen(Qt::lightGray, 0, Qt::SolidLine);
    board->oneSecCurveGrid_Board01_CH2->setMinorPen(Qt::lightGray, 0 , Qt::DotLine);
    board->oneSecCurveGrid_Board01_CH2->attach(uiQwtPlot[board_index*9+1]);
    board->oneSecCurveGrid_Board01_CH3 = new QwtPlotGrid();
    board->oneSecCurveGrid_Board01_CH3->enableXMin( true );
    board->oneSecCurveGrid_Board01_CH3->enableYMin( true );
    board->oneSecCurveGrid_Board01_CH3->setMajorPen(Qt::lightGray, 0, Qt::SolidLine);
    board->oneSecCurveGrid_Board01_CH3->setMinorPen(Qt::lightGray, 0 , Qt::DotLine);
    board->oneSecCurveGrid_Board01_CH3->attach(uiQwtPlot[board_index*9+2]);

    board->tenSecCurveGrid_Board01_CH1 = new QwtPlotGrid();
    board->tenSecCurveGrid_Board01_CH1->enableXMin( true );
    board->tenSecCurveGrid_Board01_CH1->enableYMin( true );
    board->tenSecCurveGrid_Board01_CH1->setMajorPen(Qt::lightGray, 0, Qt::SolidLine);
    board->tenSecCurveGrid_Board01_CH1->setMinorPen(Qt::lightGray, 0 , Qt::DotLine);
    board->tenSecCurveGrid_Board01_CH1->attach(uiQwtPlot[board_index*9+3]);
    board->tenSecCurveGrid_Board01_CH2 = new QwtPlotGrid();
    board->tenSecCurveGrid_Board01_CH2->enableXMin( true );
    board->tenSecCurveGrid_Board01_CH2->enableYMin( true );
    board->tenSecCurveGrid_Board01_CH2->setMajorPen(Qt::lightGray, 0, Qt::SolidLine);
    board->tenSecCurveGrid_Board01_CH2->setMinorPen(Qt::lightGray, 0 , Qt::DotLine);
    board->tenSecCurveGrid_Board01_CH2->attach(uiQwtPlot[board_index*9+4]);
    board->tenSecCurveGrid_Board01_CH3 = new QwtPlotGrid();
    board->tenSecCurveGrid_Board01_CH3->enableXMin( true );
    board->tenSecCurveGrid_Board01_CH3->enableYMin( true );
    board->tenSecCurveGrid_Board01_CH3->setMajorPen(Qt::lightGray, 0, Qt::SolidLine);
    board->tenSecCurveGrid_Board01_CH3->setMinorPen(Qt::lightGray, 0 , Qt::DotLine);
    board->tenSecCurveGrid_Board01_CH3->attach(uiQwtPlot[board_index*9+5]);
    board->hundredSecCurveGrid_Board01_CH1 = new QwtPlotGrid();
    board->hundredSecCurveGrid_Board01_CH1->enableXMin( true );
    board->hundredSecCurveGrid_Board01_CH1->enableYMin( true );
    board->hundredSecCurveGrid_Board01_CH1->setMajorPen(Qt::lightGray, 0, Qt::SolidLine);
    board->hundredSecCurveGrid_Board01_CH1->setMinorPen(Qt::lightGray, 0 , Qt::DotLine);
    board->hundredSecCurveGrid_Board01_CH1->attach(uiQwtPlot[board_index*9+6]);
    board->hundredSecCurveGrid_Board01_CH2 = new QwtPlotGrid();
    board->hundredSecCurveGrid_Board01_CH2->enableXMin( true );
    board->hundredSecCurveGrid_Board01_CH2->enableYMin( true );
    board->hundredSecCurveGrid_Board01_CH2->setMajorPen(Qt::lightGray, 0, Qt::SolidLine);
    board->hundredSecCurveGrid_Board01_CH2->setMinorPen(Qt::lightGray, 0 , Qt::DotLine);
    board->hundredSecCurveGrid_Board01_CH2->attach(uiQwtPlot[board_index*9+7]);
    board->hundredSecCurveGrid_Board01_CH3 = new QwtPlotGrid();
    board->hundredSecCurveGrid_Board01_CH3->enableXMin( true );
    board->hundredSecCurveGrid_Board01_CH3->enableYMin( true );
    board->hundredSecCurveGrid_Board01_CH3->setMajorPen(Qt::lightGray, 0, Qt::SolidLine);
    board->hundredSecCurveGrid_Board01_CH3->setMinorPen(Qt::lightGray, 0 , Qt::DotLine);
    board->hundredSecCurveGrid_Board01_CH3->attach(uiQwtPlot[board_index*9+8]);

    uiQwtPlot[board_index*9]->setAxisTitle(QwtPlot::xBottom, QStringLiteral("时间轴(X1)"));
    uiQwtPlot[board_index*9]->setAxisTitle(QwtPlot::yLeft, QStringLiteral("mA"));
    uiQwtPlot[board_index*9+1]->setAxisTitle(QwtPlot::xBottom, QStringLiteral("时间轴(X1)"));
    uiQwtPlot[board_index*9+1]->setAxisTitle(QwtPlot::yLeft, QStringLiteral("mA"));
    uiQwtPlot[board_index*9+2]->setAxisTitle(QwtPlot::xBottom, QStringLiteral("时间轴(X1)"));
    uiQwtPlot[board_index*9+2]->setAxisTitle(QwtPlot::yLeft, QStringLiteral("mA"));
    uiQwtPlot[board_index*9+3]->setAxisTitle(QwtPlot::xBottom, QStringLiteral("时间轴(X1)"));
    uiQwtPlot[board_index*9+3]->setAxisTitle(QwtPlot::xBottom, QStringLiteral("时间轴(X1)"));
    uiQwtPlot[board_index*9+4]->setAxisTitle(QwtPlot::xBottom, QStringLiteral("时间轴(X1)"));
    uiQwtPlot[board_index*9+4]->setAxisTitle(QwtPlot::yLeft, QStringLiteral("mA"));
    uiQwtPlot[board_index*9+5]->setAxisTitle(QwtPlot::yLeft, QStringLiteral("mA"));
    uiQwtPlot[board_index*9+5]->setAxisTitle(QwtPlot::yLeft, QStringLiteral("mA"));
    uiQwtPlot[board_index*9+6]->setAxisTitle(QwtPlot::xBottom, QStringLiteral("时间轴(X1)"));
    uiQwtPlot[board_index*9+6]->setAxisTitle(QwtPlot::yLeft, QStringLiteral("mA"));
    uiQwtPlot[board_index*9+7]->setAxisTitle(QwtPlot::xBottom, QStringLiteral("时间轴(X1)"));
    uiQwtPlot[board_index*9+7]->setAxisTitle(QwtPlot::yLeft, QStringLiteral("mA"));
    uiQwtPlot[board_index*9+8]->setAxisTitle(QwtPlot::xBottom, QStringLiteral("时间轴(X1)"));
    uiQwtPlot[board_index*9+8]->setAxisTitle(QwtPlot::yLeft, QStringLiteral("mA"));


}

void MainWindow::initCurveData()
{

    QwtPlot * a[72] = {ui->qwtPlot_Board01_oneSec_ch01,ui->qwtPlot_Board01_oneSec_ch02,ui->qwtPlot_Board01_oneSec_ch03,
                       ui->qwtPlot_Board01_tenSec_ch01,ui->qwtPlot_Board01_tenSec_ch02,ui->qwtPlot_Board01_tenSec_ch03,
                       ui->qwtPlot_Board01_hundredSec_ch01,ui->qwtPlot_Board01_hundredSec_ch02,ui->qwtPlot_Board01_hundredSec_ch03,
                       ui->qwtPlot_Board02_oneSec_ch01,ui->qwtPlot_Board02_oneSec_ch02,ui->qwtPlot_Board02_oneSec_ch03,
                       ui->qwtPlot_Board02_tenSec_ch01,ui->qwtPlot_Board02_tenSec_ch02,ui->qwtPlot_Board02_tenSec_ch03,
                       ui->qwtPlot_Board02_hundredSec_ch01,ui->qwtPlot_Board02_hundredSec_ch02,ui->qwtPlot_Board02_hundredSec_ch03,
                       ui->qwtPlot_Board03_oneSec_ch01,ui->qwtPlot_Board03_oneSec_ch02,ui->qwtPlot_Board03_oneSec_ch03,
                       ui->qwtPlot_Board03_tenSec_ch01,ui->qwtPlot_Board03_tenSec_ch02,ui->qwtPlot_Board03_tenSec_ch03,
                       ui->qwtPlot_Board03_hundredSec_ch01,ui->qwtPlot_Board03_hundredSec_ch02,ui->qwtPlot_Board03_hundredSec_ch03,
                       ui->qwtPlot_Board04_oneSec_ch01,ui->qwtPlot_Board04_oneSec_ch02,ui->qwtPlot_Board04_oneSec_ch03,
                       ui->qwtPlot_Board04_tenSec_ch01,ui->qwtPlot_Board04_tenSec_ch02,ui->qwtPlot_Board04_tenSec_ch03,
                       ui->qwtPlot_Board04_hundredSec_ch01,ui->qwtPlot_Board04_hundredSec_ch02,ui->qwtPlot_Board04_hundredSec_ch03,
                       ui->qwtPlot_Board05_oneSec_ch01,ui->qwtPlot_Board05_oneSec_ch02,ui->qwtPlot_Board05_oneSec_ch03,
                       ui->qwtPlot_Board05_tenSec_ch01,ui->qwtPlot_Board05_tenSec_ch02,ui->qwtPlot_Board05_tenSec_ch03,
                       ui->qwtPlot_Board05_hundredSec_ch01,ui->qwtPlot_Board05_hundredSec_ch02,ui->qwtPlot_Board05_hundredSec_ch03,
                       ui->qwtPlot_Board06_oneSec_ch01,ui->qwtPlot_Board06_oneSec_ch02,ui->qwtPlot_Board06_oneSec_ch03,
                       ui->qwtPlot_Board06_tenSec_ch01,ui->qwtPlot_Board06_tenSec_ch02,ui->qwtPlot_Board06_tenSec_ch03,
                       ui->qwtPlot_Board06_hundredSec_ch01,ui->qwtPlot_Board06_hundredSec_ch02,ui->qwtPlot_Board06_hundredSec_ch03,
                       ui->qwtPlot_Board07_oneSec_ch01,ui->qwtPlot_Board07_oneSec_ch02,ui->qwtPlot_Board07_oneSec_ch03,
                       ui->qwtPlot_Board07_tenSec_ch01,ui->qwtPlot_Board07_tenSec_ch02,ui->qwtPlot_Board07_tenSec_ch03,
                       ui->qwtPlot_Board07_hundredSec_ch01,ui->qwtPlot_Board07_hundredSec_ch02,ui->qwtPlot_Board07_hundredSec_ch03,
                       ui->qwtPlot_Board08_oneSec_ch01,ui->qwtPlot_Board08_oneSec_ch02,ui->qwtPlot_Board08_oneSec_ch03,
                       ui->qwtPlot_Board08_tenSec_ch01,ui->qwtPlot_Board08_tenSec_ch02,ui->qwtPlot_Board08_tenSec_ch03,
                       ui->qwtPlot_Board08_hundredSec_ch01,ui->qwtPlot_Board08_hundredSec_ch02,ui->qwtPlot_Board08_hundredSec_ch03,
                       };
    tabWidget[0] = ui->tabWidget_01;
    tabWidget[1] = ui->tabWidget_02;
    tabWidget[2] = ui->tabWidget_03;
    tabWidget[3] = ui->tabWidget_04;
    tabWidget[4] = ui->tabWidget_05;
    tabWidget[5] = ui->tabWidget_06;
    tabWidget[6] = ui->tabWidget_07;
    tabWidget[7] = ui->tabWidget_08;


    for(int i=0;i<8;i++){
        boardInitData(boards[i],a,i);
    }
}

void MainWindow::addSerialPort()
{
    QStringList portName;

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        portName << info.portName();
    }

    portName.sort(Qt::CaseSensitive);

    ui->comboBox_SerialPort->addItems(portName);
    ui->comboBox_SerialPort->setCurrentIndex(1);
}

void MainWindow::selectSaveDataFilePath()
{
    saveFilePath = QFileDialog::getExistingDirectory(this, QStringLiteral("数据存储目标"),
                        saveFilePath, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(!saveFilePath.isEmpty())
    {
        ui->action_start->setEnabled(true);
        ui->statusBar->showMessage(saveFilePath, 3000);
    }
}

void MainWindow::on_lineEdit_Scale_CH1_textChanged(const QString &arg1)
{
    bool toDouble = false;

    scale_CH1 = arg1.toDouble(&toDouble);

    if (!toDouble)
        scale_CH1 = 10.00;

//    Calculator_CH1->setScale(scale_CH1*10.00);
}

void MainWindow::on_lineEdit_Scale_CH2_textChanged(const QString &arg1)
{
    bool toDouble = false;

    scale_CH2 = arg1.toDouble(&toDouble);

    if (!toDouble)
        scale_CH2 = 10.00;
}

void MainWindow::on_lineEdit_Scale_CH3_textChanged(const QString &arg1)
{
    bool toDouble = false;

    scale_CH3 = arg1.toDouble(&toDouble);

    if (!toDouble)
        scale_CH3 = 10.00;
}

void MainWindow::on_tabWidget_01_currentChanged(int index)
{
    chTabIndex = index;

    this->updata_biasStd_Display();
}
void MainWindow::on_tabWidget_02_currentChanged(int index)
{
    chTabIndex = index;

    this->updata_biasStd_Display();
}
void MainWindow::on_tabWidget_03_currentChanged(int index)
{
    chTabIndex = index;

    this->updata_biasStd_Display();
}
void MainWindow::on_tabWidget_04_currentChanged(int index)
{
    chTabIndex = index;

    this->updata_biasStd_Display();
}
void MainWindow::on_tabWidget_05_currentChanged(int index)
{
    chTabIndex = index;

    this->updata_biasStd_Display();
}
void MainWindow::on_tabWidget_06_currentChanged(int index)
{
    chTabIndex = index;

    this->updata_biasStd_Display();
}
void MainWindow::on_tabWidget_07_currentChanged(int index)
{
    chTabIndex = index;

    this->updata_biasStd_Display();
}
void MainWindow::on_tabWidget_08_currentChanged(int index)
{
    chTabIndex = index;

    this->updata_biasStd_Display();
}
void MainWindow::on_tabWidget_currentChanged(int index)
{
    deviceTabIndex = index;
    this->updata_biasStd_Display();
}

void MainWindow::switch_sub_tab_display(int TabIndex,int subTabIndex){
    ui->listWidget->clear();
    switch (subTabIndex)
    {
    case 0 :
        meanFog_Disp = oneSecMean[TabIndex];
        zeroBias_Disp = oneSecStdDeviation[TabIndex];
        biasStd_Disp = 0;
        listWidgetCh1 = oneSecData[TabIndex];
        listWidgetCh2 = oneSecData[TabIndex+8];
        listWidgetCh3 = oneSecData[TabIndex+16];
        break;


    case 1 :
        meanFog_Disp = tenSecMean[TabIndex];
        zeroBias_Disp = tenSecStdDeviation[TabIndex];
        biasStd_Disp = 0;
        listWidgetCh1 = tenSecData[TabIndex];
        listWidgetCh2 = tenSecData[TabIndex+8];
        listWidgetCh3 = tenSecData[TabIndex+16];
        break;


    case 2 :
        meanFog_Disp = hundredSecMean[TabIndex];
        zeroBias_Disp = hundredSecStdDeviation[TabIndex];
        biasStd_Disp = 0;
        listWidgetCh1 = hundredSecData[TabIndex];
        listWidgetCh2 = hundredSecData[TabIndex+8];
        listWidgetCh3 = hundredSecData[TabIndex+16];
//                 meanFog_Disp_rm2 = meanFog_CH3_rm2,
//                 zeroBias_Disp_rm2 = zeroBias_CH3_rm2,
//                 biasStd_Disp_rm2 = biasStd_CH3_rm2;
        break;
    case 3 :
        meanFog_Disp = oneSecMean[TabIndex+8];
        zeroBias_Disp = oneSecStdDeviation[TabIndex+8];
        biasStd_Disp = 0;
        listWidgetCh1 = oneSecData[TabIndex];
        listWidgetCh2 = oneSecData[TabIndex+8];
        listWidgetCh3 = oneSecData[TabIndex+16];
        break;
    case 4 :
        meanFog_Disp = tenSecMean[TabIndex+8];
        zeroBias_Disp = tenSecStdDeviation[TabIndex+8];
        biasStd_Disp = 0;
        listWidgetCh1 = tenSecData[TabIndex];
        listWidgetCh2 = tenSecData[TabIndex+8];
        listWidgetCh3 = tenSecData[TabIndex+16];
        break;
    case 5 :
        meanFog_Disp = hundredSecMean[TabIndex+8];
        zeroBias_Disp = hundredSecStdDeviation[TabIndex+8];
        biasStd_Disp = 0;
        listWidgetCh1 = hundredSecData[TabIndex];
        listWidgetCh2 = hundredSecData[TabIndex+8];
        listWidgetCh3 = hundredSecData[TabIndex+16];
        break;
    case 6 :
        meanFog_Disp = oneSecMean[TabIndex+16];
        zeroBias_Disp = oneSecStdDeviation[TabIndex+16];
        biasStd_Disp = 0;
        listWidgetCh1 = oneSecData[TabIndex];
        listWidgetCh2 = oneSecData[TabIndex+8];
        listWidgetCh3 = oneSecData[TabIndex+16];
        break;
    case 7 :
        meanFog_Disp = tenSecMean[TabIndex+16];
        zeroBias_Disp = tenSecStdDeviation[TabIndex+16];
        biasStd_Disp = 0;
        listWidgetCh1 = tenSecData[TabIndex];
        listWidgetCh2 = tenSecData[TabIndex+8];
        listWidgetCh3 = tenSecData[TabIndex+16];
        break;
    case 8 :
        meanFog_Disp = hundredSecMean[TabIndex+16];
        zeroBias_Disp = hundredSecStdDeviation[TabIndex+16];
        biasStd_Disp = 0;
        listWidgetCh1 = hundredSecData[TabIndex];
        listWidgetCh2 = hundredSecData[TabIndex+8];
        listWidgetCh3 = hundredSecData[TabIndex+16];
        break;
    default: ;
    }
    //qDebug()<<"listWidgetCh1"<<listWidgetCh1;
    ui->listWidget->addItem(QString("%1__%2__%3").arg(listWidgetCh1).arg(listWidgetCh2).arg(listWidgetCh3));
}

void MainWindow::updata_biasStd_Display(void)
{
    chTabIndex = tabWidget[deviceTabIndex]->currentIndex();
    switch_sub_tab_display(deviceTabIndex,chTabIndex);

    ui->label_meanFog->setText(QString("%1").arg(meanFog_Disp, 0, 'f', 6).toLatin1());
    //ui->label_meanFog->setText(QString("%1").arg(0.0, 0, 'f', 6).toLatin1());
    ui->label_zeroBias->setText(QString("%1").arg(zeroBias_Disp, 0, 'f', 6).toLatin1());
    ui->label_biasStability->setText(QString("%1").arg(biasStd_Disp, 0, 'f', 6).toLatin1());
}

void MainWindow::on_lineEdit_FogNum_CH1_textChanged(const QString &arg1)
{
    if (arg1.isEmpty())
        fogNum_CH1 = "Pulse_CH1";
    else
        fogNum_CH1 = arg1.toUpper();
}

void MainWindow::on_lineEdit_FogNum_CH2_textChanged(const QString &arg1)
{
    if (arg1.isEmpty())
        fogNum_CH2 = "Pulse_CH2";
    else
        fogNum_CH2 = arg1.toUpper();
}

void MainWindow::on_lineEdit_FogNum_CH3_textChanged(const QString &arg1)
{
    if (arg1.isEmpty())
        fogNum_CH3 = "Pulse_CH3";
    else
        fogNum_CH3 = arg1.toUpper();
}

void MainWindow::on_comboBox_SerialPort_currentIndexChanged(const QString &arg1)
{
    curCOMPort = arg1;
}

void MainWindow::on_lineEdit_editingFinished()
{
    QString str = ui->lineEdit->text();
    unsigned int rate = str.toUInt();
    qDebug()<<"更新率";
    emit sendrenew(rate);
}

void MainWindow::on_comboBox_SerialPort_5_currentIndexChanged(const QString &arg1)
{
    curbundrate = arg1;
}
