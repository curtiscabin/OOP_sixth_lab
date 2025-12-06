#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once

#include<QMainWindow>
#include<QMouseEvent>
#include"mystorage.h"
#include"shapes.h"
#include"group.h"
#include"command.h"
#include<QRubberBand>
#include<QFileDialog>
#include<QColorDialog>
#include<QStack>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_group_clicked();

    void on_pushButton_ungroup_clicked();

    void on_LoadFile_triggered();

    void on_SaveFile_triggered();

    void on_CloseApp_triggered();

    void on_pushButtonColor_clicked();

private:
    Ui::MainWindow *ui;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;
    void onPrototypeEditPressed(Prototype *sh);
    Shape* GiveMe();
    MyStorage *store;
    QPoint b;
    QPoint e;
    QPoint delta;
    QPoint postpoint;
    QColor color = "white";
    Shape *s = nullptr;
    bool isSelecting = false;
    bool isResizing = false;
    bool isMoving = false;
    QPoint lastResizePos;
    QRubberBand* rubBand = nullptr;
    Group* group = nullptr;
    QString filename;
    Command* com = nullptr;
    QStack<Command*> undo;
    QStack<Command*> redo;

};
#endif // MAINWINDOW_H
