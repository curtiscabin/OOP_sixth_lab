#ifndef COMMAND_H
#define COMMAND_H
#include"prototype.h"
#include"group.h"
#include"mystorage.h"
#include<QPoint>

class Command {
protected:
    MyStorage*external;
    MyStorage*internal;
public:
    Command(MyStorage*external);

    ~Command();

    virtual void execute() = 0;

    virtual void unexecute() = 0;

};

class MoveCommand : public Command {
    QPoint delta;
public:
    MoveCommand(QPoint delta, MyStorage* external);

    void execute() override;

    void unexecute() override;

};

class DeleteCommand : public Command {
public:
    DeleteCommand(MyStorage* external);

    void execute() override;

    void unexecute() override;
};

// class GroupCommand : public Command {
//     MyStorage *store;
//     Group* group;
// public:
//     GroupCommand (MyStorage* store);

//     void execute() override;

//     void unexecute() override;
// };




#endif // COMMAND_H
