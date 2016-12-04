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
}

// http://stackoverflow.com/questions/1935021/getting-mousemoveevents-in-qt

void MainWindow::on_startButton_clicked(){  // startknop disabelen
    if(this->mp != NULL && !this->mp->isFinished()){
        qDebug("already running");
        // TODO 2 keer na elkaar op start klikken leidt toch nog tot een crash na het printen van deze boodschap
    }else{
        if(this->mp != NULL){
            delete mp;
        }
        this->mp = new MousePoller(50);
        mp->setLabel(this->ui->coords);
        this->mp->start();

        //nw->hello();
        nw->sendEvent(ChatEvent("HALLO"));
        //nw->sendEvent(Event(Event::NAME, "name"));
    }
}

void MainWindow::on_stopButton_clicked(){
    if(this->mp != NULL)    // deze knop disablen ipv met if te werken
        this->mp->end();
}

void MainWindow::on_actionStart_server_triggered(){
    qDebug("Starting server...");
    nw = new Network(1025);

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
