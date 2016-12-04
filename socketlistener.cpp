#include "socketlistener.h"
#include "event.h"
#include "chatevent.h"
#include "eventenvelope.h"
#include "constants.h"
#include "network.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>

// de tcp socket hier linken met het netwerk object
SocketListener::SocketListener(Network *nw){
    this->tcpServer = new QTcpServer();
    this->netwerk = nw;
    if(!this->tcpServer->listen(QHostAddress::LocalHost)){
        //QMessageBox::critical(this, tr("Opening socket"), tr("Unable to start server: %1.").arg(tcpServer->errorString()));
        qDebug("unable to start server");
        //close();
        return;
    }

    qDebug() << "Server started\tPORT : " << this->tcpServer->serverPort();

    QObject::connect(tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}

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
    QTcpSocket *socket = tcpServer->nextPendingConnection();

    this->netwerk->connect(socket);

    //TODO: socket als connection toevoegen aan network
    //QObject::connect(tcpServerConnection, SIGNAL(readyRead()),this, SLOT(handleRequest()));

    QObject::connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
    // zodat socket wordt gedelete als connectie gesloten wordt
    // TODO : ook uit network verwijderen
    /*QObject::connect(tcpServerConnection, &QAbstractSocket::disconnected,
            tcpServerConnection, &QObject::deleteLater);*/

//    tcpServer.close();
}
// http://doc.qt.io/qt-5/qtnetwork-loopback-dialog-cpp.html


void SocketListener::handleRequest(){   //in displayRequest steken
    displayRequest();

    QByteArray request = tcpServerConnection->readAll();        // TODO: opzoeken wat readAll precies doet en of er geen beter alternatief is

    QDataStream inType(&request, QIODevice::ReadOnly);
    inType.setVersion(QDataStream::Qt_4_0);
    QDataStream inAll(&request, QIODevice::ReadOnly);
    inAll.setVersion(QDataStream::Qt_4_0);

    // wat als input niet in juiste formaat??
    // als formaat nie juist is, treedt geen error op, hij vult gewoon in zo goed als mogelijk (maar het is wel verkeerd)

    //TODO: vervangen door event enveloppe

    /*qint32 type;

    inType >> type;

    Event* event;

    switch((Event::Type)type){
    case Event::CHAT:
        event = new ChatEvent();
        break;
    case Event::FILE:

        break;
    default:
        event = new Event();
    }

    inAll >> *event;

    //in >> ev;

    event->showDebug();*/

    EventEnvelope ee = EventEnvelope();

    inAll >> ee;

    ee.getEvent()->showDebug();

    qDebug(request);
}

void SocketListener::displayRequest(){
    qDebug("<<<REQUEST>>>");
}

void SocketListener::displayError(QAbstractSocket::SocketError socketError){
    if (socketError == QTcpSocket::RemoteHostClosedError)
        return;

    qDebug("displayError()");

    tcpServer->close();
}
// http://doc.qt.io/qt-5/qtnetwork-loopback-dialog-cpp.html


