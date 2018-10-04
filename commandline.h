﻿#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include <QMainWindow>
#include "hstdlib.h"
namespace Ui {
class commandline;
}

class commandline : public QMainWindow
{
    Q_OBJECT

public:
    explicit commandline(QWidget *parent = nullptr);
    ~commandline();   
private slots:

    void on_lineEdit_returnPressed();

private:
    Ui::commandline *ui;
};

#endif // COMMANDLINE_H
