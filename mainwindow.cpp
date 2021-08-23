#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    f_dialog = new QFileDialog(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
    QString file_name = f_dialog->getOpenFileName(this);
    if(file_name.isEmpty())
        return;

    gr_open_file = new QFile(file_name);
    if(!gr_open_file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Информация", "Проверьте целостность выбранного вами файла!");
        return;
    }
    if(!gr.LoadFromFile(gr_open_file))
    {
        QMessageBox::critical(this, "Информация", "Проверьте целостность выбранного вами файла!");
        return;
    }

}

void MainWindow::on_action_4_triggered()
{

    if(!gr.get_graph_size()) {
        QMessageBox::warning(this, "Предупреждение", "Необходимо загрузить исходные данные!");
        return;
    }
    gr.calculate();
}
