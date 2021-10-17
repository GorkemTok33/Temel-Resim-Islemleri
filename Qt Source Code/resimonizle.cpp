/****************************************************************************************
Program: PictureDesigner
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/


#include "resimonizle.h"
#include "ui_resimonizle.h"


ResimOnizle::ResimOnizle(int openId, MainWindow *mw, QImage *image ,QWidget *parent):
    QDialog(parent),
    ui(new Ui::ResimOnizle)
{
    ui->setupUi(this);
    this->setWindowTitle("Resim Önizle");
    ui->label->setPixmap(QPixmap::fromImage(*image).scaled(ui->label->size(),Qt::KeepAspectRatio));
    this->mw = mw;
    this->id = openId;
}

ResimOnizle::~ResimOnizle()
{
    delete ui;
}

void ResimOnizle::on_pushButton_clicked()
{
   if(id == 0)
   {
        mw->ApplyImageFromFindContours();
   }

   else if(id == 1)
   {
        mw->ApplyColorizedAndLoadedImage();
   }

   this->close();
}
