#ifndef CONNECTION_H
#define CONNECTION_H

#include "event.h"
#include "transferwindow.h"
#include <QTcpSocket>
#include <QString>
#include <QDialog>
#include <QHostAddress>
#include <QAbstractSocket>
#include <QMutex>

class Network;

// ook nog variabele bijhouden of connectie open is?

class Connection : public QObject{

    Q_OBJECT
    Q_DISABLE_COPY(Connection)

private:
    void startTransferWindow(){
        this->tfw = TransferWindow::construct(this);
        this->tfw->show();
    }

protected:
    QTcpSocket* socket;
    Network* network;
    QString person;     // name of the person you are connected to
    TransferWindow* tfw;
    QMutex* mutex;

public:
    // constructors en destructor
    Connection(QTcpSocket* socket, Network* network, QString name){
        this->socket = socket;
        this->network = network;
        this->person = name;
        this->tfw = NULL;
        this->mutex = new QMutex();
    }

    ~Connection(){
        //if(tfw) delete tfw;
    }

    static Connection* construct(QTcpSocket* socket, Network* network, QString name);

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
    void close();

protected slots:
    void respondSocketState(QAbstractSocket::SocketState state);
    void handleRequest();
    void displayError(QAbstractSocket::SocketError socketError);
    void socketDisconnected();

};

#endif // CONNECTION_H
