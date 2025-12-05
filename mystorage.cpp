#include"mystorage.h"
#include"shapes.h"

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

Prototype *MyStorage::createProto(QTextStream &in, QWidget *parent){
    QString sym = in.readLine();
    if(sym == "C"){
        qDebug()<<"return Circle";
        return new Circle(parent);
    }
    else if(sym == "R"){
        qDebug()<<"return Circle";
        return new Rect(parent);
    }
    else if(sym == "T"){
        qDebug()<<"return Circle";
        return new Triangle(parent);
    }
    else if(sym == "S"){
        qDebug()<<"return Circle";
        return new Section(parent);
    }
}

void MyStorage::SaveSelf(QString filename){
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream out(&file);
        out << get_size()<<'\n';
        for(first();!eol();next()){
            getObject()->Save(out);
        }
        file.close();
    }
}

void MyStorage::LoadFrom(QString filename, QWidget *parent){
    Prototype*obj;
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString line = in.readLine();
        int size = line.toInt();
        for(int i = 0 ; i<size; i++){
            obj = createProto(in, parent);
            obj->Load(in);
            obj->show();
            add(obj);
        }
        file.close();
    }
}
