#include "buttonqt.h"

ButtonQT::ButtonQT(const QString &text, QWidget *parent): QToolButton(parent) {
    setText(text);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

QSize ButtonQT::setSize() {
    qDebug("1");

    return QSize(5, 5);
}
