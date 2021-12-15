#include "authors.h"
#include "ui_authors.h"

Authors::Authors(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Authors)
{
    ui->setupUi(this);
    this->setWindowTitle("Генетический алгоритм размещения графа на линейке");
    this->setWindowFlag(Qt::WindowMinMaxButtonsHint, false);
}

Authors::~Authors()
{
    delete ui;
}
