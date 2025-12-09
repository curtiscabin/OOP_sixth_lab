#ifndef AFACTORY_H
#define AFACTORY_H
#include"prototype.h"

class afactory
{
public:
    afactory();

    virtual Prototype* createProto(QTextStream&in, QWidget*parent) = 0;
};

#endif // AFACTORY_H
