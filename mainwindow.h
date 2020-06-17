#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <QMap>
#include <QMultiMap>
#include <QList>
#include <QString>
#include <QDateTime>

using namespace std;

typedef QMap<QDateTime, QMap<QString, QMap<QString, double>>> NavDataType;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

class rinex
{
public:
    int length;
    string name;
    QStringList ObsType;
    NavDataType dat;
    QDateTime begin, end;
};

#endif // MAINWINDOW_H
