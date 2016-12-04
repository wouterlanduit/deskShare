#include "addressdialog.h"

AddressDialog* AddressDialog::construct(){
    AddressDialog* dial = new AddressDialog();


    dial->ipAddress = new QLineEdit();
    dial->ipAddress->setInputMask("000.000.000.000;_");

    dial->buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(dial->buttons, SIGNAL(accepted()), dial, SLOT(accept()));
    connect(dial->buttons, SIGNAL(rejected()), dial, SLOT(reject()));

    //QRegExp rx ( "^(0|[1-9]|[1-9][0-9]|1[0-9][0-9]|2([0-4][0-9]|5[0-5]))$" );
    //QValidator *validator = new QRegExpValidator(rx, pEdit);

    dial->layout = new QVBoxLayout();
    dial->setLayout(dial->layout);
    dial->layout->addWidget(dial->ipAddress);
    dial->layout->addWidget(dial->buttons);

    return dial;
}

QHostAddress AddressDialog::getAddress(){
    return QHostAddress();
}
