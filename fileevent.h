#ifndef FILEEVENT_H
#define FILEEVENT_H

#include "event.h"

#include <QFile>

class FileEvent : public Event{
protected:
    QFile* file;        // vervangen door eigen klasse File die extends wordt door Folder: in elk een methode getFiles die een array met 1 of meer files returnt

    virtual QDataStream& doprint(QDataStream& out) const;  // virtual maken : http://stackoverflow.com/questions/11905648/overloading-with-inhertiance-and-polymorphism

    virtual QDataStream& getInput(QDataStream& in);

public:
    FileEvent(): Event(Event::FILE, ""), file(NULL){}

    void setFile(QFile*);
    QFile* getFile();

    void showDebug();
};

#endif // FILEEVENT_H
