#include"prototype.h"


Prototype::Prototype(QWidget *parent) : QWidget(parent), sizeX(0), sizeY(0) {}

Prototype::Prototype() {
    qDebug()<<"created Proto without parametrs";
}

Prototype::~Prototype() {
    if(edit) delete edit;
}

bool Prototype::isCordBelong(const QPoint &p) {
    return this->geometry().contains(p);
}

int Prototype::getSizeX(){
    return sizeX;
}

int Prototype::getSizeY(){
    return sizeY;
}

void Prototype::updateEditButton() {
    if (isSelect) {
        if (!edit) {
            edit = new QPushButton(this);
            edit->setFixedSize(20, 20);
            edit->show();
            connect(edit, &QPushButton::pressed, this, &Prototype::onEditButtonPressed);
        }
        edit->move(sizeX - 20, sizeY - 20);
        edit->raise();
    } else {
        if (edit) {
            delete edit;
            edit = nullptr;
        }
    }
}

void Prototype::onEditButtonPressed() {
    qDebug() << "Base prototype EditBtn pressed";
    emit editPressed(this);
}
