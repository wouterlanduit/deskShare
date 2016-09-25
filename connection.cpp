#include "connection.h"
#include "event.h"
#include "transferwindow.h"
#include <QDataStream>
#include <QString>

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
        this->tfw = TransferWindow::construct(this);                    // via factory method: this as argument is unsafe?
        this->tfw->exec();
        break;
    }
}
