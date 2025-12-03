#ifndef COMMAND_H
#define COMMAND_H
#include"prototype.h"
#include"group.h"
#include"mystorage.h"
#include<QPoint>

class Command {
public:
    virtual ~Command(){}

    virtual void execute(Prototype*obj) = 0;

    virtual void unexecute() = 0;

};

class MoveCommand : public Command {
    Prototype*_selection;
    QPoint delta;

public:
    MoveCommand(QPoint delta) : delta(delta), _selection(nullptr){
        qDebug()<<"created MoveCommand";
    }

    MoveCommand(QPoint delta, Prototype* obj) : delta(delta), _selection(obj){
        qDebug()<<"created MoveCommand toRemember";
    }

    void execute(Prototype*obj) override {
        _selection = obj;
        _selection->MoveProto(delta);
    }

    void unexecute() override {
        if(_selection)_selection->MoveProto(-delta);
    }

};

class GroupCommand : public Command {
    MyStorage *store;
    Group* group;
public:
    GroupCommand (MyStorage* store) : store(store){
        qDebug()<<"created GroupCommand";
    }

    void execute(Prototype*Pgroup) override {
        group = dynamic_cast<Group*>(Pgroup);
        store->first();
        while(!store->eol()) {
            if(store->getObject()->isSelect_()) {
                group->push(store->exclude(store->getObject()));
                store->first();
            } else {
                store->next();
            }
        }

        if(!group->isEmpty())
            store->add(group);
        else delete group;
    }

    void unexecute() override {
        for(store->first();!store->eol();){
            Prototype*group_maybe = store->getObject();
            if(group_maybe->isSelect_() && dynamic_cast<Group*>(group_maybe)){
                Group*ungroup = dynamic_cast<Group*>(store->exclude(group_maybe));
                while(!ungroup->isEmpty()){
                    store->add(ungroup->exclude_first());
                }
                delete ungroup;
            }

            else store->next();
        }
    }
};




#endif // COMMAND_H
