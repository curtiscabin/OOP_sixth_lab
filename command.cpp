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

GroupCommand::GroupCommand(MyStorage *external, QWidget*parent) : Command(external), parent(parent)
{
    ingroup = new Group(parent);
}

void GroupCommand::doit(Prototype *obj)
{
    ingroup->push(external->exclude(obj));
    obj->ClearSelect();
}

void GroupCommand::undoit(Prototype *obj)
{
    external->add(ingroup->exclude_first());
    obj->SetSelect();
}

void GroupCommand::execute()
{

    ingroup->SetSelect();
    external->add(ingroup);
    for(internal->first();!internal->eol();internal->next()){
        doit(internal->getObject());
    }
}

void GroupCommand::unexecute()
{
    ingroup->ClearSelect();
    external->exclude(ingroup);
    for(internal->first();!internal->eol();internal->next()){
        undoit(internal->getObject());
    }
    // delete ingroup;
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
