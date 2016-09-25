#ifndef ABSTRACTFILE_H
#define ABSTRACTFILE_H

#include <string>
#include <filesystem>
#include <vector>

#include <QDataStream>

using namespace std;

class AbstractFile{
    protected:
        string name;
        string path;

    public:
        //constructors & destructor
        AbstractFile() : name(""), path(""){}
        AbstractFile(string name, string path) : name(name), path(path){}

        virtual ~AbstractFile(){}

        // getters & setters
        void setName(string n){ this->name = n; }
        string getName(){ return this->name; }
        void setPath(string p){ this->path = p; }
        string getPath(){ return this->path; }

        // methods
        virtual void addFile(AbstractFile&) = 0;
        virtual void removeFile(AbstractFile&) = 0;
        virtual vector<FILE*> getFiles() = 0;

        virtual QDataStream& writeToOut(QDataStream& out) const = 0;
        virtual QDataStream& readFromIn(QDataStream& in) = 0;

        friend QDataStream& operator<<(QDataStream& out, const AbstractFile& af){ return af.writeToOut(out);  }
        friend QDataStream& operator>>(QDataStream& in, AbstractFile& af){ return af.readFromIn(in); }
};

#endif // ABSTRACTFILE_H
