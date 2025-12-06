#include "command.h"


Command::Command(MyStorage *external) : external(external) {
    internal = new MyStorage();
}

Command::~Command(){
    qDebug()<<"desctructor Command";
    while(!internal->isEmpty()){
        internal->exclude_first();
    }
    delete internal;
}

MoveCommand::MoveCommand(QPoint delta, MyStorage *external) : delta(delta), Command(external){
    for(external->first();!external->eol();external->next()){
        Prototype*obj = external->getObject();
        if(obj->isSelect_()){
            internal->add(obj);
        }
    }
}

void MoveCommand::execute() {
    for(internal->first();!internal->eol();internal->next()){
        internal->getObject()->MoveProto(delta);
    }
}

void MoveCommand::unexecute() {
    for(internal->first();!internal->eol();internal->next()){
        internal->getObject()->MoveProto(-delta);
    }
}

DeleteCommand::DeleteCommand(MyStorage *external): Command(external){
}

void DeleteCommand::execute() {
    for(external->first();!external->eol();){
        Prototype*obj = external->getObject();
        if(obj->isSelect_()){
            internal->add(external->exclude(obj));
            obj->hide();
        }
        else external->next();
    }
}

void DeleteCommand::unexecute() {
    internal->first();
    while(!internal->isEmpty()){
        Prototype*obj = internal->exclude_first();
        external->add(obj);
        obj->show();
    }
}


