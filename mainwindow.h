#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once

#include <QMainWindow>
#include<QMouseEvent>
// #include"mystorage.h"
#include"shapes.h"
#include"prototype.h"
#include"group.h"
#include<QRubberBand>
#include <QFileDialog>

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

private:
    Ui::MainWindow *ui;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void keyPressEvent(QKeyEvent *event) override;
    void EditColorByRadioBtton();
    void onPrototypeEditPressed(Prototype *sh);
    Shape* GiveMe();
    MyStorage *store;
    QPoint b;
    QPoint e;
    QPoint delta;
    QPoint postpoint;
    QString color;
    Shape *s = nullptr;
    bool isSelecting = false;
    bool groupResizing = false;
    QPoint lastResizePos;
    QRubberBand* rubBand = nullptr;
    Group* group = nullptr;

};
#endif // MAINWINDOW_H
