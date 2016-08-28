#include "mousepoller.h"

#include <QPoint>
#include <QCursor>
#include <QDebug>
#include <QLabel>

MousePoller::MousePoller(int sleepTime){
    this->sleepTime = sleepTime;
    this->label = NULL;
    stop = false;
}

void MousePoller::run(){
    while (!stop){
        QPoint mouseLoc = QCursor::pos();
        int mouseX = mouseLoc.x();
        int mouseY = mouseLoc.y();
        // qDebug() << "Mouse position global: x,y"  << mouseX << mouseY;
        if(label != NULL){
            QString x = QString::number(mouseX);
            QString y = QString::number(mouseY);
            label->setText("X : " + x + "\nY : " + y);  //probleem als degene die labelpointer meegeeft deze plots delete
        }
        QThread::msleep(sleepTime);

        // werken met eventdispatcher???
    }

    return;
}

void MousePoller::setLabel(QLabel* label){
    this->label = label;
}

void MousePoller::end(){
    this->stop = true;
}

