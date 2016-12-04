#ifndef IPCONTROL_H
#define IPCONTROL_H

#include "stdint.h"

#include <QFrame>
#include <QLineEdit>
#include <QIntValidator>
#include <QHBoxLayout>
#include <QFont>
#include <QLabel>
#include <QKeyEvent>

#define IP_SIZE 4
#define MAX_DIGITS 3

class IPCtrl : public QFrame{
    Q_OBJECT

public:
    IPCtrl(QWidget *parent = 0);
    ~IPCtrl();

    virtual bool eventFilter( QObject *obj, QEvent *event );

public slots:
    void slotTextChanged( QLineEdit* pEdit );

signals:
    void signalTextChanged( QLineEdit* pEdit );

private:
    QLineEdit *(m_pLineEdit[IP_SIZE]);
    void MoveNextLineEdit (int i);
    void MovePrevLineEdit (int i);
};

#endif // IPCONTROL_H

// http://stackoverflow.com/questions/9306335/an-ip-address-widget-for-qt-similar-to-mfcs-ip-address-control
