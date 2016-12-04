#ifndef SOCKETLISTENER_H
#define SOCKETLISTENER_H

#include <QTcpServer>
#include <QString>

class Network;

class SocketListener : public QObject{

    Q_OBJECT

protected:
    QTcpServer* tcpServer;
    Network* netwerk;
    QTcpSocket* tcpServerConnection;    //TODO: wegdoen

public:
    SocketListener(Network* nw);
    SocketListener(int port, Network* nw);
    ~SocketListener(){
        if(tcpServer) delete tcpServer;
    }

    //methods
    QString showAddress(){ return tcpServer ? tcpServer->serverAddress().toString() + ":" + QString::number(tcpServer->serverPort()) : ""; }

protected slots:
    void acceptConnection();
    virtual void handleRequest();
    virtual void displayRequest();
    void displayError(QAbstractSocket::SocketError socketError);
};

#endif // SOCKETLISTENER_H
