#include "calculator.h"

#include "cmath"
#include "QGridLayout"
#include "QToolButton"
#include "QDebug"

Calculator::Calculator() {
// BASE SETTINGS
    setWindowTitle("Calculator");
    AddSpecialSimv();
// CREATE FIELDS
    display_in = new QLineEdit;
    display_out = new QLineEdit;
    sign_user = new QLabel;

    QGridLayout* mainLayout = new QGridLayout;
// CHANGE FONTS
    ChangeFont();
// CREATE BUTTONS
    for (short i = 0; i < 10; ++i) {
        num_button[i] = CreateButton(QString::number(i), SLOT(NumberClicked()));
    }

    ButtonQT* point_button = CreateButton(".", SLOT(PointClicked()));
    ButtonQT* sign_button = CreateButton(special_simv["sign"], SLOT(ChangeSignClicked()));

    ButtonQT* minus_button = CreateButton(special_simv["minus"], SLOT(AdditiveOperatorClicked()));
    ButtonQT* plus_button = CreateButton(special_simv["plus"], SLOT(AdditiveOperatorClicked()));
    ButtonQT* multi_button = CreateButton(special_simv["multi"], SLOT(AdditiveOperatorClicked()));
    ButtonQT* division_button = CreateButton(special_simv["division"], SLOT(AdditiveOperatorClicked()));

    ButtonQT* square_button = CreateButton(special_simv["square"], SLOT(UnaryOperatorClicked()));
    ButtonQT* squart_button = CreateButton(special_simv["squart"], SLOT(UnaryOperatorClicked()));
    ButtonQT* deletex_button = CreateButton(special_simv["deletex"], SLOT(UnaryOperatorClicked()));

    ButtonQT* equal_button = CreateButton(special_simv["equal"], SLOT(EqualClicked()));

    ButtonQT* backspace_button = CreateButton("BACKSPACE", SLOT(BackspaceClicked()));
    ButtonQT* clear_button = CreateButton("CLEAR", SLOT(Clear()));
    ButtonQT* clear_all_button = CreateButton("CLEAR ALL", SLOT(ClearAll()));


// CHANGE FIELD DISPLAY
    display_in->setReadOnly(true);
    display_out->setReadOnly(true);

    display_in->setAlignment(Qt::AlignRight);
    display_out->setAlignment(Qt::AlignRight);
    sign_user->setAlignment(Qt::AlignRight);

    display_in->setMaxLength(16);
    display_out->setMaxLength(16);

    display_out->setText("0");
// ADD ALL WIDGETS

    mainLayout->addWidget(display_in, 0, 0, 1, 6);
    mainLayout->addWidget(sign_user, 1, 5, 1, 1 );
    mainLayout->addWidget(display_out, 2, 0, 1, 6);

    mainLayout->addWidget(backspace_button, 3, 0, 1, 2);
    mainLayout->addWidget(clear_button, 3, 2, 1, 2);
    mainLayout->addWidget(clear_all_button, 3, 4, 1, 2);

    mainLayout->addWidget(division_button, 4, 4);
    mainLayout->addWidget(multi_button, 5, 4);
    mainLayout->addWidget(minus_button, 6, 4);
    mainLayout->addWidget(plus_button, 7, 4);

    mainLayout->addWidget(square_button, 4, 5);
    mainLayout->addWidget(squart_button, 5, 5);
    mainLayout->addWidget(deletex_button, 6, 5);
    mainLayout->addWidget(equal_button, 7, 5);

    for (int i = 1; i < 10; ++i) {
        int row = ((9-i)/3) + 4, column = ((i-1)%3) + 1;

        mainLayout->addWidget(num_button[i], row, column);
    }

    mainLayout->addWidget(num_button[0], 7, 1);
    mainLayout->addWidget(point_button, 7, 2);
    mainLayout->addWidget(sign_button, 7, 3);

// PRINT FIELDS
    setLayout(mainLayout);

}

Calculator::~Calculator() {
    delete display_in;
    delete display_out;
    delete sign_user;
}

void Calculator::AddSpecialSimv() {
    special_simv["sign"] = QChar(0x000000b1);
    special_simv["plus"] = "+";
    special_simv["minus"] = "-";
    special_simv["squart"] = QChar(0x221A);
    special_simv["deletex"] = "1/x";
    special_simv["division"] = QChar(0x000000F7);
    special_simv["square"] = 'x' + QChar(0x000000b2);
    special_simv["multi"] = QChar(0x000000D7);
    special_simv["equal"] = "=";

}

void Calculator::ChangeFont() {
    font = display_in->font();
    font.setPointSize(font.pointSize()+8);
    display_in->setFont(font);
    display_out->setFont(font);
    sign_user->setFont(font);
}

void Calculator::NumberClicked() {
    ButtonQT* btn = (ButtonQT*)sender();

    short num = btn->text().toInt();

    if (display_out->text()=="0") {
        display_out->clear();
        display_in->clear();
    }

    display_out->setText(display_out->text()+QString::number(num));
}
void Calculator::UnaryOperatorClicked(){
    ButtonQT* btn = (ButtonQT*) sender();

    QString oper = btn->text();

    float operand = display_out->text().toFloat();
    float result = 0.0f;

    if (oper == special_simv["squart"]) {
        if (operand < 0.0f) {
            Abort();
            return;
        }

        result = std::sqrt(operand);
    }

    else if (oper == special_simv["square"]) {
        result = std::pow(operand, 2);
    }

    else if (oper == special_simv["deletex"]) {
        if (operand == 0.0f) {
            Abort();
            return;
        }

        result = 1.0f / operand;
    }

    display_out->setText(QString::number(result));
}
void Calculator::AdditiveOperatorClicked() {
    ButtonQT *btn = (ButtonQT *) sender();
    QString operation = btn->text();

    float operand = display_out->text().toFloat();

    if (display_out->text() == "0") {
        return;
    }

    sign_user->setText(operation);

    if (display_out->text() == "") {
        return;
    }

    display_out->clear();

    if (!operator_enter_user.isEmpty()) {
        if (!Calc(operand, operator_enter_user) ) {
            Abort();
            return;
        }
        operator_enter_user.clear();
    }

    else {
        display_in->setText(QString::number(operand));
    }

    operator_enter_user = operation;
}
void Calculator::EqualClicked(){

    if (display_in->text() == "" || display_in->text() == " ") {
        return;
    }

    float operand = display_out->text().toFloat();

    if (!operator_enter_user.isEmpty()) {
        if (!Calc(operand, operator_enter_user) ) {
            Abort();
            return;
        }
        operator_enter_user.clear();
    }

    display_out->setText(display_in->text());
    display_in->clear();
    sign_user->clear();



}
void Calculator::PointClicked(){
    if (!display_out->text().contains('.')) {
        display_out->setText(display_out->text() + '.');
    }
}
void Calculator::ChangeSignClicked(){
    QString txt = display_out->text();
    float num = txt.toFloat();

    if (num>0.0) {
        txt.prepend("-");
    }

    else if (num < 0.0) {
        txt.remove(0,1);
    }

    display_out->setText(txt);
}

void Calculator::Clear(){
    display_out->setText("0");
}

void Calculator::ClearAll(){
    display_in->setText("");
    display_out->setText("0");
    operator_enter_user.clear();
}

void Calculator::BackspaceClicked() {
    QString text = display_out->text();

    text.chop(1);

    if (text.isEmpty()) {
        text = "0";
    }

    display_out->setText(text);
}

void Calculator::Abort() {
    display_in->setText("*#&");
    display_out->setText("*#&");
}

bool Calculator::Calc(float operand, const QString &operation) {
    float temp = display_in->text().toFloat();

    if (operation == special_simv["plus"]) {
        temp+=operand;
    }

    else if (operation == special_simv["minus"]) {
        temp-=operand;
    }

    else if (operation == special_simv["multi"] || operation == "*") {
        temp*=operand;
    }

    else if (operation == special_simv["division"] || operation == "/") {
        if (operand == 0.0f) {
            return false;
        }

        temp/=operand;
    }

    display_in->setText(QString::number(temp));

    return true;
}

void Calculator::keyPressEvent(QKeyEvent *event) {
    int key_user = event->key();

    if (key_user >= Qt::Key_0 && key_user <= Qt::Key_9) {
        NumberKey(QString(QChar(key_user)));
    }

    else if (key_user == Qt::Key_Plus || key_user == Qt::Key_Minus || key_user == Qt::Key_Asterisk || key_user == Qt::Key_Slash) {
        AdditiveOperatorKey(QString(QChar(key_user)));
    }

    else if (key_user == Qt::Key_Delete || key_user == Qt::Key_Backspace) {
        BackspaceClicked();
    }

    else if (key_user == Qt::Key_Equal || key_user == Qt::Key_Return) {
        EqualClicked();
    }
    // key_user == 46, 46 - number key point
    else if (key_user == Qt::Key_Comma || key_user == 46) {
        PointClicked();
    }
    // key_user == 94, 94 - square number
   else if (key_user == 94) {
        display_out->setText(QString::number(std::pow(display_out->text().toFloat(), 2)));
   }

   else if (key_user == Qt::Key_Delete) {
       ClearAll();
   }

    //qDebug() << key_user << QString(QChar(key_user));
}

void Calculator::NumberKey(const QString& key_user) {

    short num = key_user.toShort();

    if (display_out->text()=="0") {
        display_out->clear();
        display_in->clear();
    }

    display_out->setText(display_out->text()+QString::number(num));
}

void Calculator::AdditiveOperatorKey(const QString &key_user) {
    QString operation = key_user;

    float operand = display_out->text().toFloat();

    if (display_out->text() == "0") {
        return;
    }

    sign_user->setText(operation);

    if (display_out->text() == "") {
        return;
    }

    display_out->clear();

    if (!operator_enter_user.isEmpty()) {
        if (!Calc(operand, operator_enter_user) ) {
            Abort();
            return;
        }
        operator_enter_user.clear();
    }

    else {
        display_in->setText(QString::number(operand));
    }

    operator_enter_user = operation;
}

ButtonQT* Calculator::CreateButton(const QString &text, const char *member) {
    ButtonQT* btn = new ButtonQT(text);
    connect(btn, SIGNAL(clicked()), this, member);

    return btn;
}
