#include "fileenvelope.h"
#include "abstractfile.h"
#include "singlefile.h"
#include "folder.h"

QDataStream& FileEnvelope::writeToOut(QDataStream& out) const{
    //dynamic cast -> SINGLEFILE of FOLDER

    qint32 type = (qint32)FileEnvelope::SINGLEFILE;

    out << type << *(this->file);

    return out;
}

QDataStream& FileEnvelope::readFromIn(QDataStream& in){
    qint32 type;

    in >> type;

    switch((FileEnvelope::AbstractFileType)type){
    case FileEnvelope::SINGLEFILE:
        file = new SingleFile();
        break;
    case FileEnvelope::FOLDER:
        file = new Folder();
        break;
    default:
        ;//TODO: foutboodschap
    }

    in >> *(this->file);

    return in;
}
