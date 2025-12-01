#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include<QPoint>
#include<QWidget>

class Prototype : public QWidget {
    Q_OBJECT

public:
    Prototype(QWidget *parent = nullptr) : QWidget(parent) {}

    virtual bool isCordBelong(const QPoint& p) = 0;

    virtual void SetSelect() = 0;

    virtual void ClearSelect() = 0;

    virtual bool isSelect_() = 0;

    virtual void PaintShape() = 0;

    virtual bool MoveShape(const QPoint&delta) = 0;

    virtual void EditColor(const QString &c) = 0;

    virtual void ResizeThat(const QPoint &delta) = 0;


};

#endif // PROTOTYPE_H
