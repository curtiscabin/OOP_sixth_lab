#ifndef PROTOFACTORY_H
#define PROTOFACTORY_H

#include "afactory.h"
#include"shapes.h"
#include"group.h"

class ProtoFactory : public afactory
{
public:
    ProtoFactory() {}

    Prototype* createProto(QTextStream&in, QWidget*parent) override;
};

#endif // PROTOFACTORY_H
