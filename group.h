#ifndef GROUP_H
#define GROUP_H

#include"prototype.h"
#include"mystorage.h"

class Group : public Prototype{
public:
    MyStorage* group_store;

    Group(){
        group_store = new MyStorage;
    }

    ~Group(){
        group_store->deleteCircles();
    }


    void push(Prototype* obj){
        group_store->add(obj);
    }

    void SetSelect() override {
        for(group_store->first();!group_store->eol();group_store->next()){
            group_store->getObject()->SetSelect();
        }
    }

    void ClearSelect() override {
        for(group_store->first();!group_store->eol();group_store->next()){
            group_store->getObject()->ClearSelect();
        }
    }

    bool isSelect_() override {
        for(group_store->first();!group_store->eol();group_store->next()){
            if(group_store->getObject()->isSelect_())return true;
        }
        return false;
    }

    void PaintShape() override{
        for(group_store->first();!group_store->eol();group_store->next()){
            group_store->getObject()->PaintShape();
        }
    }

    bool MoveShape(const QPoint&delta) override {
        for(group_store->first();!group_store->eol();group_store->next()){
            if(!group_store->getObject()->MoveShape(delta))return false;
        }
        return true;
    }

    void EditColor(const QString &c) override {
        for(group_store->first();!group_store->eol();group_store->next()){
            group_store->getObject()->EditColor(c);
        }
    }

    void ResizeThat(const QPoint &delta) override {
        for(group_store->first();!group_store->eol();group_store->next()){
            group_store->getObject()->ResizeThat(delta);
        }
    }
};

#endif // GROUP_H
