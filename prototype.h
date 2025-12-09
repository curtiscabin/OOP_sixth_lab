#ifndef PROTOTYPE_H
#define PROTOTYPE_H
#pragma once
#include<QPoint>
#include<QWidget>
#include<QPainter>
#include<QPushButton>
#include<QFile>

class Prototype : public QWidget {
    Q_OBJECT
protected:
    int sizeX;
    int sizeY;
    bool isSelect = false;
    QPushButton *edit = nullptr;

public:

    Prototype(QWidget *parent = nullptr);

    Prototype();

    virtual ~Prototype();

    bool isCordBelong(const QPoint& p);

    virtual void SetSelect() = 0;

    virtual void ClearSelect() = 0;

    virtual bool isSelect_() = 0;

    virtual bool MoveProto(const QPoint&delta) = 0;

    virtual void EditColor(const QColor &c) = 0;

    virtual void ResizeThat(const QPoint &delta) = 0;

    int getSizeX();

    int getSizeY();

    void updateEditButton();

    virtual void Save(QTextStream& out) = 0;

    virtual void Load(QTextStream& out) = 0;

    virtual QString getSymbol() = 0;

    virtual void hideProto() = 0;

    virtual void showProto() = 0;

    virtual QColor getColor() = 0;

    void EditRaise(){
        edit->raise();
    }

signals:
    void editPressed(Prototype *self);

protected slots:
    void onEditButtonPressed();

};

#endif // PROTOTYPE_H
