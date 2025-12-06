#include "command.h"


Command::Command(MyStorage *external) : external(external) {
    internal = new MyStorage();
    for(external->first();!external->eol();external->next()){
        Prototype*obj = external->getObject();
        if(obj->isSelect_()){
            internal->add(obj);
        }
    }
}

Command::~Command(){
    qDebug()<<"desctructor Command";
    while(!internal->isEmpty()){
        internal->exclude_first();
    }
    delete internal;
}

MoveCommand::MoveCommand(QPoint delta, MyStorage *external) : delta(delta), Command(external){

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
    for(internal->first();!internal->eol();internal->next()){
        Prototype*obj = internal->getObject();
        external->exclude(obj);
        obj->hideProto();
    }
}

void DeleteCommand::unexecute() {
    for(internal->first();!internal->eol();internal->next()){
        Prototype*obj = internal->getObject();
        external->add(obj);
        obj->showProto();
    }
}


