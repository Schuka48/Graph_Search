#ifndef SETTINGS_H
#define SETTINGS_H

#include "genetic_algorithm/params.h"

#include <QMainWindow>
#include <QDebug>

namespace Ui {
class Settings;
}

class Settings : public QMainWindow
{
    Q_OBJECT

public:
    explicit Settings(Params* &parametrs, QWidget *parent = nullptr);
    ~Settings();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Settings *ui;
    Params* params;
};

#endif // SETTINGS_H
