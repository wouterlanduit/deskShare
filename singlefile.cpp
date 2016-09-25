#include "singlefile.h"
#include <vector>
#include <filesystem>

using namespace std;

void SingleFile::addFile(AbstractFile& file){
    //TODO : errormsg
}

void SingleFile::removeFile(AbstractFile& file){
    //TODO : errormsg
}

vector<FILE*> SingleFile::getFiles(){
    vector<FILE*> v;
    //FILE* f = new FILE();
    //v.push_back(f);

    return v;    //TODO
}

QDataStream& SingleFile::writeToOut(QDataStream& out) const{
    //TODO:implementation
    return out;
}

QDataStream& SingleFile::readFromIn(QDataStream& in){
    //TODO:implementation
    return in;
}
