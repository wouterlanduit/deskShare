#ifndef CHATEVENT_H
#define CHATEVENT_H

#include "event.h"


class ChatEvent : public event{
public:
    ChatEvent():Event(Event::CHAT, ""){}

    ChatEvent(QString msg):Event(Event::CHAT, msg){}

    QString getMsg(){ return this->msg; }
    void setMsg(QString msg){ this->msg = msg; }

};

#endif // CHATEVENT_H
