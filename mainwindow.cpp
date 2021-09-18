#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    graph = new Graph();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
//    QString file_path = QFileDialog::getOpenFileName(this);
//    if(file_path.isEmpty()) return;
    QString file_path = "data.txt";
    QFile open_file(file_path); // поменять на выбор файла
    if(!open_file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Warning!", "Файл не открылся!");
        return;
    }

    graph->LoadFromFile(&open_file);

    open_file.close();

}
