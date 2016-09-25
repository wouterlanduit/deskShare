#ifndef EVENT_H
#define EVENT_H

#include <QDataStream>
#include <QString>


class Event{        // misschien abstracte klasse van maken
public:
    enum Type {NONE, CHAT, FILE};

protected:
    Type type;
    QString mess;

    virtual QDataStream& doprint(QDataStream& out) const;  // virtual maken : http://stackoverflow.com/questions/11905648/overloading-with-inhertiance-and-polymorphism

    virtual QDataStream& getInput(QDataStream& in);
public:
    Event():type(Event::NONE),mess(""){}

    Event(Type type, QString mess){
        this->type = type;
        this->mess = mess;
    }

    friend QDataStream& operator<<(QDataStream& out, const Event& ev){ return ev.doprint(out);  }
    friend QDataStream& operator>>(QDataStream& in, Event& ev){ return ev.getInput(in); }

    virtual void showDebug();

    QString getMsg(){ return this->getMsg(); }
    void setMsg(QString msg){ this->setMsg(msg); }
};

#endif // EVENT_H

