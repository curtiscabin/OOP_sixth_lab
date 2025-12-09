#include "protofactory.h"

Prototype *ProtoFactory::createProto(QTextStream&in, QWidget *parent, afactory*fact)
{
    QString sym = in.readLine();
    if(sym == "C"){
        qDebug()<<"return Circle";
        return new Circle(parent);
    }
    else if(sym == "R"){
        qDebug()<<"return Circle";
        return new Rect(parent);
    }
    else if(sym == "T"){
        qDebug()<<"return Circle";
        return new Triangle(parent);
    }
    else if(sym == "S"){
        qDebug()<<"return Circle";
        return new Section(parent);
    }
    else if(sym == "G"){
        qDebug()<<"return Group";
        return new Group(parent, fact);
    }
}
