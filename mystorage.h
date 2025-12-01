#ifndef MYSTORAGE_H
#define MYSTORAGE_H
#pragma once
#endif // MYSTORAGE_H
#include "Prototype.h"

class Node{

    Node *next;
    Prototype *prototype;

    Node():next(nullptr),prototype(nullptr){}

    ~Node(){
        if (!prototype) delete prototype;
    }

    friend class MyStorage;


};

class MyStorage {
    Node *head;
    Node *tail;
    Node *current;

public:
    MyStorage() : head(nullptr),tail(nullptr),current(nullptr) {}

    void clear(){
        while (head){
            current = head;
            head = current->next;
            delete current;

        }
        current = nullptr;
        tail = nullptr;
    }

    ~MyStorage(){
        this->clear();
    }

    bool isEmpty(){
        return !head;
    }

    void add(Prototype *shap){
        qDebug()<<"enter to add";
        Node* node = new Node;
        node->prototype = shap;
        node->next = head;
        head = node;
        current = node;
        if (!tail) tail = node;

    }

    void first(){
        current = head;
    }

    void next(){
        if (current) current = current->next ;
    }

    bool eol(){
        return current == nullptr;
    }


    Prototype *getObject(){
        return current ? current->prototype : nullptr;
    }

    int get_size(){
        int count =0;
        for(this->first();!this->eol();this->next()) count++;
        return count;
    }

    void clearSelection (){
        qDebug()<<"enter to ClearSelection";
        for(this->first();!this->eol();this->next()){
            qDebug()<<"enter to loop in ClearSelection";
            if(this->getObject()->isSelect_()){
                qDebug()<<"enter to if in ClearSelection";
                this->getObject()->ClearSelect();
                qDebug()<<"over from if in ClearSelection";
            }
            qDebug()<<"over from loop in ClearSelection";
        }
        qDebug()<<"over from ClearSelection";
    }

    void deleteCircles (){
        Node* prev = nullptr;
        Node* node = head;
        Node* toDelete = nullptr;

        while(node){
            if(node->prototype->isSelect_()){
                toDelete = node;
                node = node->next;

                if(prev){
                    prev->next = node;
                }
                else {
                    head = node;
                }

                if(!node){
                    tail = prev;
                }

                delete toDelete;
            }
            else {
                prev = node;
                node = node->next;
            }
        }
    }

    Prototype* exclude(Prototype* obj) {
        Node* prev = nullptr;
        Node* curr = head;
        Prototype* toExclude;

        while (curr) {
            if (curr->prototype == obj) {
                toExclude = curr->prototype;

                if (prev) {
                    prev->next = curr->next;
                } else {
                    head = curr->next;
                }

                if (curr == tail) {
                    tail = prev;
                }
                curr->prototype = nullptr;
                delete curr;

                return toExclude;
            }
            prev = curr;
            curr = curr->next;
        }
    }




};
