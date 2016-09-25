#ifndef HTTPSOCKETLISTENER_H
#define HTTPSOCKETLISTENER_H

#include "socketlistener.h"

class Network;

class HttpSocketListener : public SocketListener{

    Q_OBJECT

private:
    void httpResponse();

public:
    HttpSocketListener(Network* nw) : SocketListener(80, nw){}

    virtual void handleRequest();
    virtual void displayRequest();
};

#endif // HTTPSOCKETLISTENER_H
