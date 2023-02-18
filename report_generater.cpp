#include "report_generater.h"

#define LINE_WIDTH 100

#define X1 400
#define Y1 600
#define X2 2794
#define Y2 600
#define X3 X1
#define Y3 Y1+LINE_WIDTH*8
#define X4 X2
#define Y4 Y1+LINE_WIDTH*8

Report_Generater::Report_Generater()
{
    filePath.clear();

    fogNum = "N/A";
    expCondition = "N/A";

    fogMean = 0;
    fogScale = 1.00;
    zeroBias = 0;
    biasStability = 0;
    fogMean_rm2 = 0;
    zeroBias_rm2 = 0;
    biasStability_rm2 = 0;
    randomWalk = 0;
}

void Report_Generater::run()
{
    if (!filePath.isEmpty())
    {
        QFile PDF_file(filePath + "/" + fogNum + "_report.pdf");

        if (!PDF_file.open(QIODevice::WriteOnly))
            return ;

        QPdfWriter *PdfWriter = new QPdfWriter(&PDF_file);
        QPainter *painter = new QPainter(PdfWriter);
        QString currentDate = QDate::currentDate().toString("yyyy-MM-dd");
        PdfWriter->setPageSize(QPagedPaintDevice::A4);
        painter->scale(3, 3);
        painter->setPen(QColor(0, 0, 0, 255));
        painter->setFont(QFont("微软雅黑", 6, QFont::Normal));
        painter->drawText(1000, 450, QStringLiteral("航遨航空科技（西安）有限公司"));
        painter->drawLine(900, 500, 2294, 500);
        painter->setPen(QPen(Qt::black, 6, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->drawLine(X1, Y1, X2, Y2);
        painter->drawLine(X1, Y1+LINE_WIDTH*1, X2, Y2+LINE_WIDTH*1);
        painter->drawLine(X1, Y1+LINE_WIDTH*2, X2, Y2+LINE_WIDTH*2);
        painter->drawLine(X1, Y1+LINE_WIDTH*3, X2, Y2+LINE_WIDTH*3);
        painter->drawLine(X1, Y1+LINE_WIDTH*4, X2, Y2+LINE_WIDTH*4);
        painter->drawLine(X1, Y1+LINE_WIDTH*5, X2, Y2+LINE_WIDTH*5);
        painter->drawLine(X1, Y1+LINE_WIDTH*6, X2, Y2+LINE_WIDTH*6);
        painter->drawLine(X1, Y1+LINE_WIDTH*7, X2, Y2+LINE_WIDTH*7);
        painter->drawLine(X1, Y1+LINE_WIDTH*8, X2, Y2+LINE_WIDTH*8);
        painter->drawLine(X1, Y1, X3, Y3);
        painter->drawLine(900, 600, 900, 1400);
        painter->drawLine(1597, 600, 1597, 800);
        painter->drawLine(2097, 600, 2097, 800);
        painter->drawLine(1847, 800, 1847, 900);
        painter->drawLine(1847, 1000, 1847, Y4-100);
        painter->drawLine(X2, Y2, X4, Y4);
        painter->setFont(QFont("微软雅黑", 4, QFont::Normal));
        painter->drawText(420, 675, QStringLiteral("    产品类型："));
        painter->drawText(920, 675, QStringLiteral("脉冲仪表"));
        painter->drawText(1627, 675, QStringLiteral("    产品编号："));
        painter->drawText(2117, 675, fogNum);
        painter->drawText(420, 775, QStringLiteral("    标定进程："));
        painter->drawText(920, 775, expCondition);
        painter->drawText(1627, 775, QStringLiteral("    标定日期："));
        painter->drawText(2117, 775, currentDate);
        painter->drawText(420, 975, QStringLiteral("    标度因数："));
        painter->drawText(920, 975, QString("%1").arg(fogScale, 0, 'f', 4));
        painter->drawText(920, 875, QStringLiteral("           全数据"));
        painter->drawText(1867, 875, QStringLiteral("          去2分钟"));
        painter->drawText(420, 1075, QStringLiteral("    均    值："));
        painter->drawText(920, 1075, QString("%1").arg(fogMean, 0, 'f', 4));
        painter->drawText(1867, 1075, QString("%1").arg(fogMean_rm2, 0, 'f', 4));
        painter->drawText(420, 1175, QStringLiteral("    标 准 差："));
        painter->drawText(920, 1175, QString("%1").arg(zeroBias, 0, 'f', 4));
        painter->drawText(1867, 1175, QString("%1").arg(zeroBias_rm2, 0, 'f', 4));
        painter->drawText(420, 1275, QStringLiteral("  零偏稳定性："));
        painter->drawText(920, 1275, QString("%1").arg(biasStability, 0, 'f', 4));
        painter->drawText(1867, 1275, QString("%1").arg(biasStability_rm2, 0, 'f', 4));
        painter->drawText(420, 1375, QStringLiteral("    随机游走："));
//        painter->drawText(920, 1375, QString("%1").arg(randomWalk));   //待开发功能
        painter->drawText(920, 1375, QStringLiteral("待开发功能"));
        painter->drawText(1867, 1375, QStringLiteral("(平滑到100Hz计算值)"));
        painter->drawText(400, 1500, QStringLiteral("测试波形图："));
        painter->drawImage(QPoint(400,1550), curveImage);
        painter->end();

        delete painter;
        delete PdfWriter;
        PDF_file.close();
    }
}
