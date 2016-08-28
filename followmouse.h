#ifndef FOLLOWMOUSE_H
#define FOLLOWMOUSE_H

#include "QDialog"
#include "QLabel"
#include "QHBoxLayout"

#include "mouseeventhandler.h"


class FollowMouse : public QDialog{
    Q_OBJECT

private:
    QLabel* coords;
    QHBoxLayout* layout;
    MouseEventHandler* mouseEventHandler;

public:
    FollowMouse(){
        coords = NULL;
        layout = NULL;
        this->setupWindow();
        this->setMouseTracking(true);
        mouseEventHandler = new MouseEventHandler();
        this->installEventFilter(mouseEventHandler);
    }

    ~FollowMouse(){
        if(coords != NULL){
            delete coords;
        }
        if(layout != NULL){
            delete layout;
        }
    }

    void mouseMoveEvent ( QMouseEvent * event );
    //bool eventFilter(QObject *obj, QEvent *event);

    void setupWindow();
};

#endif // FOLLOWMOUSE_H


