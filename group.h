#ifndef GROUP_H
#define GROUP_H

#include"prototype.h"
#include"mystorage.h"

class Group : public Prototype{
Q_OBJECT
    MyStorage* group_store = nullptr;

public:
    Group(QWidget* parent = nullptr) : Prototype(parent) {
        group_store = new MyStorage;
        SetSelect();
    }

    ~Group() {
        delete group_store;
    }

    void updateSize() {

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
    }


    void push(Prototype* obj){
        group_store->add(obj);
        obj->ClearSelect();
        updateSize();
        show();
    }

    bool isEmpty(){
        return group_store->isEmpty();
    }

    void SetSelect(){
        isSelect = true;
        update();
    }

    void ClearSelect() override {
        for(group_store->first();!group_store->eol();group_store->next()){
            group_store->getObject()->ClearSelect();
        }
        isSelect = false;
        update();
    }

    bool isSelect_() override {
        return isSelect;
    }

    bool MoveShape(const QPoint&delta) override {
        int nx = x() + delta.x();
        int ny = y() + delta.y();

        QRect rectMove(nx,ny, sizeX,sizeY);
        if(!parentWidget()->rect().contains(rectMove))return false;

        move(nx,ny);

        for(group_store->first();!group_store->eol();group_store->next()){
            if(!group_store->getObject()->MoveShape(delta))return false;
        }
        // updateSize();
        return true;
    }

    void EditColor(const QString &c) override {
        for(group_store->first();!group_store->eol();group_store->next()){
            group_store->getObject()->EditColor(c);
        }
    }

    void ResizeThat(const QPoint &delta) override {
        for(group_store->first();!group_store->eol();group_store->next()){
            group_store->getObject()->ResizeThat(delta);
        }
        updateSize();
    }

    void paintEvent(QPaintEvent *) override {
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

};

#endif // GROUP_H
