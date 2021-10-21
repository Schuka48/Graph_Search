#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "graph/graph.h"
#include "genetic_algorithm/population.h"
#include "forms/settings/settings.h"
#include "genetic_algorithm/params.h"
#include "genetic_algorithm/manager.h"

#include <QMainWindow>
#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>

enum  Errors {
    openFile_Error = 1,
    graphSize_Error = 2,
    fileFormat_Error = 3
};

namespace Ui {
class StartWindow;
}

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

    void show_result();
    void print_result();

public slots:
    void on_algorithm_finished();

private slots:
    void on_action_triggered();

    void on_pushButton_clicked();

    void on_action_5_triggered();

    void on_action_2_triggered();

private:
    Ui::StartWindow *ui;

    Graph* graph;

    Graph* result_graph;

    Params* algorithm_params;

    Manager* algorithm_manager;

    QList<Population*> result;
};

#endif // STARTWINDOW_H
