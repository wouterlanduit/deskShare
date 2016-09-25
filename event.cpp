#include "event.h"
#include <iostream>
#include <string.h>

#include <QDebug>

using namespace std;

QDataStream& Event::doprint(QDataStream& out) const{
    qint32 type = (qint32) this->type;
    out << type << this->mess;

    return out;
}

QDataStream& Event::getInput(QDataStream& in){
    qint32 type;
    QString mess;

    in >> type >> mess;

    this->type = (Event::Type)type;
    this->mess = mess;

    return in;
}

void Event::showDebug(){
    qDebug() << "type " << this->type << ": " << this->mess << "(event)";
}
