#include "network.h"
#include "socketlistener.h"
#include "connection.h"

Network::Network(int port){
    sl = new SocketListener(port, this);
    cn = NULL;
}

Connection Network::connect(QHostAddress ip, int port){
    QTcpSocket* socket = new QTcpSocket();
    socket->connectToHost(ip, port);        // what to do if no connection can be made? ; does this need to be on a seperate thread?
    return connect(socket);
}

Connection Network::connect(QTcpSocket* socket){
    this->cn = new Connection(socket, this, "EMPTY");

    return *cn;
}

void Network::disconnect(){
    // TODO: verder over nadenken
    delete cn;
}

void Network::hello(){
    if(cn != NULL){
        this->cn->sendHello();
    }else{
        qDebug() << "Connection not yet established.";
    }

}

void Network::sendEvent(Event& ev){
    if(cn != NULL){
        this->cn->send(ev);
    }else{
        qDebug() << "Connection not yet established.";
    }
}
