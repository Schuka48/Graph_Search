#include "settings.h"
#include "ui_settings.h"

Settings::Settings(Params *&parametrs, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::WindowMinMaxButtonsHint, false);
    this->params = parametrs;
//    this->params->set_population_size(parametrs->get_population_size());
//    this->params->set_iter_count(parametrs->get_iter_count());
//    this->params->set_mutation_potention(parametrs->get_mutation_potention());

    this->ui->spinBox->setValue(this->params->get_population_size());
    this->ui->spinBox_2->setValue(this->params->get_iter_count());
    this->ui->doubleSpinBox->setValue(this->params->get_mutation_potention());
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_pushButton_clicked()
{
    this->params->set_population_size(this->ui->spinBox->value());
    this->params->set_iter_count(this->ui->spinBox_2->value());
    this->params->set_mutation_potention(this->ui->doubleSpinBox->value());
    this->params->set_num_steps_without_improvment(this->ui->spinBox_3->value());

    qDebug() << this->params << " " << this->params->get_num_steps_without_improvment();

    this->close();
}
