#include "transferwindow.h"
#include "connection.h"
#include "chatevent.h"
#include <iostream>
#include <QHostAddress>
#include <QAbstractSocket>
#include <QTextEdit>
#include <QLayout>
#include <QLabel>
#include <QPushButton>

TransferWindow* TransferWindow::construct(Connection *conn){
    TransferWindow* wind = new TransferWindow(conn);

    std::cout << "Local\t->\t" << conn->printLocalAddress().toStdString() << std::endl;
    std::cout << "Peer\t->\t" << conn->printPeerAddress().toStdString() << std::endl;

    wind->setWindowTitle(conn->getPerson());
    wind->setMinimumSize(QSize(200, 100));

    wind->setupChatBox();

    wind->setupDropBox();

    wind->putTogether();

    return wind;
}

void TransferWindow::setupChatBox(){
    // TODO: make height adjustable
    this->chatBox = new QHBoxLayout();
    this->chatInput = new QTextEdit();
    this->chatInput->setMaximumHeight(60);
    this->sendButton = new QPushButton("SEND");
    this->sendButton->setMaximumHeight(60);
    QObject::connect(sendButton, SIGNAL(clicked(bool)), this, SLOT(sendChat()));
    this->chatBox->addWidget(chatInput);
    this->chatBox->addWidget(sendButton);
}

void TransferWindow::setupDropBox(){
    this->dropBox = new QLabel();
    this->dropBox->setText("Drop content here.");
    this->dropBox->setGeometry(QRect(0, 0, this->width(), this->height()-60));
    this->dropBox->setAlignment(Qt::AlignCenter);
    this->dropBox->setStyleSheet("border: 2px dashed black; background: grey");
    //TODO zoeken om kleiner te maken
}

void TransferWindow::putTogether(){
    this->VLayout = new QVBoxLayout();
    this->VLayout->addWidget(dropBox);
    this->VLayout->addLayout(chatBox);

    this->setLayout(VLayout);
}

void TransferWindow::sendChat(){
    QString chatMsg = chatInput->toPlainText();
    this->getConnection()->send(ChatEvent(chatMsg));
    chatInput->clear();
}
