#include "startwindow.h"
#include "ui_startwindow.h"

StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    graph = nullptr;
    result_graph = nullptr;
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
    if(graph != nullptr)
        delete graph;

    graph = new Graph();

    QString file_path = "adjacency_matrix.txt";
    QFile open_file(file_path); // поменять на выбор файла
    if(!open_file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Warning!", "Файл не открылся!");
        return;
    }
    int error = 0;
    graph->LoadFromFile(&open_file, error);

    // switch case если вернули false;
    switch (error) {
    case 1: QMessageBox::warning(this, "Предупреждение", "Невозможно открыть файл"); break;
    case 2: QMessageBox::warning(this, "Предупреждение", "Размер графа меньше допустимого значения,"
                                                         " для ознакомления с параметрами графа обратитесь к справке."); break;
    case 3: QMessageBox::warning(this, "Предупреждение", "Неправильный формат файла, обартитесь к справке"); break;
    }

    open_file.close();
}

void StartWindow::on_pushButton_clicked()
{
    // запуск Генетического алгоритма

    qDebug() << algorithm_params << " " << algorithm_params->get_iter_count();
    if(graph == nullptr) {
        QMessageBox::warning(this, "Предупреждение", "Необходимо загрузить модель графа.");
        return;

    }
    else if(graph->get_node_count() == 0 || graph->get_sum() == 0)
    {
        QMessageBox::warning(this, "Предупреждение", "Необходимо загрузить модель графа.");
        return;
    }
    population = new Population(graph, *algorithm_params);
    population->start();

    result_graph = this->population->get_best_individ();
    delete graph;
}

void StartWindow::on_action_5_triggered()
{
    Settings* settings = new Settings(algorithm_params);
    settings->show();
}
