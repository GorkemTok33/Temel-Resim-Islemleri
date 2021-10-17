/****************************************************************************************
Program: PictureDesigner
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/


#ifndef PICTUREOPERATIONS_H
#define PICTUREOPERATIONS_H

#include <QImage>
#include <QLabel>
#include <QDebug>


class PictureOperations
{
public:
    PictureOperations();
    void PutImageIntoLabel(QImage qimage, QLabel *imageLabel);
    void ZoomInImage();
    void ZoomOutImage();

private:
    QLabel *imageLabel;

};

#endif // PICTUREOPERATIONS_H
