#include "chatevent.h"
#include "event.h"

#include <QDebug>

QDataStream& ChatEvent::doprint(QDataStream& out) const{
    qint32 type = (qint32) this->type;
    out << type << this->mess;

    qDebug("LOG:\tdoPrint() (ChatEvent)");

    return out;
}

QDataStream& ChatEvent::getInput(QDataStream& in){
    /*qint32 type;
    QString mess;

    in >> type >> mess;

    this->type = (Event::Type)type;
    this->mess = mess;*/

    in >> (this->mess);

    return in;
}

void ChatEvent::showDebug(){
    qDebug() << "type " << this->type << ": " << this->mess << "(chatevent)";
}
