#ifndef TRANSFERWINDOW_H
#define TRANSFERWINDOW_H

#include <QDialog>

class Connection;

class TransferWindow : public QDialog{

    Q_OBJECT

private:
    Connection* conn;

public:
    //  constructor
    TransferWindow(Connection *conn){
        this->conn = conn;
    }

    static TransferWindow* construct(Connection *conn);
};

#endif // TRANSFERWINDOW_H
