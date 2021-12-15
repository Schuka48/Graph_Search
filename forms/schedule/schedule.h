#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QMainWindow>
#include <graphic/qcustomplot.h>

namespace Ui {
class Schedule;
}

class Schedule : public QMainWindow
{
    Q_OBJECT

public:
    explicit Schedule(QVector<int> IntermediateResults, QWidget *parent = nullptr);
    ~Schedule();

private:
    Ui::Schedule *ui;
    int ResultMax = 0;
    QVector<double> Results;    // Вектор лучших особей в своей популяции
    QCustomPlot *wGraphic;      // Объявляем объект QCustomPlot
    QCPCurve *verticalLine;     // Объявляем объект для вертикальной линии
    QCPItemTracer *tracer;      // Трасировщик по точкам графика

private slots:
    void slotMousePress(QMouseEvent * event);
    void slotMouseMove(QMouseEvent * event);
    void slotMouseRelease(QMouseEvent * event);
};

#endif // SCHEDULE_H
