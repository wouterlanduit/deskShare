#ifndef EVENTENVELOPE_H
#define EVENTENVELOPE_H

#include "event.h"

#include <QDataStream>

class EventEnvelope
{
protected:
    Event* event;

    //methods
    QDataStream& writeToOut(QDataStream& out) const;
    QDataStream& readFromIn(QDataStream& in);

public:
    //enum EventType{SINGLEFILE, FOLDER};

    EventEnvelope(){}
    EventEnvelope(Event* e):event(e){}
    ~EventEnvelope(){
        if(event){
           delete event;
        }
    }

    Event* getEvent(){ return event; }

    friend QDataStream& operator<<(QDataStream& out, const EventEnvelope& env){ return env.writeToOut(out);  }
    friend QDataStream& operator>>(QDataStream& in, EventEnvelope& env){ return env.readFromIn(in); }
};

#endif // EVENTENVELOPE_H
