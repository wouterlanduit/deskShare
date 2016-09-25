#ifndef NETWORK_H
#define NETWORK_H

#include <QHostAddress>

#include "socketlistener.h"
#include "httpsocketlistener.h"
#include "connection.h"

class Network{
private:
    SocketListener* sl;
    Connection* cn;

public:
    // constructors
    Network(){
        sl = NULL;
        cn = NULL;
    }

    Network(int port){
        switch(port){
        case 80:
            sl = new HttpSocketListener(this);
            break;
        default:
            sl = new SocketListener(port, this);
        }

        cn = NULL;
    }

    // methods
    void connect(QHostAddress ip,int port);
    void connect(QTcpSocket*);

    void disconnect();

    void hello();
    void sendEvent(Event& ev);
};

#endif // NETWORK_H
