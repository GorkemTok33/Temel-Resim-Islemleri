/****************************************************************************************
Program: PictureDesigner
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/


#include "fileoperations.h"

FileOperations::FileOperations()
{
    qfileDialog = new QFileDialog();
}

QString FileOperations::LoadImageFromFile(MainWindow *mw)
{
    QString filter = "Resim Dosyaları (*.png *.jpg *.jpeg)";
    filePath = qfileDialog->getOpenFileName(mw, "Resim seçme",QDir::homePath(),filter);
    return filePath;
}

QString FileOperations::SaveImage(MainWindow *mw)
{
    QString filter = "Resim Dosyası (*.png);;Resim Dosyası (*.jpg);;Resim Dosyası (*jpeg)";
    filePath = qfileDialog->getSaveFileName(mw, "Resim kaydetme",QDir::homePath(), filter);
    return filePath;
}
