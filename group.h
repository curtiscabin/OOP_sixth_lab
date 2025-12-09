#ifndef GROUP_H
#define GROUP_H
#pragma once
#include"prototype.h"
#include"mystorage.h"

class MyStorage;

class Group : public Prototype{
Q_OBJECT
    MyStorage* group_store = nullptr;
    afactory* fact = nullptr;

public:
    Group(QWidget* parent = nullptr);

    Group(QWidget* parent, afactory*fact);

    ~Group();

    void updateSize();

    void push(Prototype* obj);

    Prototype *exclude_first();

    bool isEmpty();

    void SetSelect() override;

    void ClearSelect() override;

    bool isSelect_() override;

    bool MoveProto(const QPoint&delta) override;

    void EditColor(const QColor &c) override;

    void ResizeThat(const QPoint &delta) override;

    void paintEvent(QPaintEvent *) override;

    QString getSymbol() override;

    void Save(QTextStream& out) override;

    void Load(QTextStream& in) override;

    void hideProto() override;

    void showProto() override;

    QColor getColor() override;

};

#endif // GROUP_H
