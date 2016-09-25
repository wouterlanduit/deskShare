#ifndef SINGLEFILE_H
#define SINGLEFILE_H

#include "abstractfile.h"

#include <string>
#include <filesystem>
#include <vector>

using namespace std;

class SingleFile : public AbstractFile{
public:
    // constructors
    SingleFile() : AbstractFile(){}
    SingleFile(string n, string p) : AbstractFile(n, p){}

    virtual ~SingleFile(){}

    // getters & setters
    void setName(string n){ this->name = n; }
    string getName(){ return this->name; }
    void setPath(string p){ this->path = p; }
    string getPath(){ return this->path; }

    // methods
    virtual void addFile(AbstractFile&);
    virtual void removeFile(AbstractFile&);
    virtual vector<FILE*> getFiles();

    virtual QDataStream& writeToOut(QDataStream& out) const;
    virtual QDataStream& readFromIn(QDataStream& in);
};

#endif // SINGLEFILE_H
