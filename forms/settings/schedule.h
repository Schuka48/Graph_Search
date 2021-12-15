#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QDialog>

namespace Ui {
class Schedule;
}

class Schedule : public QDialog
{
    Q_OBJECT

public:
    explicit Schedule(QWidget *parent = nullptr);
    ~Schedule();

private:
    Ui::Schedule *ui;
};

#endif // SCHEDULE_H
