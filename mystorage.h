#ifndef MYSTORAGE_H
#define MYSTORAGE_H
#pragma once
#include<QString>
#include "Prototype.h"
#include"node.h"

class MyStorage {
    Node *head;
    Node *tail;
    Node *current;

public:
    MyStorage();

    ~MyStorage();

    void clear();

    bool isEmpty();

    void add(Prototype *shap);

    void first();

    void next();

    bool eol();

    Prototype *getObject();

    int get_size();

    void clearSelection ();

    void deleteCircles ();

    Prototype* exclude(Prototype* obj);

    Prototype* exclude_first();

    Prototype*createProto(QTextStream &in, QWidget* parent = nullptr);

    void SaveSelf(QTextStream &out);

    void LoadFrom(QTextStream &in, QWidget*parent);

};

#endif // MYSTORAGE_H
