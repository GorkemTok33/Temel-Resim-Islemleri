/****************************************************************************************
Program: PictureDesigner
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/


#ifndef APPLYPAST_H
#define APPLYPAST_H

#include <QDialog>
#include <QList>

namespace Ui {
class Applypast;
}

class Applypast : public QDialog
{
    Q_OBJECT

public:
    explicit Applypast(QList<QString> myList ,QWidget *parent = nullptr);
    ~Applypast();

private:
    Ui::Applypast *ui;
    QList<QString> myList;
};

#endif // APPLYPAST_H
