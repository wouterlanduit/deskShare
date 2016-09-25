#ifndef SOCKETLISTENER_H
#define SOCKETLISTENER_H

#include <QTcpServer>

class Network;

class SocketListener : public QObject{

    Q_OBJECT

protected:
    QTcpServer* tcpServer;
    Network* netwerk;
    QTcpSocket* tcpServerConnection;

public:
    SocketListener(int port, Network* nw);
    ~SocketListener(){
        if(tcpServer) delete tcpServer;
    }

protected slots:
    void acceptConnection();
    virtual void handleRequest();
    virtual void displayRequest();
    void displayError(QAbstractSocket::SocketError socketError);
};

#endif // SOCKETLISTENER_H
