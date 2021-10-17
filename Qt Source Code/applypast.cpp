/****************************************************************************************
Program: PictureDesigner
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/


#include "applypast.h"
#include "ui_applypast.h"

Applypast::Applypast(QList<QString> myList ,QWidget *parent):
    QDialog(parent),
    ui(new Ui::Applypast)
{
    ui->setupUi(this);
    this->myList = myList;
    for(int i = 0; i < myList.length(); i++)
        ui->listWidget->addItem(myList.at(i));
    this->setWindowTitle("Uygulanan işlem geçmişi.");
}

Applypast::~Applypast()
{
    delete ui;
}
