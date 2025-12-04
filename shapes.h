#ifndef SHAPES_H
#define SHAPES_H

#pragma once

#include<QDebug>
#include<QString>
#include<math.h>
#include<QPushButton>
#include"prototype.h"




class Shape : public Prototype {
    Q_OBJECT
protected:
    QString color = "white";


public:
    Shape(const QPoint& b, const QPoint& e, QWidget* parent = nullptr) : Prototype(parent) {
        qDebug()<<"created Shape with parametrs";
        sizeX = abs(e.x() - b.x());
        sizeY = abs(e.y()- b.y());
        SetSelect();
    }


    Shape(QWidget* parent = nullptr) : Prototype(parent){
    }

    ~Shape(){
        update();
    }



    void SetSelect() override {
        isSelect = true;
        updateEditButton();
        update();
    }

    void ClearSelect() override {
        isSelect = false;
        updateEditButton();
        update();
    }

    bool isSelect_() override {
        return isSelect;
    }

    void PaintShape(){
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
        updateEditButton();
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
        if(isSelect)updateEditButton();
        update();
    }

    void Save(QTextStream& out) override {
        out<<getSymbol()<<'\n';
        out<<x()<<'\n';
        out<<y()<<'\n';
        out<<sizeX<<'\n';
        out<<sizeY<<'\n';
        out<<color<<'\n';
    }

    void Load(QTextStream& in) override {
        int x,y;
        QString line;
        line = in.readLine();
        x = line.toInt();
        line = in.readLine();
        y = line.toInt();
        line = in.readLine();
        sizeX = line.toInt();
        line = in.readLine();
        sizeY = line.toInt();
        color = in.readLine();
        move(x,y);
        setFixedSize(sizeX,sizeY);
        EditColor(color);
    }
};



class Circle : public Shape {
public:
    Circle(const QPoint& b, const QPoint& e, QWidget* parent) : Shape(b, e, parent){
        qDebug()<<"Created Circle";
    }

    Circle(QWidget* parent = nullptr) : Shape(parent){}

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

    QString getSymbol() override{
        return "C";
    }
};

class Rect : public Shape {
public:
    Rect(const QPoint& b, const QPoint& e, QWidget* parent)
        : Shape(b, e, parent)
    {
        qDebug() << "Created Square";
    }

    Rect(QWidget* parent = nullptr) : Shape(parent){}

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

    QString getSymbol() override{
        return "R";
    }
};

class Triangle : public Shape {
public:
    Triangle(const QPoint& b, const QPoint& e, QWidget* parent)
        : Shape(b, e, parent)
    {
        qDebug() << "Created Triangle";
    }

    Triangle(QWidget* parent = nullptr) : Shape(parent){}

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

    QString getSymbol() override{
        return "T";
    }
};

class Section : public Shape {
public:
    Section(const QPoint& b, const QPoint& e, QWidget* parent) : Shape(b, e, parent){
        qDebug()<<"Created Circle";
    }

    Section(QWidget* parent = nullptr) : Shape(parent){}

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

    QString getSymbol() override{
        return "S";
    }
};

#endif // SHAPES_H






