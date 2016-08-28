#ifndef EVENT_H
#define EVENT_H

#include <QDataStream>
#include <QString>


class Event{        // misschien abstracte klasse van maken
public:
    enum Type {NONE, CHAT, FILE};

    Event():type(Event::NONE),mess(""){}

    Event(Type, QString);

    friend QDataStream& operator<<(QDataStream& out, const Event& ev);
    friend QDataStream& operator>>(QDataStream& in, Event& ev);

    void showDebug();

private:
    Type type;
    QString mess;

};

#endif // EVENT_H
