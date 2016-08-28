#include "followmouse.h"
#include "mouseeventhandler.h"

#include "QMouseEvent"

void FollowMouse::setupWindow(){
    this->setWindowTitle("Follow your mouse");

    coords = new QLabel("no value");

    layout = new QHBoxLayout();
    layout->addStretch();
    layout->addWidget(coords);
    layout->addStretch();

    this->setLayout(layout);


}

void FollowMouse::mouseMoveEvent ( QMouseEvent * event )
{
  //Show x and y coordinate values of mouse cursor here
  this->coords->setText("X:"+QString::number(event->pos().x())+"-- Y:"+QString::number(event->pos().y()));
}

/*bool FollowMouse::eventFilter(QObject *obj, QEvent *event){
    if (event->type() == QEvent::MouseMove)
    {
      QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
      this->coords->setText("X:"+QString::number(mouseEvent->x())+"-- Y:"+QString::number(mouseEvent->y()));
      //ui->listWidget->addItem(QString("Mouse pressed: %1,%2").arg(mouseEvent>pos().x()).arg(mouseEvent->pos().y()));
    }
  return false;
}*/

