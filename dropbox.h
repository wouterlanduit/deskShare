#ifndef DROPBOX_H
#define DROPBOX_H

#include <QLabel>
#include <QDragEnterEvent>
#include <QDropEvent>

class DropBox : public QLabel{
public:
    DropBox(){
        setText("Drop content here.");
        setAlignment(Qt::AlignCenter);
        setStyleSheet("border: 2px dashed black; background: grey");
        setAcceptDrops(true);
    }

    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);
};

#endif // DROPBOX_H
