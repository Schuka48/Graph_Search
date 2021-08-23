#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "graph.h"


#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

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

    void on_action_4_triggered();

private:
    Ui::MainWindow *ui;
    Graph gr;
    QFile* gr_open_file;
    QFile* gr_save_file;
    QFileDialog* f_dialog;
};
#endif // MAINWINDOW_H
