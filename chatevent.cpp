#include "chatevent.h"
#include "event.h"

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

void FileEvent::showDebug(){
    qDebug() << this->type << this->mess;
}
