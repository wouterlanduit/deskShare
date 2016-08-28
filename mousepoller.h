#ifndef MOUSEPOLLER_H
#define MOUSEPOLLER_H

#include <QThread>
#include <Qlabel>

class MousePoller : public QThread{
    Q_OBJECT

public:
    MousePoller(int sleepTime);

    void setLabel(QLabel*);

    void end();

protected:
    void run();
private:
    int sleepTime;
    bool stop;
    QLabel* label;
};

#endif // MOUSEPOLLER_H
