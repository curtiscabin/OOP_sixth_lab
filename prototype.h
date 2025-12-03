#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include<QPoint>
#include<QWidget>
#include<QPainter>
#include<QPushButton>

class Prototype : public QWidget {
    Q_OBJECT
protected:
    int sizeX;
    int sizeY;
    bool isSelect = false;
    QPushButton *edit = nullptr;

public:

    Prototype(QWidget *parent = nullptr) : QWidget(parent), sizeX(0), sizeY(0) {}

    virtual ~Prototype() {
        if(edit) delete edit;
    }

    bool isCordBelong(const QPoint& p) {
        return this->geometry().contains(p);
    }

    virtual void SetSelect() = 0;

    virtual void ClearSelect() = 0;

    virtual bool isSelect_() = 0;

    virtual bool MoveShape(const QPoint&delta) = 0;

    virtual void EditColor(const QString &c) = 0;

    virtual void ResizeThat(const QPoint &delta) = 0;

    int getSizeX(){
        return sizeX;
    }

    int getSizeY(){
        return sizeY;
    }

    void updateEditButton() {
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

signals:
    void editPressed(Prototype *self);

protected slots:
    void onEditButtonPressed() {
        qDebug() << "Base prototype EditBtn pressed";
        emit editPressed(this);
    }

};

#endif // PROTOTYPE_H
