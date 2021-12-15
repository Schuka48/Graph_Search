#include "schedule.h"
#include "ui_schedule.h"

Schedule::Schedule(QVector<int> IntermediateResults, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Schedule)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::WindowMinMaxButtonsHint, false);
    this->setWindowTitle("Генетический алгоритм размещения графа на линейке");

    for(int i = 0; i < IntermediateResults.size(); i++) {
        this->Results.push_back(static_cast<double>(IntermediateResults[i]));
    }

    int ResultSize = this->Results.length();

    for(auto tmp: this->Results) {
        if(tmp > this->ResultMax)
            this->ResultMax = tmp;
    }

    // Объявление полотна графика
    wGraphic = new QCustomPlot();
    ui->gridLayout_2->addWidget(wGraphic,1,0,1,1);

    // Инициализируем вертикальную линию
    verticalLine = new QCPCurve(wGraphic->xAxis, wGraphic->yAxis);

    // Подключаем сигналы событий мыши от полотна графика к слотам для их обработки
    connect(wGraphic, &QCustomPlot::mousePress, this, &Schedule::slotMousePress);
    connect(wGraphic, &QCustomPlot::mouseMove, this, &Schedule::slotMouseMove);
    connect(wGraphic, &QCustomPlot::mouseRelease, this, &Schedule::slotMouseRelease);

    // создаём вектора для вертикальной линии
    QVector<double> x1(2) , y1(2);
        x1[0] = 0;
        y1[0] = 0;
        x1[1] = 0;
        y1[1] = this->ResultMax + 50;

     wGraphic->addPlottable(verticalLine);   // Добавляем линию на полотно
     verticalLine->setName("Vertical");      // Устанавливаем ей наименование
     verticalLine->setData(x1, y1);            // И устанавливаем координаты

    // Вектор координат по оси абсцисс
    QVector<double> x;
    for (double i = 0; i < ResultSize; i++) {
        x.push_back(i);
    }
    // Добавляем график на полотно
    wGraphic->addGraph(wGraphic->xAxis, wGraphic->yAxis);
    wGraphic->graph(0)->setData(x, this->Results);

    // Инициализируем трассировщик
    tracer = new QCPItemTracer(wGraphic);
    tracer->setGraph(wGraphic->graph(0));   // Трассировщик будет работать с графиком

    // Подписываем оси координат
    wGraphic->xAxis->setLabel("Итерация Генетического алгоритма");
    wGraphic->yAxis->setLabel("Лучшая особь в популяции");

    // Устанавливаем максимальные и минимальные значения координат
    wGraphic->xAxis->setRange(0, ResultSize);
    wGraphic->yAxis->setRange(0, ResultMax + 10);

    // Отрисовываем содержимое полотна
    wGraphic->replot();
}

Schedule::~Schedule()
{
    delete ui;
}

void Schedule::slotMousePress(QMouseEvent *event)
{
    // Определяем координату X на графике, где был произведён клик мышью
    double coordX = wGraphic->xAxis->pixelToCoord(event->pos().x());

    // Подготавливаем координаты по оси X для переноса вертикальной линии
    QVector<double> x(2), y(2);
    x[0] = coordX;
    y[0] = 0;
    x[1] = coordX;
    y[1] = ResultMax + 10;

    // Устанавливаем новые координаты
    verticalLine->setData(x, y);

    // По координате X клика мыши определим ближайшие координаты для трассировщика
    tracer->setGraphKey(coordX);

    // Выводим координаты точки графика, где установился трассировщик, в lineEdit
    ui->label->setText("x: " + QString::number(tracer->position->key()) +
                          " y: " + QString::number(tracer->position->value()));
    wGraphic->replot(); // Перерисовываем содержимое полотна графика
}

void Schedule::slotMouseMove(QMouseEvent *event)
{
    /* Если при передвижении мыши, её кнопки нажаты,
     * то вызываем отработку координат мыши
     * через слот клика
     * */
    if(QApplication::mouseButtons()) slotMousePress(event);
}

void Schedule::slotMouseRelease(QMouseEvent *event)
{
    ui->label->setText("График эволюции популяции Генетического алгоритма размещения графа на линейке");
}
