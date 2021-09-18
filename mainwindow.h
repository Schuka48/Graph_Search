#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "graph.h"
#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_triggered();

private:
    Ui::MainWindow *ui;
    Graph* graph;
};
#endif // MAINWINDOW_H
