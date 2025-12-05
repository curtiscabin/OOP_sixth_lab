#include "node.h"

Node::Node():next(nullptr),prototype(nullptr){}

Node::~Node(){
    if (prototype) delete prototype;
}
