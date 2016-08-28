#include "fileevent.h"
#include "event.h"

QFile* FileEvent::getFile(){
    return this->file;
}

void FileEvent::setFile(QFile* f){
    this->file = f;
}

QDataStream& operator<<(QDataStream& out, const Event& ev){
    qint32 type = (qint32) ev.type;

    // TODO : file

    out << type << ev.mess;

    return out;
}

QDataStream& operator>>(QDataStream& in, Event& ev){
    qint32 type;
    QString mess;

    //TODO : file

    in >> type >> mess;

    ev = Event((Event::Type)type, mess);

    return in;
}

void FileEvent::showDebug(){
    qDebug() << this->type << this->mess;
}
