/****************************************************************************************
Program: PictureDesigner
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/


#include "aboutprogram.h"
#include "ui_aboutprogram.h"

aboutProgram::aboutProgram(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutProgram)
{
    ui->setupUi(this);
    this->setWindowTitle("Program Hakkında");
}

aboutProgram::~aboutProgram()
{
    delete ui;
}
