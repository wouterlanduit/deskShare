#include <QTcpSocket>
#include <QDebug>

#include "httpsocketlistener.h"

void HttpSocketListener::handleRequest(){
    displayRequest();

    this->httpResponse();

}

void HttpSocketListener::httpResponse(){
    qDebug("<<<RESPONSE>>>");
    //QByteArray response = QByteArray("HTTP/1.1 404 Not Found/r/n/r/n");
    QByteArray response = QByteArray("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n<!DOCTYPE html>\r\n<html><body>HELLO WORLD</body></html>");
    //QDataStream out(&response, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_4_0);

    //out << "HTTP/1.1 200 OK/r/n/r/n";
    //out << "hello";

    qDebug(response);

    tcpServerConnection->write(response);
    tcpServerConnection->flush();
    tcpServerConnection->disconnectFromHost();      // when this is not here, the browser keeps waiting for more info before it show anything
}

void HttpSocketListener::displayRequest(){
    qDebug("<<<REQUEST>>>");
    QByteArray request = tcpServerConnection->readAll();        // TODO: opzoeken wat readAll precies doet en of er geen beter alternatief is

    qDebug() << request << "/n";
}
