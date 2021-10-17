/****************************************************************************************
Program: PictureDesigner
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/


#include "pictureoperations.h"


PictureOperations::PictureOperations()
{

}

void PictureOperations::PutImageIntoLabel(QImage qimage, QLabel *imageLabel)
{
    imageLabel->setPixmap(QPixmap::fromImage(qimage).scaled(imageLabel->size(),Qt::KeepAspectRatio));
    qDebug()<<"PutImageIntoLabel: Success";
    return;
}
