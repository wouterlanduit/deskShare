#include "fileevent.h"
#include "event.h"

#include <iostream>
#include <fstream>

#include <QDebug>

QFile* FileEvent::getFile(){
    return this->file;
}

void FileEvent::setFile(QFile* f){
    this->file = f;
}

QDataStream& FileEvent::doprint(QDataStream& out) const{
    qint32 type = (qint32) this->type;

    // TODO : file

    // copy a file      // http://stackoverflow.com/questions/10195343/copy-a-file-in-a-sane-safe-and-efficient-way
    // std::ifstream  src("from.ogv", std::ios::binary);
    // std::ofstream  dst("to.ogv",   std::ios::binary);
    // dst << src.rdbuf();

    out << type << this->mess;

    return out;
}

QDataStream& FileEvent::getInput(QDataStream& in){
    qint32 type;
    QString mess;

    //TODO : file

    in >> type >> mess;

    this->type = (Event::Type)type;
    this->mess = mess;

    return in;
}


void FileEvent::showDebug(){
    qDebug() << "type " << this->type << ": " << this->mess << "(fileevent)";
}
