#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    store = new MyStorage();

}
MainWindow::~MainWindow()
{
    delete ui;
    delete store;
}

void MainWindow::mousePressEvent(QMouseEvent *event){
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
        if (isResizing) {//resizing
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

            com = new MoveCommand(delta, store);
            com->execute();
            delete com;
        }
    }
    else if (event->buttons() & Qt::RightButton){//right click -> rubberBand
        if(rubBand)rubBand->setGeometry(QRect(b,e).normalized());
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *){//unclick
    if(s) s = nullptr;
    if (isResizing) {//stop resizing
        isResizing = false;
        releaseMouse();
    }
    if(isMoving){
        isMoving = false;
        delta = e - b;
        undo.push(new MoveCommand(delta, store));
        eraseRedo();
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

void MainWindow::keyPressEvent(QKeyEvent *event){
    int key = event->key();

    if (key == Qt::Key_Delete){
        qDebug()<<"Key is Delete";
        com = new DeleteCommand(store);
        com->execute();
        undo.push(com);
        com = nullptr;
        eraseRedo();
    }
    else if (key == Qt::Key_O){
        qDebug()<<"Key is O";
        on_LoadFile_triggered();
    }
    else if (key == Qt::Key_S){
        qDebug()<<"Key is S";
        if(!filename.isEmpty())store->SaveOpen(filename);
        else on_SaveFile_triggered();
    }
    else if(key == Qt::Key_Z && (event->modifiers() & Qt::ShiftModifier)){
        qDebug()<<"Key is Z and Shift";
        if(!redo.isEmpty())
        {
            com = redo.top();
            redo.pop();
            com->execute();
            undo.push(com);
        }
    }
    else if(key == Qt::Key_Z){
        qDebug()<<"Key is Z";
        if(!undo.isEmpty())
        {
            com = undo.top();
            undo.pop();
            com->unexecute();
            redo.push(com);
        }
    }

}


Shape* MainWindow::GiveMe(){
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

void MainWindow::eraseRedo()
{
    while(!redo.isEmpty()){
        redo.pop();
    }
}

void MainWindow::onPrototypeEditPressed(Prototype *sh)
{
    if(sh->isSelect_()){
        isResizing = true;
        lastResizePos = mapFromGlobal(QCursor::pos());
        grabMouse();
    }
}

void MainWindow::on_pushButton_group_clicked()
{
    com = new GroupCommand(store, this);
    com->execute();
    undo.push(com);
    eraseRedo();

    for(store->first();!store->eol();store->next()){
        Prototype* group_maybe = store->getObject();
        if(dynamic_cast<Group*>(group_maybe) && group_maybe->isSelect_()){
            connect(group_maybe, &Prototype::editPressed, this, &MainWindow::onPrototypeEditPressed);
        }
    }
}


void MainWindow::on_pushButton_ungroup_clicked()
{
    com = new UnGroupCommand(store, this);
    com->execute();
    undo.push(com);
    eraseRedo();

    for(store->first();!store->eol();store->next()){
        Prototype* proto = store->getObject();
        if(proto->isSelect_())
        {
            connect(proto, &Prototype::editPressed, this, &MainWindow::onPrototypeEditPressed);
        }
    }

}


void MainWindow::on_LoadFile_triggered()
{
    filename = QFileDialog::getOpenFileName(this, "Открыть файл", "C:\\my_projects\\qt_projects\\OOP_sixth_lab\\saves", "Текстовые файлы (*.txt);;Все файлы (*.*)");
    afactory* fact = new ProtoFactory;

    if (!filename.isEmpty()) {
        qDebug() << "Выбран файл:" << filename;
        store->LoadOpen(filename, this, fact);
    }



    for(store->first();!store->eol();store->next()){
        connect(store->getObject(), &Prototype::editPressed,this, &MainWindow::onPrototypeEditPressed);
    }
}


void MainWindow::on_SaveFile_triggered()
{
    filename = QFileDialog::getSaveFileName(this,"Сохранить файл", "C:\\my_projects\\qt_projects\\OOP_sixth_lab\\saves","Текстовые файлы (*.txt);;Все файлы (*.*)", nullptr,QFileDialog::DontConfirmOverwrite);

    if (!filename.isEmpty()) {
        qDebug() << "Сохранить в:" << filename;
        store->SaveOpen(filename);
    }
}


void MainWindow::on_CloseApp_triggered()
{
    QApplication::quit();
}


void MainWindow::on_pushButtonColor_clicked()
{

    color = QColorDialog::getColor(QColor(255, 100, 200, 255));
    if (!color.isValid())
    {
        qDebug()<<color;
        color = "white";
        return;
    }
    qDebug()<<color;

    com = new EditColorCommand(store, color);
    com->execute();
    undo.push(com);
    eraseRedo();
}

