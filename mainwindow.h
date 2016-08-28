#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mousepoller.h"
#include "network.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_startButton_clicked();
    void on_stopButton_clicked();

    void on_actionStart_server_triggered();

    void on_actionConnect_triggered();

private:
    Ui::MainWindow *ui;
    MousePoller* mp;
    Network* nw;
};

#endif // MAINWINDOW_H
