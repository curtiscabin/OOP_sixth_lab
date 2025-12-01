#ifndef SHAPES_H
#define SHAPES_H

#pragma once

#include<QDebug>
#include<QString>
#include<QPainter>
#include<math.h>
#include<QPushButton>
#include"prototype.h"




class Shape : public Prototype {
    Q_OBJECT
protected:
    int sizeX;
    int sizeY;
    bool isSelect = false;
    QString color = "white";
    QPushButton *edit = nullptr;

signals:
    void editPressed(Shape *self);


public:
    Shape(const QPoint& b, const QPoint& e, QWidget* parent = nullptr) : Prototype(parent) {
        sizeX = abs(e.x() - b.x());
        sizeY = abs(e.y()- b.y());
    }

    ~Shape(){
        update();
    }

    bool isCordBelong(const QPoint& p) override {
        return this->geometry().contains(p);
    }

    void SetSelect() override {
        isSelect = true;
        if(!edit)
        {
            edit = new QPushButton(this);
            edit->setFixedSize(20,20);
            edit->move(sizeX - 20, sizeY - 20);
            edit->show();
        }

        if (edit && this) {
            connect(edit, &QPushButton::pressed, this, &Shape::onEditButtonPressed);
        }
        update();
    }

    void ClearSelect() override {
        isSelect = false;
        delete edit;
        edit = nullptr;
        update();
    }

    bool isSelect_() override {
        return isSelect;
    }

    void PaintShape() override {
        show();
    }

    bool MoveShape(const QPoint&delta) override {
        int nx = x() + delta.x();
        int ny = y() + delta.y();

        QRect rectMove(nx,ny, sizeX,sizeY);
        if(!parentWidget()->rect().contains(rectMove))return false;

        move(nx,ny);
        return true;
    }

    void EditColor(const QString &c) override {
        color = c;
        update();
    }

    void CreatSize(const QPoint& b, const QPoint& e) {
        QRect parentRect = this->parentWidget()->rect();

        int ex = e.x();
        int ey = e.y();

        if (ex < parentRect.left()) ex = parentRect.left();
        else if (ex > parentRect.right()) ex = parentRect.right();

        if (ey < parentRect.top()) ey = parentRect.top();
        else if (ey > parentRect.bottom()) ey = parentRect.bottom();

        sizeX = abs(ex - b.x());
        sizeY = abs(ey - b.y());

        setFixedSize(sizeX, sizeY);

        if (b.x() < ex && b.y() > ey){
            move(b.x(), ey);
        }
        else if (b.x() > ex && b.y() < ey){
            move(ex, b.y());
        }
        else if (b.x() > ex && b.y() > ey){
            move(ex, ey);
        }
        else move(b.x(), b.y());

        if(edit){
            edit->move(sizeX - 20, sizeY - 20);
        }

        update();
    }

    void ResizeThat(const QPoint &delta) override {
        int nw = sizeX + delta.x();
        int nh = sizeY + delta.y();

        if (nw < 10) nw = 10;
        if (nh < 10) nh = 10;

        QRect parentRect = parentWidget()->rect();
        QRect newRect(x(), y(), nw, nh);
        if (!parentRect.contains(newRect))
            return;

        sizeX = nw;
        sizeY = nh;
        setFixedSize(sizeX, sizeY);

        if (edit) {
            edit->move(sizeX - 20, sizeY - 20);
        }

        update();
    }

protected slots:
    void onEditButtonPressed() {
        qDebug()<<"Button is pressed";
        emit editPressed(this);
    }
};



class Circle : public Shape {
public:
    Circle(const QPoint& b, const QPoint& e, QWidget* parent) : Shape(b, e, parent){
        qDebug()<<"Created Circle";
    }

    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        QPen CirclePen;
        painter.setRenderHint(QPainter::Antialiasing);

        if (isSelect_()){
            QPen SelectPen;
            SelectPen.setDashPattern({4,4});
            SelectPen.setColor("cyan");
            SelectPen.setWidth(3);
            painter.setPen(SelectPen);
            painter.drawRect(0,0,sizeX,sizeY);
        }
        CirclePen.setColor(color);
        painter.setBrush(color);

        painter.setPen(CirclePen);
        painter.drawEllipse(0,0,sizeX,sizeY);
    }

};

class Rect : public Shape {
public:
    Rect(const QPoint& b, const QPoint& e, QWidget* parent)
        : Shape(b, e, parent)
    {
        qDebug() << "Created Square";
    }

    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QPen rectPen(color);
        painter.setPen(rectPen);
        painter.setBrush(color);
        painter.drawRect(0, 0, sizeX, sizeY);

        if (isSelect_()) {
            QPen selectPen(Qt::cyan);
            selectPen.setDashPattern({4, 4});
            selectPen.setWidth(3);
            painter.setPen(selectPen);
            painter.setBrush(Qt::NoBrush);
            painter.drawRect(0, 0, sizeX, sizeY);
        }
    }
};

class Triangle : public Shape {
public:
    Triangle(const QPoint& b, const QPoint& e, QWidget* parent)
        : Shape(b, e, parent)
    {
        qDebug() << "Created Triangle";
    }

    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QPen trianglePen(color);
        painter.setPen(trianglePen);
        painter.setBrush(color);

        QPolygonF poly;
        poly << QPointF(sizeX / 2.0, 0)
             << QPointF(sizeX,       sizeY)
             << QPointF(0,           sizeY);
        painter.drawPolygon(poly);

        if (isSelect_()) {
            QPen selectPen(Qt::cyan);
            selectPen.setDashPattern({4, 4});
            selectPen.setWidth(3);
            painter.setPen(selectPen);
            painter.setBrush(Qt::NoBrush);
            painter.drawRect(0, 0, sizeX, sizeY);
        }
    }
};

class Section : public Shape {
public:
    Section(const QPoint& b, const QPoint& e, QWidget* parent) : Shape(b, e, parent){
        qDebug()<<"Created Circle";
    }

    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        QPen SectionPen;
        painter.setRenderHint(QPainter::Antialiasing);

        if (isSelect_()){
            QPen SelectPen;
            SelectPen.setDashPattern({4,4});
            SelectPen.setColor("cyan");
            SelectPen.setWidth(3);
            painter.setPen(SelectPen);
            painter.drawRect(0,0,sizeX,sizeY);
        }
        SectionPen.setColor(color);
        painter.setPen(SectionPen);
        painter.drawLine(0,0,sizeX,sizeY);
    }

};

#endif // SHAPES_H






