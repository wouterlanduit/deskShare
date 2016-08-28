#ifndef SOCKETLISTENER_H
#define SOCKETLISTENER_H

#include <QTcpServer>

class Network;

class SocketListener:public QObject{

    Q_OBJECT

private:
    QTcpServer* tcpServer;
    Network* netwerk;
    QTcpSocket* tcpServerConnection;

    void httpResponse();

public:
    SocketListener(Network* nw);
    SocketListener(int port, Network* nw);

private slots:
    void displayRequest();
    void httpRequest();
    void acceptConnection();
    void displayError(QAbstractSocket::SocketError socketError);
};

#endif // SOCKETLISTENER_H
