#include "connection.h"
#include "event.h"
#include "chatevent.h"
#include "fileevent.h"
#include "eventenvelope.h"
#include "transferwindow.h"
#include <QDataStream>
#include <QString>

Connection* Connection::construct(QTcpSocket* socket, Network* network, QString name){
    Connection* conn = new Connection(socket, network, name);

    QObject::connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            conn, SLOT(respondSocketState(QAbstractSocket::SocketState)));
    QObject::connect(socket, SIGNAL(readyRead()),conn, SLOT(handleRequest()));
    QObject::connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            conn, SLOT(displayError(QAbstractSocket::SocketError)));
    QObject::connect(socket, &QAbstractSocket::disconnected, socket, &QObject::deleteLater);

    conn->mutex->lock();
    if(conn->isConnected() && conn->tfw == NULL){
        conn->startTransferWindow();
    }
    conn->mutex->unlock();

    return conn;
}

void Connection::sendHello(){
    if(this->isConnected()){
        this->socket->write("HELLO WORLD");
        this->socket->flush();    //sluit de connectie ofzo??
    }else{
        qDebug() << "Connection not yet established.";
    }

}

void Connection::send(Event& e){
    QByteArray mess;
    QDataStream out(&mess, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    //out << EventEnvelope(&e);
    out << e;
    this->write(mess);
}

Event* Connection::receive(){
    //TODO implement en vanuit network oproepen
    return NULL;
}

void Connection::write(QByteArray& mess){
    if(this->isConnected()){
        this->socket->write(mess);
        //this->socket->flush();
        //this->socket->disconnectFromHost();
    }else{
        qDebug() << "Connection not yet established.";
    }
}

bool Connection::isConnected(){
    return this->socket != NULL && this->socket->state() == QTcpSocket::ConnectedState;
}

void Connection::respondSocketState(QAbstractSocket::SocketState state){
    switch(state){
    case QAbstractSocket::ConnectedState:
        this->mutex->lock();
        if(this->tfw == NULL){
            this->startTransferWindow();
        }
        this->mutex->unlock();
        break;
    }
}

void Connection::handleRequest(){
    QByteArray request = socket->readAll();        // TODO: opzoeken wat readAll precies doet en of er geen beter alternatief is

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

    event->showDebug();

    qDebug(request);*/

    EventEnvelope ee = EventEnvelope();

    inAll >> ee;

    ee.getEvent()->showDebug();

}

void Connection::displayError(QAbstractSocket::SocketError socketError){
    if (socketError == QTcpSocket::RemoteHostClosedError)
        return;

    qDebug("displayError()");

    this->socket->close();
}

