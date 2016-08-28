#ifndef FILEEVENT_H
#define FILEEVENT_H

#include "event.h"

#include <QFile>

class FileEvent : public event{
private:
    QFile* file;

public:
    FileEvent(): event(Event::FILE), file(NULL){}

    void setFile(QFile*);
    QFile* getFile();
};

#endif // FILEEVENT_H
