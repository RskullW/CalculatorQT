#pragma once
#include "QToolButton"

class ButtonQT: public QToolButton {
    Q_OBJECT

public:
    explicit ButtonQT(const QString& text, QWidget *parent = nullptr);
    QSize setSize();

};
