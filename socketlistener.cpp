#include "socketlistener.h"
#include "event.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>

// de tcp socket hier linken met het netwerk object

SocketListener::SocketListener(int port, Network *nw){
    this->tcpServer = new QTcpServer();
    this->netwerk = nw;
    if(!this->tcpServer->listen(QHostAddress::LocalHost, port)){
        //QMessageBox::critical(this, tr("Opening socket"), tr("Unable to start server: %1.").arg(tcpServer->errorString()));
        qDebug("unable to start server");
        //close();
        return;
    }
    qDebug() << "Server started\tPORT : " << this->tcpServer->serverPort();

    QObject::connect(tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}
// http://doc.qt.io/qt-5/qtnetwork-fortuneserver-example.html


void SocketListener::acceptConnection(){
    tcpServerConnection = tcpServer->nextPendingConnection();

    //TODO: socket als connection toevoegen aan network

    switch(tcpServer->serverPort()){
    case 80:
        QObject::connect(tcpServerConnection, SIGNAL(readyRead()),this, SLOT(httpRequest()));
        break;
    default:
        QObject::connect(tcpServerConnection, SIGNAL(readyRead()),this, SLOT(displayRequest()));
    }

    QObject::connect(tcpServerConnection, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
    // zodat socket wordt gedelete als connectie gesloten wordt
    // TODO : ook uit network verwijderen
    QObject::connect(tcpServerConnection, &QAbstractSocket::disconnected,
            tcpServerConnection, &QObject::deleteLater);

//    tcpServer.close();
}
// http://doc.qt.io/qt-5/qtnetwork-loopback-dialog-cpp.html

void SocketListener::httpRequest(){
    displayRequest();

    this->httpResponse();

}

void SocketListener::httpResponse(){
    qDebug("<<<RESPONSE>>>");
    //QByteArray response = QByteArray("HTTP/1.1 404 Not Found/r/n/r/n");
    QByteArray response = QByteArray("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n<!DOCTYPE html>\r\n<html><body>HELLO WORLD</body></html>");
    //QDataStream out(&response, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_4_0);

    //out << "HTTP/1.1 200 OK/r/n/r/n";
    //out << "hello";

    qDebug(response);

    tcpServerConnection->write(response);
    tcpServerConnection->flush();
    tcpServerConnection->disconnectFromHost();      // when this is not here, the browser keeps waiting for more info before it show anything
}

void SocketListener::displayRequest(){
    qDebug("<<<REQUEST>>>");
    QByteArray request = tcpServerConnection->readAll();

    // qint32 type;
    // QString mess;
    Event ev;

    QDataStream in(&request, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_0);

    // wat als input niet in juiste formaat??
    // als formaat nie juist is, treedt geen error op, hij vult gewoon in zo goed als mogelijk (maar het is wel verkeerd)

    in >> ev;

    qDebug(request);

}

void SocketListener::displayError(QAbstractSocket::SocketError socketError){
    if (socketError == QTcpSocket::RemoteHostClosedError)
        return;

    qDebug("displayError()");

    tcpServer->close();
}
// http://doc.qt.io/qt-5/qtnetwork-loopback-dialog-cpp.html


