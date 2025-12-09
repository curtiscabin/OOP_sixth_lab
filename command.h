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
    Command();

    Command(MyStorage*external);

    ~Command();

    virtual void execute();

    virtual void unexecute();

    virtual void doit(Prototype*obj) = 0;

    virtual void undoit(Prototype*obj) = 0;

};

class MoveCommand : public Command {
    QPoint delta;
public:
    MoveCommand(QPoint delta, MyStorage* external);

    void doit(Prototype*obj) override;

    void undoit(Prototype*obj) override;

};

class DeleteCommand : public Command {
public:
    DeleteCommand(MyStorage* external);

    void doit(Prototype*obj) override;

    void undoit(Prototype*obj) override;
};

class GroupCommand : public Command {
    Group*ingroup;
    QWidget*parent;
public:
    GroupCommand(MyStorage* external, QWidget*parent);

    void doit(Prototype *obj) override;

    void undoit(Prototype *obj) override;

    void execute() override;

    void unexecute() override;
};

class UnGroupCommand : public Command {
    Group*inUngroup;
    QWidget*parent;
    QList<MyStorage*>kids;
public:
    UnGroupCommand(MyStorage* external, QWidget*parent);

    void doit(Prototype *obj) override;

    void undoit(Prototype *obj) override;

    void execute() override;

    void unexecute() override;
};

class EditColorCommand : public Command {
    QColor color;
    QList<QColor>colors;
public:
    EditColorCommand(MyStorage* external, const QColor& color);

    void doit(Prototype*obj) override;

    void undoit(Prototype*obj) override;
};

#endif // COMMAND_H
