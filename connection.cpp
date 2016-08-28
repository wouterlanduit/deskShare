#include "connection.h"
#include "event.h"
#include <QDataStream>
#include <QString>

Connection::Connection(QTcpSocket *socket, Network *network, QString name){
    this->socket = socket;
    this->network = network;
    this->person = name;
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

    out << e;
    this->write(mess);

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
