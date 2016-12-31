#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QPoint>

#include "followmouse.h"
#include "mousepoller.h"
#include "socketlistener.h"
#include "network.h"
#include "event.h"
#include "chatevent.h"
#include "fileevent.h"
#include "transferwindow.h"
#include "constants.h"
#include "addressdialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    //ui->stopButton->setDisabled(true);
    mousePollerMutex = new QMutex();

    this->mp = NULL;
    this->nw = NULL;
}

MainWindow::~MainWindow(){
    delete ui;
    if(mp != NULL){
        mp->end();
        mp->wait(100); // wait untill thread has finished or untill timeout
        delete mp;
    }
    delete mousePollerMutex;
}

// http://stackoverflow.com/questions/1935021/getting-mousemoveevents-in-qt

void MainWindow::on_startButton_clicked(){  // startknop disabelen
    mousePollerMutex->lock();
    //ui->startButton->setDisabled(true);
    if(this->mp != NULL && !this->mp->isFinished()){    // 2 keer snel na elkaar op start klikken leidt tot problemen
        qDebug("already running");
    }else{
        if(this->mp != NULL){
            delete mp;
            mp = NULL;
        }
        this->mp = new MousePoller(50);
        mp->setLabel(this->ui->coords);
        this->mp->start();
    }
    //ui->stopButton->setDisabled(false);
    mousePollerMutex->unlock();
}

void MainWindow::on_stopButton_clicked(){
    mousePollerMutex->lock();
    //ui->stopButton->setDisabled(true);
    if(this->mp != NULL){    // deze knop disablen ipv met if te werken
        this->mp->end();
    }
    //ui->startButton->setDisabled(false);
    mousePollerMutex->unlock();
}

void MainWindow::on_actionStart_server_triggered(){
    if(nw == NULL){
        qDebug("Starting server...");
        nw = new Network(1025);
    }else{
        qDebug("Server already running...");
    }

    SocketListener* sl = nw->getSocketListener();
    sl ? ui->ServerLocation->setText(nw->getSocketListener()->showAddress()) : ui->ServerLocation->setText("");

    // TODO : message if server is up.
}

// check socket state:
    // m_pSocket->state() == QTcpSocket::ConnectedState
    // enum SocketState { UnconnectedState, HostLookupState, ConnectingState, ConnectedState, ..., ListeningState }

void MainWindow::on_actionConnect_triggered(){
    // call dialog window

    // TODO create dialog window

    AddressDialog* dial = AddressDialog::construct();
    if(dial->exec()){
        QHostAddress ip("127.0.0.1");
        nw = new Network();
        nw->connect(ip, 1025);
    }

    // TODO : message if connection is established
    // TODO : create window that allows sending stuff


}
