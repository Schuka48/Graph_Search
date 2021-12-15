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
    this->setWindowTitle("Генетический алгоритм размещения графа на линейке");
    this->ui->pushButton_2->setEnabled(false);

    this->author = new Authors(this);
    this->schedule = nullptr;
    this->help = new Help(this);
    this->settings = nullptr;
}

StartWindow::~StartWindow()
{
    delete ui;
    delete algorithm_params;
    this->author->deleteLater();
    this->schedule->deleteLater();
    this->help->deleteLater();
    this->settings->deleteLater();
}

int StartWindow::printResult()
{
    QFileDialog* fd = new QFileDialog(this);
    QString save_file_name = fd->getSaveFileName(this);

    if(save_file_name.isEmpty()) return 1;

    QFile save_file(save_file_name);

    if(save_file.open(QIODevice::WriteOnly)) {

        QTextStream out(&save_file);

        QString str = "";

        if(this->result_graph == nullptr) {
            QMessageBox::information(this, "Предупреждение", "Необходимо загрузить граф!");
            return 1;
        }

        for(auto vertexs: this->result_graph->get_nodes())
        {
            str = str + QString::number(vertexs->get_id()) + " - ";
        }
        int pos = str.lastIndexOf("-");
        str = str.remove(pos, 2);
        int strLen = str.length();

        out << str << endl;
        out << "Summ is: " << QString::number(this->result_graph->get_sum());

        out << endl;
        str.clear();

        for(int i = 0; i < strLen - 1; i++) {
            str += "-";
        }
        out << str << endl;
        str.clear();

        out << "Results of the best individual in each generation: " << endl;

        for(int i = 0; i < this->BestIntermediateResults.size(); i++)
        {
            out << QString::number(i + 1) << ". " << "The best individual: "
                << this->BestIntermediateResults[i] << endl;
        }
        for(int i = 0; i < strLen - 1; i++) {
            str += "-";
        }
        out << str;
    }
    else {
        return 1;
    }
    save_file.close();
    fd->deleteLater();
    return 0;
}

void StartWindow::on_algorithm_finished()
{
    if(this->schedule != nullptr) {
        delete this->schedule;
    }
    this->result = algorithm_manager->get_result();
    if (this->result_graph->get_sum() > result[0]->get_best_individ()->get_sum()) {
        this->result_graph = result[0]->get_best_individ();
        this->BestIntermediateResults = result[0]->GetIntermediateResults();
    }
    ui->label_3->setText("Алгоритм завершился. Сохраните результат!");
    ui->label_4->setText(ui->label_4->text() + " " + QString::number(result[0]->get_best_individ()->get_sum()));
    this->IntermediateResults = result[0]->GetIntermediateResults();
    schedule = new Schedule(this->IntermediateResults);
    this->ui->pushButton_2->setEnabled(true);
    this->ui->pushButton->setEnabled(true);

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

    this->result_graph = this->graph;

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

    ui->label_3->setText("Запущен. Ожидайте завершения!");

    this->ui->pushButton_2->setEnabled(false);
    this->ui->pushButton->setEnabled(false);

    this->algorithm_manager = new Manager(graph, *algorithm_params, algorithm_params->get_thread_count());

    connect(algorithm_manager, &Manager::finish, this, &StartWindow::on_algorithm_finished);

    algorithm_manager->start();

//    result_graph = this->population->get_best_individ();

//    delete population;
}

void StartWindow::on_action_5_triggered()
{
    settings = new Settings(algorithm_params);
    this->settings->show();
}

void StartWindow::on_action_2_triggered()
{
    if(this->printResult()) {
        return;
    }
}

void StartWindow::on_pushButton_2_clicked()
{
    this->schedule->show();
}

void StartWindow::on_action_6_triggered()
{
    this->help->show();
}

void StartWindow::on_action_7_triggered()
{
    this->author->show();
}
