#ifndef FILEENVELOPE_H
#define FILEENVELOPE_H

#include "abstractfile.h"

#include <QDataStream>


class FileEnvelope
{
protected:
    AbstractFile* file;

public:
    enum AbstractFileType{SINGLEFILE, FOLDER};

    FileEnvelope(AbstractFile* f):file(f){}
    ~FileEnvelope(){
        if(file){
           delete file;
        }
    }

    AbstractFile* getFile(){ return file; }

    //methods
    QDataStream& writeToOut(QDataStream& out) const;    //bij schrijven eerst aantal files en dan streammethodes van SingleFile of Folder gebruiken
    QDataStream& readFromIn(QDataStream& in);

    friend QDataStream& operator<<(QDataStream& out, const FileEnvelope& env){ return env.writeToOut(out);  }
    friend QDataStream& operator>>(QDataStream& in, FileEnvelope& env){ return env.readFromIn(in); }
};

#endif // FILEENVELOPE_H
