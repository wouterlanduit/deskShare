#include "folder.h"

#include <vector>

using namespace std;

void Folder::addFile(AbstractFile&){


}


void Folder::removeFile(AbstractFile&){


}


vector<FILE*> Folder::getFiles(){
    vector<FILE*> v;

    //TODO: implement
    // FILE* f = new FILE();
    // v.push_back(f);

    return v;
}


QDataStream& Folder::writeToOut(QDataStream& out) const{
    //TODO:implementation
    return out;
}

QDataStream& Folder::readFromIn(QDataStream& in){
    //TODO:implementation
    return in;
}
