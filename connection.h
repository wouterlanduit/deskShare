#ifndef CONNECTION_H
#define CONNECTION_H

#include "event.h"
#include "transferwindow.h"
#include <QTcpSocket>
#include <QString>
#include <QDialog>
#include <QHostAddress>
#include <QAbstractSocket>


class Network;

// ook nog variabele bijhouden of connectie open is?

class Connection : public QObject{

    Q_OBJECT
    Q_DISABLE_COPY(Connection)

protected:
    QTcpSocket* socket;
    Network* network;
    QString person;     // name of the person you are connected to
    TransferWindow* tfw;


public:
    // constructors en destructor
    Connection(QTcpSocket* socket, Network* network, QString name){
        this->socket = socket;
        this->network = network;
        this->person = name;
    }

    ~Connection(){
        if(tfw) delete tfw;
    }

    static Connection* construct(QTcpSocket* socket, Network* network, QString name){
        Connection* conn = new Connection(socket, network, name);

        QObject::connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
                conn, SLOT(respondSocketState(QAbstractSocket::SocketState)));

        return conn;
    }

    //getters/setters
    QString getPerson(){ return this->person; }


    // print methods
    QString printLocalAddress(){ return this->socket->localAddress().toString() + " : " + QString::number(this->socket->localPort()); }
    QString printPeerAddress(){  return this->socket->peerAddress().toString() + " : " + QString::number(this->socket->peerPort()); }

    QAbstractSocket::SocketState getState(){ return this->socket->state(); }
    QHostAddress getIP(){ return this->socket->localAddress(); }
    quint16 getPort(){ return this->socket->localPort(); }


    void sendHello();
    void send(Event&);
    Event* receive();
    bool isConnected();
    void write(QByteArray& mess);

protected slots:
    void respondSocketState(QAbstractSocket::SocketState state);

};

#endif // CONNECTION_H
