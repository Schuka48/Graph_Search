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
    this->setWindowIcon(QPixmap(":/algorithm.png"));
}

StartWindow::~StartWindow()
{
    delete ui;
    delete algorithm_params;
}

void StartWindow::on_algorithm_finished()
{
    this->result = algorithm_manager->get_result();
    ui->label_3->setText("Алгоритм завершился. Сохраните результат!");
    ui->label_4->setText(ui->label_4->text() + " " + QString::number(result[0]->get_best_individ()->get_sum()));
}

void StartWindow::on_action_triggered()
{
    if(graph != nullptr)
        delete graph;

    graph = new Graph();

    QFileDialog* fd = new QFileDialog(this);

    QString file_path = fd->getOpenFileName(this);

    if(file_path.isEmpty()) return;

    QFile open_file(file_path); // поменять на выбор файла
    if(!open_file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Warning!", "Файл не открылся!");
        delete graph;
        graph = nullptr;
        return;
    }
    int error = 0;
    graph->LoadFromFile(&open_file, error);

    // switch case если вернули false;
    switch (error) {
    case openFile_Error: {
        QMessageBox::warning(this, "Предупреждение", "Невозможно открыть файл");
        delete graph;
        graph = nullptr;
        break;
        }
    case graphSize_Error: QMessageBox::warning(this, "Предупреждение", "Размер графа меньше допустимого значения,"
                                                         " для ознакомления с параметрами графа обратитесь к справке."); break;
    case fileFormat_Error: QMessageBox::warning(this, "Предупреждение", "Неправильный формат файла, обартитесь к справке"); break;
    }

    open_file.close();
}

void StartWindow::on_pushButton_clicked()
{
    // запуск Генетического алгоритма

    ui->label_3->setText("Запущен. Ожидайте завершения!");

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

    this->algorithm_manager = new Manager(graph, *algorithm_params, algorithm_params->get_thread_count());

    connect(algorithm_manager, &Manager::finish, this, &StartWindow::on_algorithm_finished);

    algorithm_manager->start();

//    result_graph = this->population->get_best_individ();

    delete graph;
//    delete population;
}

void StartWindow::on_action_5_triggered()
{
    Settings* settings = new Settings(algorithm_params);
    settings->show();
}

void StartWindow::on_action_2_triggered()
{
    QFileDialog* fd = new QFileDialog(this);
    QString save_file_name = fd->getSaveFileName(this);
    if(save_file_name.isEmpty()) return;
    QFile save_file(save_file_name);
    if(save_file.open(QIODevice::WriteOnly)) {
        QTextStream out(&save_file);
        QString str = "";
        for(auto vertexs: this->result[0]->get_best_individ()->get_nodes())
        {
            str = str + QString::number(vertexs->get_id()) + " - ";
        }
        int pos = str.lastIndexOf("-");
        str = str.remove(pos, 2);
        out << str << endl;
        out << "Summ is: " << QString::number(result[0]->get_best_individ()->get_sum());
    }
    save_file.close();
    fd->deleteLater();
}
