#include "mouseeventhandler.h"

#include "QEvent"
#include "QMouseEvent"


bool MouseEventHandler::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseMove) {
        QMouseEvent *mouseEvent = (QMouseEvent *)(event);
        qDebug("x = %d , y = %d", mouseEvent->x(),mouseEvent->y());
        return true;
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}
