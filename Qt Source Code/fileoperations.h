/****************************************************************************************
Program: PictureDesigner
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/


#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <QString>
#include <QFileDialog>
#include "mainwindow.h"

class FileOperations
{

public:
    FileOperations();
    QString LoadImageFromFile(MainWindow *mw);
    QString SaveImage(MainWindow *mw);

private:
    QString filePath;
    QFileDialog *qfileDialog;


};

#endif // FILEOPERATIONS_H
