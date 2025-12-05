#ifndef NODE_H
#define NODE_H
#include"prototype.h"

class Node{

    Node *next;
    Prototype *prototype;

    Node();

    ~Node();

    friend class MyStorage;


};

#endif // NODE_H
