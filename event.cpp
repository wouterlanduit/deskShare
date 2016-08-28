#include "event.h"

Event::Event(Type type, QString mess){
    this->type = type;
    this->mess = mess;
}

QDataStream& operator<<(QDataStream& out, const Event& ev){
    qint32 type = (qint32) ev.type;
    out << type << ev.mess;

    return out;
}

QDataStream& operator>>(QDataStream& in, Event& ev){
    qint32 type;
    QString mess;

    in >> type >> mess;

    ev = Event((Event::Type)type, mess);

    return in;
}

void Event::showDebug(){
    qDebug() << type << mess;
}
