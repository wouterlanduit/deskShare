#include "eventenvelope.h"
#include "event.h"
#include "chatevent.h"
#include "fileevent.h"

QDataStream& EventEnvelope::writeToOut(QDataStream& out) const{
    //dynamic cast -> SINGLEFILE of FOLDER

    qint32 type = (qint32)Event::CHAT;

    out << type << *(this->event);

    return out;
}

QDataStream& EventEnvelope::readFromIn(QDataStream& in){
    qint32 type;

    in >> type;     // werkt dit? of is in volledig leeg??

    switch((Event::Type)type){
    case Event::CHAT:
        event = new ChatEvent();
        break;
    case Event::FILE:
        event = new FileEvent();
        break;
    default:
        ;//TODO: foutboodschap
    }

    in >> *(this->event);

    return in;
}
