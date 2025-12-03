#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    store = new MyStorage();

    connect(ui->radioBlue,&QRadioButton::clicked,this,&MainWindow::EditColorByRadioBtton);
    connect(ui->radioGreen,&QRadioButton::clicked,this,&MainWindow::EditColorByRadioBtton);
    connect(ui->radioOrange,&QRadioButton::clicked,this,&MainWindow::EditColorByRadioBtton);
    connect(ui->radioBlack,&QRadioButton::clicked,this,&MainWindow::EditColorByRadioBtton);
    connect(ui->radioPink,&QRadioButton::clicked,this,&MainWindow::EditColorByRadioBtton);
    connect(ui->radioRed,&QRadioButton::clicked,this,&MainWindow::EditColorByRadioBtton);
    connect(ui->radioWhite,&QRadioButton::clicked,this,&MainWindow::EditColorByRadioBtton);
    connect(ui->radioYellow,&QRadioButton::clicked,this,&MainWindow::EditColorByRadioBtton);

    ui->radioWhite->setChecked(true);
    EditColorByRadioBtton();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event){//one click
    b = event->pos();
    if (event->button() == Qt::LeftButton)
    {
        qDebug()<<"enter to LeftClick";

        bool ctrl = event->modifiers() & Qt::ControlModifier;

        if(!ctrl){
            store->clearSelection();
            isSelecting = false;
        }

        for (store->first();!store->eol();store->next()){
            if(store->getObject()->isCordBelong(event->pos())){
                store->getObject()->SetSelect();
                isSelecting = true;
                postpoint = event->pos();
                return;
            }
        }
        if(!isSelecting) store->clearSelection();

        postpoint = b;
    }
    else if (event->button() == Qt::RightButton){
        store->clearSelection();
        if(!rubBand){
            rubBand = new QRubberBand(QRubberBand::Rectangle, this);
        }
        rubBand->setGeometry(QRect(b,QSize()));
        rubBand->show();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){//moveclick
    e = event->pos();
    if(event->buttons() & Qt::LeftButton){//left click
        if (isrResizing) {//resizing
            delta = e - lastResizePos;
            lastResizePos = e;

            for (store->first(); !store->eol(); store->next()) {
                if(store->getObject()->isSelect_()){
                    store->getObject()->ResizeThat(delta);
                }
            }
            return;
        }
        if (!isSelecting ){//creating
            if(!s){
                s = GiveMe();
                s->EditColor(color);
                store->add(s);
            }
            dynamic_cast<Shape*>(s)->CreatSize(b,e);
            s->PaintShape();
        }

        else{//moving
            isMoving = true;
            delta = e - postpoint;
            postpoint = e;

            for(store->first();!store->eol();store->next()){
                if(store->getObject()->isSelect_()) {
                    com = new MoveCommand(delta);
                    com->execute(store->getObject());
                    delete com;
                    com = nullptr;
                }
            }
        }
    }
    else if (event->buttons() & Qt::RightButton){//right click -> rubberBand
        if(rubBand)rubBand->setGeometry(QRect(b,e).normalized());
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *){//unclick
    if(s) s = nullptr;
    if (isrResizing) {//stop resizing
        isrResizing = false;
        releaseMouse();
    }
    if(isMoving){
        isMoving = false;
        delta = e - b;
        for(store->first();!store->eol();store->next()){
            if(store->getObject()->isSelect_()){
                coms.push(new MoveCommand(delta,store->getObject()));
            }
        }
    }
    if(rubBand && rubBand->isVisible()){
        for(store->first();!store->eol();store->next()){
            if(rubBand->geometry().contains(store->getObject()->geometry())){
                store->getObject()->SetSelect();
            }
        }
        rubBand->hide();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event){//key contoller
    int key = event->key();

    if (key == Qt::Key_Delete){
        qDebug()<<"Key is Delete";
        store->deleteCircles();
        while(!coms.isEmpty())coms.pop();
    }
    else if(key == Qt::Key_Z){
        if(!coms.isEmpty())
        {
            com = coms.top();
            coms.pop();
            com->unexecute();
            delete com;
        }
    }

}

void MainWindow::EditColorByRadioBtton(){ //color editor
if (ui->radioBlue->isChecked()){
        color = "blue";
    }
    else if (ui->radioBlack->isChecked()){
        color = "black";
    }
    else if (ui->radioGreen->isChecked()){
        color = "green";
    }
    else if (ui->radioOrange->isChecked()){
        color = "orange";
    }
    else if (ui->radioPink->isChecked()){
        color = "pink";
    }
    else if (ui->radioRed->isChecked()){
        color = "red";
    }
    else if (ui->radioWhite->isChecked()){
        color = "white";
    }
    else if (ui->radioYellow->isChecked()){
        color = "yellow";
    }

    for(store->first();!store->eol();store->next()){
        if(store->getObject()->isSelect_()){
            store->getObject()->EditColor(color);
        }
    }

}

Shape* MainWindow::GiveMe(){// like fabric
    int key = ui->comboBox->currentIndex();
    Shape *ns;
    switch (key)
    {
    case 0 :
        ns =  new Circle(b,e,this);
        break;
    case 1 :
        ns = new Rect(b,e,this);
        break;
    case 2 :
        ns = new Triangle(b,e,this);
        break;
    case 3 :
        ns = new Section(b,e,this);
        break;
    }

    connect(ns, &Prototype::editPressed,this, &MainWindow::onPrototypeEditPressed);

    return ns;

}

void MainWindow::onPrototypeEditPressed(Prototype *sh)//editBtn is pressed
{
    if(sh->isSelect_()){
        isrResizing = true;
        lastResizePos = mapFromGlobal(QCursor::pos());
        grabMouse();
    }
}

void MainWindow::on_pushButton_group_clicked()//grouping
{
    group = new Group(this);

    connect(group, &Prototype::editPressed, this, &MainWindow::onPrototypeEditPressed);

    // store->first();
    // while(!store->eol()) {
    //     if(store->getObject()->isSelect_()) {
    //         group->push(store->exclude(store->getObject()));
    //         store->first();
    //     } else {
    //         store->next();
    //     }
    // }

    // if(!group->isEmpty())
    //     store->add(group);
    // else delete group;

    com = new GroupCommand(store);
    com->execute(group);
    coms.push(com);
}


void MainWindow::on_pushButton_ungroup_clicked()//ungrouping
{
    // for(store->first();!store->eol();){
    //     Prototype*group_maybe = store->getObject();
    //     if(group_maybe->isSelect_() && dynamic_cast<Group*>(group_maybe)){
    //         Group*ungroup = dynamic_cast<Group*>(store->exclude(group_maybe));
    //         while(!ungroup->isEmpty()){
    //             store->add(ungroup->exclude_first());
    //         }
    //         delete ungroup;
    //     }

    //     else store->next();
    // }

    com = new GroupCommand(store);
    com->unexecute();
}

