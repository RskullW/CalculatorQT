#pragma once

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include "buttonqt.h"
#include "QKeyEvent"

class Calculator : public QWidget
{
Q_OBJECT

public:
    Calculator();
    ~Calculator();
private:
    ButtonQT* CreateButton(const QString& text, const char* member);

    void AddSpecialSimv();
    void ChangeFont();
    void Abort();

    virtual void keyPressEvent(QKeyEvent *event);

    bool Calc(float operand, const QString& operation);

private:
    float summa_user;
    QString operator_enter_user;
    QString text_user;
    QLabel* sign_user;

    QLineEdit* display_in, *display_out;

    ButtonQT* num_button[10];
    QMap<QString, QString> special_simv;

    QFont font;

private slots:
    void NumberClicked();
    void UnaryOperatorClicked();
    void AdditiveOperatorClicked();
    void EqualClicked();
    void PointClicked();
    void ChangeSignClicked();
    void Clear();
    void ClearAll();
    void BackspaceClicked();
    void NumberKey(const QString& key_user);
    void AdditiveOperatorKey(const QString& key_user);
};

/*
    special_simv["sign"] = QChar(0x000000b1);
    special_simv["plus"] = "+";
    special_simv["minus"] = "-";
    special_simv["squart"] = QChar(0x221A);
    special_simv["deletex"] = "1/x";
    special_simv["division"] = QChar(0x000000F7);
    special_simv["square"] = 'x' + QChar(0x000000b2);
    special_simv["multi"] = QChar(0x000000D7);
    special_simv["equal"] = "=";
 */
