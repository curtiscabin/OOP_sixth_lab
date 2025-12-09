#include"mystorage.h"
#include"shapes.h"
#include"group.h"

MyStorage::MyStorage() : head(nullptr),tail(nullptr),current(nullptr) {}

MyStorage::~MyStorage(){
    this->clear();
}

void MyStorage::clear(){
    while (head){
        current = head;
        head = current->next;
        delete current;

    }
    current = nullptr;
    tail = nullptr;
}

bool MyStorage::isEmpty(){
    return !head;
}

void MyStorage::add(Prototype *shap){
    qDebug()<<"enter to add";
    Node* node = new Node;
    node->prototype = shap;
    node->next = head;
    head = node;
    current = node;
    if (!tail) tail = node;

}

void MyStorage::first(){
    current = head;
}

void MyStorage::next(){
    if (current) current = current->next ;
}

bool MyStorage::eol(){
    return current == nullptr;
}

Prototype *MyStorage::getObject(){
    return current ? current->prototype : nullptr;
}

int MyStorage::get_size(){
    int count =0;
    for(this->first();!this->eol();this->next()) count++;
    return count;
}

void MyStorage::clearSelection(){
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

void MyStorage::deleteCircles(){
    Prototype* obj;
    for(first();!eol();){
        obj = getObject();
        if(obj->isSelect_())
            {
            next();
            delete exclude(obj);
        }
        else next();
    }
}

Prototype *MyStorage::exclude(Prototype *obj) {
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

            if (current == curr) {
                current = curr->next;
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
    return nullptr;
}

Prototype *MyStorage::exclude_first(){
    return exclude(head->prototype);
}

void MyStorage::SaveSelf(QTextStream &out){
    out<<get_size()<<"\n";
    for(first();!eol();next()){
        getObject()->Save(out);
    }
}

void MyStorage::LoadFrom(QTextStream &in, QWidget *parent, afactory* fact){
    Prototype*obj;
    QString line = in.readLine();
    int size = line.toInt();
    for(int i = 0 ; i<size; i++){
        obj = fact->createProto(in, parent, fact);
        obj->Load(in);
        add(obj);
    }

}

void MyStorage::SaveOpen(const QString &filename)
{
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream out(&file);
        SaveSelf(out);
        file.close();
    }
}

void MyStorage::LoadOpen(const QString &filename, QWidget *parent, afactory* fact)
{
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        LoadFrom(in, parent, fact);
        file.close();
    }
}
