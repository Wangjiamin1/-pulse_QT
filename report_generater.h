#ifndef REPORT_GENERATER_H
#define REPORT_GENERATER_H

#include <QThread>
#include <QTextCodec>
#include <QPdfWriter>
#include <QFile>
#include <QPainter>
#include <QPageSize>
#include <QDebug>
#include <QTime>
#include <QDate>
#include <QString>
#include <QPixmap>
#include <QImage>

class Report_Generater : public QThread
{
    Q_OBJECT
public:
    Report_Generater();

    QString filePath;

    QString fogNum;
    QString expCondition;

    double fogMean;
    double fogScale;
    double zeroBias;
    double biasStability;
    double fogMean_rm2;
    double zeroBias_rm2;
    double biasStability_rm2;
    double randomWalk;
    QImage curveImage;

protected:
    void run();
};

#endif // REPORT_GENERATER_H
