#ifndef MOUSEEVENTHANDLER_H
#define MOUSEEVENTHANDLER_H

#include <QObject>
#include <QPoint>
#include <QCursor>
#include <QDebug>
#include <QThread>


class MouseEventHandler : public QObject{
    Q_OBJECT

public:
    //MouseEventHandler();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void pollMouse(int time){
        //Loop forever
        while ( true )
        {
            QPoint mouseLoc = QCursor::pos();
            qDebug() << "Mouse position global: x,y"  << mouseLoc.x() << mouseLoc.y();

            QThread::msleep(time);
        }
    }
};

#endif // MOUSEEVENTHANDLER_H

