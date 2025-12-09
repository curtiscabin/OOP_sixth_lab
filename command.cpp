#include "command.h"

Command::Command() {

}

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
    obj->EditRaise();
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
}

UnGroupCommand::UnGroupCommand(MyStorage *external, QWidget *parent) : parent(parent), Command()
{
    this->external = external;
    internal = new MyStorage();
    for (external->first();!external->eol();external->next()){
        Group*group_maybe = dynamic_cast<Group*>(external->getObject());
        if(group_maybe && group_maybe->isSelect_()){
            internal->add(group_maybe);
        }
    }
}

void UnGroupCommand::doit(Prototype *obj)
{
    Group* gr = dynamic_cast<Group*>(obj);
    if (kids.isEmpty()) {
        kids.push_back(new MyStorage);
        while(!gr->isEmpty()){
            Prototype* proto = gr->exclude_first();
            external->add(proto);
            kids.last()->add(proto);
            proto->SetSelect();
            proto->EditRaise();
        }
    } else {
        MyStorage* store = kids.first();
        for(store->first(); !store->eol(); store->next()){
            Prototype* proto = gr->exclude_first();
            if (proto) {
                external->add(proto);
                proto->SetSelect();
                proto->EditRaise();
            }
        }
        kids.append(kids.takeFirst());
    }

}

void UnGroupCommand::undoit(Prototype *obj)
{
    Group* gr = dynamic_cast<Group*>(obj);
    if (!kids.isEmpty()) {
        MyStorage* store = kids.first();
        for(store->first(); !store->eol(); store->next()){
            Prototype* p = store->getObject();
            external->exclude(p);
            p->ClearSelect();
            gr->push(p);
        }
        kids.append(kids.takeFirst());
    }
}

void UnGroupCommand::execute()
{
    for(internal->first();!internal->eol();internal->next()){
        Prototype*group = internal->getObject();
        group->ClearSelect();
        external->exclude(group);
        doit(group);
    }
}

void UnGroupCommand::unexecute()
{
    for(internal->first();!internal->eol();internal->next()){
        Prototype*group = internal->getObject();
        external->add(group);
        undoit(group);
        group->SetSelect();
    }
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
