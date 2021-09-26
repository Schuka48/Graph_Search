#include "startwindow.h"
#include "ui_startwindow.h"

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    graph = new Graph();
    algorithm_params = new Params();
}

StartWindow::~StartWindow()
{
    delete ui;
    delete graph;
    delete algorithm_params;
    delete population;
}

void StartWindow::on_action_triggered()
{
    QString file_path = "data.txt";
    QFile open_file(file_path); // поменять на выбор файла
    if(!open_file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Warning!", "Файл не открылся!");
        return;
    }
    int error = 0;
    graph->LoadFromFile(&open_file, error);

    // switch case если вернули false;

    open_file.close();
}

void StartWindow::on_pushButton_clicked()
{
    // запуск Генетического алгоритма

    QString str("");
    qDebug() << algorithm_params << " " << algorithm_params->get_iter_count();

    if(graph->get_node_count() == 0 || graph->get_sum() == 0)
    {
        QMessageBox::warning(this, "Предупреждение", "Необходимо загрузить модель графа.");
        return;
    }
    result_graph = new Graph(*graph);


    population = new Population(result_graph, *algorithm_params);
//    population->start();
}

void StartWindow::on_action_5_triggered()
{
    Settings* settings = new Settings(algorithm_params);
    settings->show();
}
