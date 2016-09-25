#ifndef CHATEVENT_H
#define CHATEVENT_H

#include "event.h"


class ChatEvent : public Event{
protected:
    virtual QDataStream& doprint(QDataStream& out) const;
    virtual QDataStream& getInput(QDataStream& in);
public:
    ChatEvent():Event(Event::CHAT, ""){}

    ChatEvent(QString msg):Event(Event::CHAT, msg){}

    virtual void showDebug();

};

#endif // CHATEVENT_H
