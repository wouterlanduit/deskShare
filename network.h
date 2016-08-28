#ifndef NETWORK_H
#define NETWORK_H

#include <QHostAddress>

#include "socketlistener.h"
#include "connection.h"

class Network{
private:
    SocketListener* sl;
    Connection* cn;

public:
    Network(int port);

    Connection connect(QHostAddress ip,int port);
    Connection connect(QTcpSocket*);

    void disconnect();

    void hello();
    void sendEvent(Event& ev);
};

#endif // NETWORK_H
