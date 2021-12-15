#include "help.h"
#include "ui_help.h"

Help::Help(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
    this->setWindowTitle("Генетический алгоритм размещения графа на линейке");
}

Help::~Help()
{
    delete ui;
}
