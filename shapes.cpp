#include"shapes.h"
#include<QPushButton>
#include<QDebug>
#include<QString>
#include<math.h>


Shape::Shape(const QPoint &b, const QPoint &e, QWidget *parent) : Prototype(parent) {
    qDebug()<<"created Shape with parametrs";
    sizeX = abs(e.x() - b.x());
    sizeY = abs(e.y()- b.y());
    SetSelect();
}

Shape::Shape(QWidget *parent) : Prototype(parent){

}

Shape::~Shape(){
    update();
}

void Shape::SetSelect() {
    isSelect = true;
    updateEditButton();
    update();
}

void Shape::ClearSelect() {
    isSelect = false;
    updateEditButton();
    update();
}

bool Shape::isSelect_() {
    return isSelect;
}

void Shape::PaintShape(){
    show();
}

bool Shape::MoveProto(const QPoint &delta) {
    int nx = x() + delta.x();
    int ny = y() + delta.y();

    QRect rectMove(nx,ny, sizeX,sizeY);
    if(!parentWidget()->rect().contains(rectMove))return false;

    move(nx,ny);
    return true;
}

void Shape::EditColor(const QColor &c) {
    color = c;
    update();
}

void Shape::CreatSize(const QPoint &b, const QPoint &e) {
    QRect parentRect = this->parentWidget()->rect();

    int ex = e.x();
    int ey = e.y();

    if (ex < parentRect.left()) ex = parentRect.left();
    else if (ex > parentRect.right()) ex = parentRect.right();

    if (ey < parentRect.top()) ey = parentRect.top();
    else if (ey > parentRect.bottom()) ey = parentRect.bottom();

    sizeX = abs(ex - b.x());
    sizeY = abs(ey - b.y());

    setFixedSize(sizeX, sizeY);

    if (b.x() < ex && b.y() > ey){
        move(b.x(), ey);
    }
    else if (b.x() > ex && b.y() < ey){
        move(ex, b.y());
    }
    else if (b.x() > ex && b.y() > ey){
        move(ex, ey);
    }
    else move(b.x(), b.y());

    if(edit){
        edit->move(sizeX - 20, sizeY - 20);
    }
    updateEditButton();
    update();
}

void Shape::ResizeThat(const QPoint &delta) {
    int nw = sizeX + delta.x();
    int nh = sizeY + delta.y();

    if (nw < 10) nw = 10;
    if (nh < 10) nh = 10;

    QRect parentRect = parentWidget()->rect();
    QRect newRect(x(), y(), nw, nh);
    if (!parentRect.contains(newRect))
        return;

    sizeX = nw;
    sizeY = nh;
    setFixedSize(sizeX, sizeY);

    if (edit) {
        edit->move(sizeX - 20, sizeY - 20);
    }
    if(isSelect)updateEditButton();
    update();
}

void Shape::Save(QTextStream &out) {
    out<<getSymbol()<<'\n';
    out<<x()<<'\n';
    out<<y()<<'\n';
    out<<sizeX<<'\n';
    out<<sizeY<<'\n';
    out<<color.name()<<'\n';
}

void Shape::Load(QTextStream &in) {
    int x,y;
    QString line;
    line = in.readLine();
    x = line.toInt();
    line = in.readLine();
    y = line.toInt();
    line = in.readLine();
    sizeX = line.toInt();
    line = in.readLine();
    sizeY = line.toInt();
    color = in.readLine();
    move(x,y);
    setFixedSize(sizeX,sizeY);
    EditColor(color);
    show();
}

void Shape::hideProto(){
    hide();
}

void Shape::showProto(){
    show();
}

Circle::Circle(const QPoint &b, const QPoint &e, QWidget *parent) : Shape(b, e, parent){
    qDebug()<<"Created Circle";
}

Circle::Circle(QWidget *parent) : Shape(parent){}

void Circle::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPen CirclePen;
    painter.setRenderHint(QPainter::Antialiasing);

    if (isSelect_()){
        QPen SelectPen;
        SelectPen.setDashPattern({4,4});
        SelectPen.setColor("cyan");
        SelectPen.setWidth(3);
        painter.setPen(SelectPen);
        painter.drawRect(0,0,sizeX,sizeY);
    }
    CirclePen.setColor(color);
    painter.setBrush(color);

    painter.setPen(CirclePen);
    painter.drawEllipse(0,0,sizeX,sizeY);
}

QString Circle::getSymbol(){
    return "C";
}

Rect::Rect(const QPoint &b, const QPoint &e, QWidget *parent)
    : Shape(b, e, parent)
{
    qDebug() << "Created Square";
}

Rect::Rect(QWidget *parent) : Shape(parent){}

void Rect::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen rectPen(color);
    painter.setPen(rectPen);
    painter.setBrush(color);
    painter.drawRect(0, 0, sizeX, sizeY);

    if (isSelect_()) {
        QPen selectPen(Qt::cyan);
        selectPen.setDashPattern({4, 4});
        selectPen.setWidth(3);
        painter.setPen(selectPen);
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(0, 0, sizeX, sizeY);
    }
}

QString Rect::getSymbol(){
    return "R";
}

Triangle::Triangle(const QPoint &b, const QPoint &e, QWidget *parent)
    : Shape(b, e, parent)
{
    qDebug() << "Created Triangle";
}

Triangle::Triangle(QWidget *parent) : Shape(parent){}

void Triangle::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen trianglePen(color);
    painter.setPen(trianglePen);
    painter.setBrush(color);

    QPolygonF poly;
    poly << QPointF(sizeX / 2.0, 0)
         << QPointF(sizeX,       sizeY)
         << QPointF(0,           sizeY);
    painter.drawPolygon(poly);

    if (isSelect_()) {
        QPen selectPen(Qt::cyan);
        selectPen.setDashPattern({4, 4});
        selectPen.setWidth(3);
        painter.setPen(selectPen);
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(0, 0, sizeX, sizeY);
    }
}

QString Triangle::getSymbol(){
    return "T";
}

Section::Section(const QPoint &b, const QPoint &e, QWidget *parent) : Shape(b, e, parent){
    qDebug()<<"Created Circle";
}

Section::Section(QWidget *parent) : Shape(parent){}

void Section::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPen SectionPen;
    painter.setRenderHint(QPainter::Antialiasing);

    if (isSelect_()){
        QPen SelectPen;
        SelectPen.setDashPattern({4,4});
        SelectPen.setColor("cyan");
        SelectPen.setWidth(3);
        painter.setPen(SelectPen);
        painter.drawRect(0,0,sizeX,sizeY);
    }
    SectionPen.setColor(color);
    painter.setPen(SectionPen);
    painter.drawLine(0,0,sizeX,sizeY);
}

QString Section::getSymbol(){
    return "S";
}
