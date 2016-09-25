#include "transferwindow.h"
#include "connection.h"
#include <iostream>
#include <QHostAddress>
#include <QAbstractSocket>

TransferWindow *TransferWindow::construct(Connection *conn){
    TransferWindow* wind = new TransferWindow(conn);

    std::cout << "Local\t->\t" << conn->printLocalAddress().toStdString() << std::endl;
    std::cout << "Peer\t->\t" << conn->printPeerAddress().toStdString() << std::endl;

    wind->setWindowTitle(conn->getPerson());
    wind->setMinimumSize(QSize(200, 100));

    return wind;
}
