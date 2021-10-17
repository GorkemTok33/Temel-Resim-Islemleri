/****************************************************************************************
Program: PictureDesigner
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/

#ifndef ABOUTPROGRAM_H
#define ABOUTPROGRAM_H

#include <QDialog>

namespace Ui {
class aboutProgram;
}

class aboutProgram : public QDialog
{
    Q_OBJECT

public:
    explicit aboutProgram(QWidget *parent = nullptr);
    ~aboutProgram();

private:
    Ui::aboutProgram *ui;
};

#endif // ABOUTPROGRAM_H
