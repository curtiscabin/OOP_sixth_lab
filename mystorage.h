#ifndef MYSTORAGE_H
#define MYSTORAGE_H
#pragma once
#include<QString>
#include "Prototype.h"
#include"node.h"
#include"protofactory.h"

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

    void SaveSelf(QTextStream &out);

    void LoadFrom(QTextStream &in, QWidget*parent, afactory* fact);

    void SaveOpen(const QString &filename);

    void LoadOpen(const QString &filename, QWidget*parent, afactory* fact);

};

#endif // MYSTORAGE_H
