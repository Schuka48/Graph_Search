#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "graph/graph.h"
#include "genetic_algorithm/population.h"
#include "forms/settings/settings.h"
#include "genetic_algorithm/params.h"

#include <QMainWindow>
#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>

namespace Ui {
class StartWindow;
}

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

private slots:
    void on_action_triggered();

    void on_pushButton_clicked();

    void on_action_5_triggered();

private:
    Ui::StartWindow *ui;

    Graph* graph;
    Graph* result_graph;

    Params* algorithm_params;

    Population* population;
};

#endif // STARTWINDOW_H
