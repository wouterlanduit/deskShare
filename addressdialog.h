#ifndef ADDRESSDIALOG_H
#define ADDRESSDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLayout>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QHostAddress>

class AddressDialog : public QDialog
{

    Q_OBJECT

private:
    QLineEdit *ipAddress;
    QDialogButtonBox* buttons;
    QVBoxLayout *layout;

public:
    //  constructor
    AddressDialog(){

    }

    ~AddressDialog(){
        if(ipAddress)
            delete ipAddress;
        if(buttons)
            delete buttons;
        if(layout)
            delete layout;
    }

    static AddressDialog* construct();

    QHostAddress getAddress();
};

#endif // ADDRESSDIALOG_H
