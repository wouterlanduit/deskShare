#ifndef CONNECTION_H
#define CONNECTION_H

#include "event.h"
#include <QTcpSocket>
#include <QString>

class Network;

// ook nog variabele bijhouden of connectie open is?

class Connection{
private:
    QTcpSocket* socket;
    Network* network;
    QString person;     // name of the person you are connected to


public:
    Connection(QTcpSocket* socket, Network* network, QString name);
    void sendHello();
    void send(Event&);
    bool isConnected();
    void write(QByteArray& mess);


};

#endif // CONNECTION_H
