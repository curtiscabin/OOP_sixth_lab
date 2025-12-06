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

void Command::execute(){
    for(internal->first();!internal->eol();internal->next()){
        doit(internal->getObject());
    }
}

void Command::unexecute(){
    for(internal->first();!internal->eol();internal->next()){
        undoit(internal->getObject());
    }
}

MoveCommand::MoveCommand(QPoint delta, MyStorage *external) : delta(delta), Command(external){
}

void MoveCommand::doit(Prototype*obj) {
    obj->MoveProto(delta);
}

void MoveCommand::undoit(Prototype*obj) {
    obj->MoveProto(-delta);
}

DeleteCommand::DeleteCommand(MyStorage *external): Command(external){
}

void DeleteCommand::doit(Prototype*obj) {
    external->exclude(obj);
    obj->hideProto();
}

void DeleteCommand::undoit(Prototype*obj) {
    external->add(obj);
    obj->showProto();
}

GroupCommand::GroupCommand(MyStorage *external) : Command(external)
{
    ingroup = new Group;
}

void GroupCommand::doit(Prototype *obj)
{

}

void GroupCommand::undoit(Prototype *obj)
{

}

EditColorCommand::EditColorCommand(MyStorage *external, const QColor &color) : Command(external), color(color)
{
}

void EditColorCommand::doit(Prototype *obj)
{
    colors.push_back(obj->getColor());
    obj->EditColor(color);
}

void EditColorCommand::undoit(Prototype *obj)
{

    obj->EditColor(colors.takeFirst());
}
