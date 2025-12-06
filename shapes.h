#ifndef SHAPES_H
#define SHAPES_H
#pragma once
#include"prototype.h"

class Shape : public Prototype {
    Q_OBJECT
protected:
    QColor color;

public:
    Shape(const QPoint& b, const QPoint& e, QWidget* parent = nullptr);

    Shape(QWidget* parent = nullptr);

    ~Shape();

    void SetSelect() override;

    void ClearSelect() override;

    bool isSelect_() override;

    void PaintShape();

    bool MoveProto(const QPoint&delta) override;

    void EditColor(const QColor &c) override;

    void CreatSize(const QPoint& b, const QPoint& e);

    void ResizeThat(const QPoint &delta) override;

    void Save(QTextStream& out) override;

    void Load(QTextStream& in) override;

    void hideProto() override;

    void showProto() override;
};



class Circle : public Shape {
public:
    Circle(const QPoint& b, const QPoint& e, QWidget* parent);

    Circle(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent *) override;

    QString getSymbol() override;
};

class Rect : public Shape {
public:
    Rect(const QPoint& b, const QPoint& e, QWidget* parent);

    Rect(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent *) override;

    QString getSymbol() override;
};

class Triangle : public Shape {
public:
    Triangle(const QPoint& b, const QPoint& e, QWidget* parent);

    Triangle(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent *) override;

    QString getSymbol() override;
};

class Section : public Shape {
public:
    Section(const QPoint& b, const QPoint& e, QWidget* parent);

    Section(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent *) override;

    QString getSymbol() override;
};

#endif // SHAPES_H






