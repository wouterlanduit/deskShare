#include "network.h"
#include "httpsocketlistener.h"
#include "connection.h"
#include "constants.h"

void Network::connect(QHostAddress ip, int port){
    QTcpSocket* socket = new QTcpSocket();
    socket->connectToHost(ip, port);        // what to do if no connection can be made? ; does this need to be on a seperate thread?
    connect(socket);
}

void Network::connect(QTcpSocket* socket){
    this->cn = Connection::construct(socket, this, "EMPTY");
}

void Network::disconnect(Connection *conn){
    // TODO: verder over nadenken
    delete conn;
}

void Network::hello(){
    if(cn != NULL){
        this->cn->sendHello();
    }else{
        qDebug() << ERR_NO_CONNECTION;
    }
}

void Network::sendEvent(Event& ev){
    if(cn != NULL){
        this->cn->send(ev);
    }else{
        qDebug() << ERR_NO_CONNECTION;
    }
}
