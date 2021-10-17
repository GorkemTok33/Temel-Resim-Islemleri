/****************************************************************************************
Program: PictureDesigner
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/


#ifndef RESIMONIZLE_H
#define RESIMONIZLE_H

#include <QDialog>
#include <QImage>
#include "mainwindow.h"

namespace Ui {
class ResimOnizle;
}

class ResimOnizle : public QDialog
{
    Q_OBJECT

public:
    explicit ResimOnizle(int openId, MainWindow *mw, QImage *image ,QWidget *parent = nullptr);
    ~ResimOnizle();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ResimOnizle *ui;
    MainWindow *mw;
    int id;

};

#endif // RESIMONIZLE_H
