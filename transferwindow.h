#ifndef TRANSFERWINDOW_H
#define TRANSFERWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QTextEdit>
#include <QLayout>
#include <QLabel>

class Connection;

class TransferWindow : public QDialog{

    Q_OBJECT

private:
    Connection* conn;

    QHBoxLayout* chatBox;
    QTextEdit* chatInput;
    QPushButton* sendButton;

    QLabel* dropBox;
    QVBoxLayout* VLayout;

public:
    //  constructor
    TransferWindow(Connection *conn){
        this->conn = conn;
    }

    ~TransferWindow(){      //TODO: is dit nodig? of verwijderd QDialog al zijn kinderen bij delete
        //delete conn;
        delete chatBox;
        delete chatInput;
        delete sendButton;
        delete dropBox;
        delete VLayout;
    }

    static TransferWindow* construct(Connection *conn);

    void setupChatBox();
    void setupDropBox();
    void putTogether();

    Connection* getConnection(){ return this->conn;}

public slots:
    void sendChat();
};

#endif // TRANSFERWINDOW_H
