#ifndef FOLDER_H
#define FOLDER_H

#include "abstractfile.h"
#include <filesystem>
#include <string>
#include <vector>

using namespace std;

class Folder : public AbstractFile
{
protected:
    // vector van abstractfiles
public:
    //constructors
    Folder() : AbstractFile(){}
    Folder(string n, string p) : AbstractFile(n, p){}

    virtual ~Folder(){}

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

#endif // FOLDER_H
