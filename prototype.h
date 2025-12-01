#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include<QPoint>
#include<QWidget>
#include<QPainter>

class Prototype : public QWidget {
    Q_OBJECT
protected:
    int sizeX;
    int sizeY;
    bool isSelect = false;

public:

    Prototype(QWidget *parent = nullptr) : QWidget(parent), sizeX(0), sizeY(0) {}

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


};

#endif // PROTOTYPE_H
