#include "connection.h"
#include "event.h"
#include "chatevent.h"
#include "fileevent.h"
#include "eventenvelope.h"
#include "transferwindow.h"
#include "network.h"
#include <QDataStream>
#include <QString>

Connection* Connection::construct(QTcpSocket* socket, Network* network, QString name){
    Connection* conn = new Connection(socket, network, name);

    QObject::connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            conn, SLOT(respondSocketState(QAbstractSocket::SocketState)));
    QObject::connect(socket, SIGNAL(readyRead()),conn, SLOT(handleRequest()));
    QObject::connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            conn, SLOT(displayError(QAbstractSocket::SocketError)));
    //QObject::connect(socket, &QAbstractSocket::disconnected, socket, &QObject::deleteLater);
    QObject::connect(socket, SIGNAL(disconnected()), conn, SLOT(socketDisconnected()));

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

void Connection::close(){
    //TODO: implement
    // delete tfw
    //delete this->tfw;

    // close TCP socket
    if(this->isConnected()){
        // TODO what if connection is closed here?
        this->socket->disconnectFromHost();     //delete through deleteLater (see construct)
    }

    // delete this object (how?????)
    this->network->disconnect(this);
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

    QDataStream in(&request, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_0);

    // wat als input niet in juiste formaat??
    // als formaat nie juist is, treedt geen error op, hij vult gewoon in zo goed als mogelijk (maar het is wel verkeerd)

    EventEnvelope ee = EventEnvelope();

    in >> ee;

    ee.getEvent()->showDebug();

}

void Connection::displayError(QAbstractSocket::SocketError socketError){
    qDebug("Connection::displayError()");
    switch(socketError)
    {
    case QTcpSocket::RemoteHostClosedError:
        this->tfw->setWindowTitle(this->getPerson() + "(disconnected)");
        break;

    default:
        this->socket->close();
    }
}

void Connection::socketDisconnected(){
    qDebug("Connection::socketDisconnected()");
    QObject::connect(socket, &QAbstractSocket::disconnected, socket, &QObject::deleteLater);
    this->socket = NULL;
}

