#include"group.h"

Group::Group(QWidget *parent) : Prototype(parent) {
    group_store = new MyStorage;
    SetSelect();
}

Group::~Group() {
    delete group_store;
}

void Group::updateSize() {

    int minX = 100000, minY = 100000;
    int maxX = -100000, maxY = -100000;

    for (group_store->first(); !group_store->eol(); group_store->next()) {
        QRect r = group_store->getObject()->geometry();

        if (r.left() < minX) minX = r.left();
        if (r.top() < minY) minY = r.top();
        if (r.right() > maxX) maxX = r.right();
        if (r.bottom() > maxY) maxY = r.bottom();

        sizeX = maxX - minX;
        sizeY = maxY - minY;
    }

    setGeometry(minX, minY, sizeX, sizeY);

    if(isSelect)updateEditButton();
}

void Group::push(Prototype *obj){
    group_store->add(obj);
    obj->ClearSelect();
    updateSize();
    show();
}

Prototype *Group::exclude_first(){
    return group_store->exclude_first();
}

bool Group::isEmpty(){
    return group_store->isEmpty();
}

void Group::SetSelect() {
    isSelect = true;
    updateEditButton();
    update();
}

void Group::ClearSelect() {
    for(group_store->first();!group_store->eol();group_store->next()){
        group_store->getObject()->ClearSelect();
    }
    isSelect = false;
    updateEditButton();
    update();
}

bool Group::MoveShape(const QPoint &delta) {
    int nx = x() + delta.x();
    int ny = y() + delta.y();

    QRect rectMove(nx,ny, sizeX,sizeY);
    if(!parentWidget()->rect().contains(rectMove))return false;

    move(nx,ny);

    for(group_store->first();!group_store->eol();group_store->next()){
        group_store->getObject()->MoveShape(delta);
    }
    return true;
}

void Group::EditColor(const QColor &c) {
    for(group_store->first();!group_store->eol();group_store->next()){
        group_store->getObject()->EditColor(c);
    }
}

void Group::ResizeThat(const QPoint &delta) {
    for(group_store->first();!group_store->eol();group_store->next()){
        group_store->getObject()->ResizeThat(delta);
    }
    updateSize();
}

void Group::paintEvent(QPaintEvent *) {
    if (isSelect_()) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QPen SelectPen;
        SelectPen.setDashPattern({4, 4});
        SelectPen.setColor("cyan");
        SelectPen.setWidth(3);

        painter.setPen(SelectPen);
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(0, 0, width(), height());
    }
}

QString Group::getSymbol(){
    return "G";
}

void Group::Save(QTextStream &out) {
    // for(group_store->first();!group_store->eol();group_store->next()){
    //     group_store->getObject()->Save(out);
    // }
}

void Group::Load(QTextStream &in) {
    // for(group_store->first();!group_store->eol();group_store->next()){
    //     group_store->getObject()->Load(in);
    // }
}
