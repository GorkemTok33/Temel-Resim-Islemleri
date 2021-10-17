/****************************************************************************************
Program: PictureDesigner
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  "opencv_.h"
#include "aboutprogram.h"
#include <QDebug>
#include <QMessageBox>



Opencv_ *mycv;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->labelLoadedPicture->setStyleSheet("QLabel{background-color : black; }");
    ui->labelProcessPicture->setStyleSheet("QLabel{background-color : black;}");
    ui->lineEditFilterX->setValidator(new QIntValidator(-1,15,this));
    ui->lineEditFilterY->setValidator(new QIntValidator(-1,15,this));
    ui->lineEditFilterDelta->setValidator(new QDoubleValidator(0,15,3,this));
    ui->lineEditEdgeFoundDelta->setValidator(new QDoubleValidator(0,15,3,this));
    ui->groupBoxCanny->setEnabled(false);
    AllFalseBlur();
    ui->groupBoxSizeX->setEnabled(true);
    ui->groupBoxSizeY->setEnabled(true);
    ui->lineEditBlurancX->setEnabled(true);
    ui->lineEditBlurancY->setEnabled(true);
    for(int i = 1; i<8; i+=2)
    {
        ui->cBEdgeFoundSize->addItem(QString::number(i));
    }
    ui->checkBoxXT->setChecked(true);
    this->setWindowTitle("Temel Resim İşlemleri - Görkem Tok - 18.03.2021 - 1.1.0");
    mycv = new Opencv_(this, ui->labelLoadedPicture, ui->labelProcessPicture,ui->labelx,ui->labelY, ui->labelinc, ui->labelch,
                       ui->label_x1, ui->label_y1, ui->label_inc1, ui->label_ch1, ui->lblValues);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ApplyEdgeFound()
{
    mycv->EdgeDetection(ui->cbEdge->currentIndex(), ui->checkBoxXT->isChecked(), ui->checkBoxYT->isChecked(),
                        ui->cBEdgeFoundSize->currentText().toInt(),
                        scale,ui->lineEditEdgeFoundDelta->text().toInt(),thressMin,thressMax);
}

void MainWindow::ApplyBlur()
{
    mycv->Blur(ui->comboBoxBlurFunctions->currentIndex(), sizeX, sizeY,ui->lineEditBlurancX->text().toInt(),
               ui->lineEditBlurancY->text().toInt(), ui->lineEditBlurSigmaX->text().toDouble(),
               ui->lineEditBlurSigmaY->text().toDouble(), size, thressMin, thressMax);
}

void MainWindow::ApplyFilter2D()
{
    mycv->Filter2D(ui->comboBoxFilter->currentIndex(),ui->cbFilter2DFunc->currentIndex(),  ui->lineEditFilterX->text().toInt(),
                   ui->lineEditFilterY->text().toInt(), ui->lineEditFilterDelta->text().toDouble(),ui->comboBoxAdaptiveType->currentIndex(),
                   ui->comboBoxThreshType->currentIndex(),sizeX, sizeY, size);
}

void MainWindow::ApplyFilter2D(int currentIndex)
{
    mycv->Filter2D(ui->comboBoxFilter->currentIndex(),ui->cbFilter2DFunc->currentIndex(),  ui->lineEditFilterX->text().toInt(),
                   ui->lineEditFilterY->text().toInt(), ui->lineEditFilterDelta->text().toDouble(),ui->comboBoxAdaptiveType->currentIndex(),
                   currentIndex,sizeX, sizeY, size);
}

void MainWindow::ApplyMorphology()
{
    mycv->Morphology(ui->comboBoxMorphoFunc->currentIndex(), ui->comboBoxMorphoShape->currentIndex(), sizeX, sizeY,
                     ui->lineEditMorphAnchorX->text().toInt(), ui->lineEditMorphAncY->text().toInt(), size);
}

void MainWindow::ApplyColorFilter()
{
    mycv->ColorFilter(ui->labelMiniGray, hmin,smin,vmin,hmax,smax,vmax);
}

void MainWindow::ApplyfindContours()
{
    mycv->findContours(ui->lcdNumber,ui->comboBoxFindConMod->currentIndex(), ui->comboBoxFindConMethod->currentIndex(),
                       ui->lineEditcolorB->text().toInt(), ui->lineEditcolorG->text().toInt(), ui->lineEditcolorR->text().toInt(),
                       ui->comboBoxThickness->currentText().toInt(),ui->checkBoxfindConsNum->isChecked(), ui->checkBoxFindConLoaded->isChecked());
}

void MainWindow::AllFalseBlur()
{
    ui->groupBoxSizeX->setEnabled(false);
    ui->groupBoxSizeY->setEnabled(false);
    ui->lineEditBlurancX->setEnabled(false);
    ui->lineEditBlurancY->setEnabled(false);
    ui->lineEditBlurSigmaX->setEnabled(false);
    ui->lineEditBlurSigmaY->setEnabled(false);
    ui->groupBoxBlurK_Size->setEnabled(false);
    ui->groupBoxBlurBilateralColor->setEnabled(false);
    ui->groupBoxBileteralSigmaSpace->setEnabled(false);
}

void MainWindow::on_actionA_triggered()
{
    mycv->OpenImage();
}

void MainWindow::on_pushButton_clicked()
{
    ApplyPast.append(ui->comboBoxFilter->currentText()+" işlemi uygulandı.");
    mycv->Filter2DApply();
}

void MainWindow::on_lineEditFilterX_textChanged(const QString &arg1)
{
    if(arg1 == "")
    {
        ui->lineEditFilterX->setText("-1");
    }

    else if(arg1.toInt() > 2)
        ui->lineEditFilterX->setText("2");

    ApplyFilter2D();
}

void MainWindow::on_lineEditFilterY_textChanged(const QString &arg1)
{
    if(arg1 == "")
    {
        ui->lineEditFilterY->setText("-1");
    }

    else if(arg1.toInt() > 2)
        ui->lineEditFilterY->setText("2");

    ApplyFilter2D();
}

void MainWindow::on_lineEditFilterDelta_textChanged(const QString &arg1)
{
    if(arg1 == "")
    {
        ui->lineEditFilterDelta->setText("0");
    }

    ApplyFilter2D();
}


void MainWindow::on_pushButton_2_clicked()
{
    ApplyPast.append(ui->cbEdge->currentText()+" işlemi uygulandı.");
    mycv->EdgeApply();
}

void MainWindow::on_cbEdge_currentIndexChanged(int index)
{
    currentFunctionIndexcb = index;

    if(index == 0)
    {
        ui->cBEdgeFoundSize->clear();
        for(int i = 1; i<8; i+=2)
        {
            ui->cBEdgeFoundSize->addItem(QString::number(i));
        }

        if(!ui->checkBoxXT->isChecked() && !ui->checkBoxYT->isChecked())
            ui->checkBoxXT->setChecked(true);

        ui->groupBoxEdgeFoundTStatue->setEnabled(true);
        ui->groupBoxCanny->setEnabled(false);
        ui->checkBoxXT->setEnabled(true);
        ui->checkBoxYT->setEnabled(true);
        ui->cBEdgeFoundSize->setEnabled(true);
        ui->sliderScale->setEnabled(true);
        ui->lineEditEdgeFoundDelta->setEnabled(true);
        qDebug()<<"Sobel";
    }

    else if(index == 1)
    {
        ui->cBEdgeFoundSize->clear();
        for(int i = 3; i<20; i+=2)
        {
            ui->cBEdgeFoundSize->addItem(QString::number(i));
        }

        if(!ui->checkBoxXT->isChecked() && !ui->checkBoxYT->isChecked())
            ui->checkBoxXT->setChecked(true);

        ui->groupBoxEdgeFoundTStatue->setEnabled(false);
        ui->groupBoxCanny->setEnabled(false);
        ui->cBEdgeFoundSize->setEnabled(true);
        ui->sliderScale->setEnabled(true);
        ui->lineEditEdgeFoundDelta->setEnabled(true);

        qDebug()<<"Laplacian";
    }

    else if(index == 2)
    {
        ui->cBEdgeFoundSize->clear();
        for(int i = 1; i<15; i++)
        {
            ui->cBEdgeFoundSize->addItem(QString::number(i));
        }

        if(!ui->checkBoxXT->isChecked() && !ui->checkBoxYT->isChecked())
            ui->checkBoxXT->setChecked(true);
        else if(ui->checkBoxXT->isChecked() || ui->checkBoxYT->isChecked())
        {
             ui->checkBoxXT->setChecked(true);
             ui->checkBoxYT->setChecked(false);
        }

        ui->groupBoxEdgeFoundTStatue->setEnabled(true);
        ui->groupBoxCanny->setEnabled(false);
        ui->checkBoxXT->setEnabled(true);
        ui->checkBoxYT->setEnabled(true);
        ui->sliderScale->setEnabled(true);
        ui->lineEditEdgeFoundDelta->setEnabled(true);
        ui->cBEdgeFoundSize->setEnabled(false);
        qDebug()<<"Scharr";
    }

    else if(index == 3)
    {
        ui->groupBoxCanny->setEnabled(true);
        ui->groupBoxEdgeFoundTStatue->setEnabled(false);
        ui->cBEdgeFoundSize->setEnabled(false);
        ui->checkBoxXT->setEnabled(false);
        ui->checkBoxYT->setEnabled(false);
        ui->lineEditEdgeFoundDelta->setEnabled(false);
        ui->sliderScale->setEnabled(false);
    }

    ApplyEdgeFound();
}


void MainWindow::on_sliderThressMin_sliderMoved(int position)
{
    thressMin = position;
    ApplyEdgeFound();
}

void MainWindow::on_sliderScale_sliderMoved(int position)
{
    scale = position;
    ApplyEdgeFound();
}

void MainWindow::on_sliderThressMax_sliderMoved(int position)
{
    thressMax = position;
    ApplyEdgeFound();
}

void MainWindow::on_lineEditEdgeFoundDelta_textChanged(const QString &arg1)
{
    if(arg1 == "")
        ui->lineEditEdgeFoundDelta->setText("0");
    ApplyEdgeFound();
}


void MainWindow::on_checkBoxXT_clicked()
{
    if(!ui->checkBoxYT->isChecked() && ui->cbEdge->currentIndex() == 0)
    {
        QMessageBox::information(this,"Sobel Türev Kuralı","Sobel dx+dy > 0 olmak zorundadır !");
        ui->checkBoxXT->setChecked(true);
    }

    else if(ui->checkBoxYT->isChecked() && ui->cbEdge->currentIndex() == 2)
    {
        ui->checkBoxXT->setChecked(true);
        ui->checkBoxYT->setChecked(false);
    }

    else if(!ui->checkBoxXT->isChecked() && !ui->checkBoxYT->isChecked() && ui->cbEdge->currentIndex() == 2)
    {
        QMessageBox::information(this,"Scharr Türev Kuralı","Scharr dx+dy = 0 olmalıdır");
        ui->checkBoxXT->setChecked(true);
    }

    ApplyEdgeFound();
    return;
}

void MainWindow::on_checkBoxYT_clicked()
{
    if(!ui->checkBoxXT->isChecked() && ui->cbEdge->currentIndex() == 0)
    {

        QMessageBox::information(this,"Sobel Türev Kuralı","Sobel dx+dy > 0 olmak zorundadır !");
        ui->checkBoxYT->setChecked(true);
    }

    else if(ui->checkBoxXT->isChecked() && ui->cbEdge->currentIndex() == 2)
    {
        ui->checkBoxYT->setChecked(true);
        ui->checkBoxXT->setChecked(false);
    }

    else if(!ui->checkBoxXT->isChecked() && !ui->checkBoxYT->isChecked() && ui->cbEdge->currentIndex() == 2)
    {
        QMessageBox::information(this,"Scharr Türev Kuralı","Scharr dx+dy = 0 olmalıdır");
        ui->checkBoxYT->setChecked(true);
    }

    ApplyEdgeFound();
    return;
}

void MainWindow::on_comboBoxBlurFunctions_currentIndexChanged(int index)
{
    if(index == 0)
    {
        AllFalseBlur();
        ui->groupBoxSizeX->setEnabled(true);
        ui->groupBoxSizeY->setEnabled(true);
        ui->lineEditBlurancX->setEnabled(true);
        ui->lineEditBlurancY->setEnabled(true);
    }

    else if(index == 1)
    {
        AllFalseBlur();
        ui->groupBoxSizeX->setEnabled(true);
        ui->groupBoxSizeY->setEnabled(true);
        ui->lineEditBlurSigmaX->setEnabled(true);
        ui->lineEditBlurSigmaY->setEnabled(true);
    }

    else if(index == 2)
    {
        AllFalseBlur();
        size = 3;
        ui->groupBoxBlurK_Size->setEnabled(true);
    }

    else if(index == 3)
    {
        AllFalseBlur();
        ui->groupBoxSizeX->setEnabled(true);
        ui->groupBoxSizeY->setEnabled(true);
        ui->lineEditBlurancX->setEnabled(true);
        ui->lineEditBlurancY->setEnabled(true);
    }

    else if(index == 4)
    {
        AllFalseBlur();
        ui->groupBoxBlurK_Size->setEnabled(true);
        ui->groupBoxBlurBilateralColor->setEnabled(true);
        ui->groupBoxBileteralSigmaSpace->setEnabled(true);
    }

    ApplyBlur();
}


void MainWindow::on_horizontalSliderBlurScaleX_sliderMoved(int position)
{
    sizeX = position;
    if(sizeX%2==0)
        sizeX+=1;
    qDebug()<<sizeX;
    ApplyBlur();
}

void MainWindow::on_horizontalSliderBlurScaleY_sliderMoved(int position)
{
    sizeY = position;
    if(sizeY%2==0)
        sizeY+=1;
    qDebug()<<sizeY;
    ApplyBlur();
}

void MainWindow::on_horizontalSliderBlurSigmaColor_2_sliderMoved(int position)
{
    size = position;
    if(size % 2 == 0 && ui->comboBoxBlurFunctions->currentIndex() == 2)
        size +=1;
    ApplyBlur();
}

void MainWindow::on_horizontalSliderBlurSigmaColor_sliderMoved(int position)
{
    thressMin = position;
    ApplyBlur();
}

void MainWindow::on_horizontalSliderBlurSigmaSpace_sliderMoved(int position)
{
    thressMax = position;
    ApplyBlur();
}

void MainWindow::on_pushButton_3_clicked()
{
    ApplyPast.append(ui->comboBoxBlurFunctions->currentText()+" işlemi uygulandı.");
    mycv->BluredApply();
}

void MainWindow::on_lineEditBlurancX_textChanged(const QString &arg1)
{
    if(arg1 == "")
        ui->lineEditBlurancX->setText("-1");
    ApplyBlur();
}

void MainWindow::on_lineEditBlurancY_textChanged(const QString &arg1)
{
    if(arg1 == "")
        ui->lineEditBlurancY->setText("-1");
    ApplyBlur();
}

void MainWindow::on_lineEditBlurSigmaX_textChanged(const QString &arg1)
{
    if(arg1 == "")
        ui->lineEditBlurSigmaX->setText("0");
    ApplyBlur();
}

void MainWindow::on_lineEditBlurSigmaY_textChanged(const QString &arg1)
{
    if(arg1 == "")
        ui->lineEditBlurSigmaY->setText("0");
    ApplyBlur();
}

void MainWindow::on_cbFilter2DFunc_currentIndexChanged(int index)
{
    ApplyFilter2D(0);
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    sizeX = position; // kernel x
    ApplyMorphology();
}

void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
    sizeY = position; // kernel y
    ApplyMorphology();
}

void MainWindow::on_horizontalSlider_3_sliderMoved(int position)
{
    size = position; // apply time
    ApplyMorphology();
}

void MainWindow::on_comboBoxMorphoFunc_currentIndexChanged(int index)
{
    ApplyMorphology();
}

void MainWindow::on_comboBoxMorphoShape_currentIndexChanged(int index)
{
    ApplyMorphology();
}

void MainWindow::on_pushButton_4_clicked()
{
    ApplyPast.append(ui->comboBoxMorphoFunc->currentText()+" işlemi uygulandı.");
    mycv->ApplyMorphology();
}

void MainWindow::on_actionProgram_Hakk_nda_triggered()
{
    aboutMe = new aboutProgram(this);
    aboutMe->show();
}

void MainWindow::on_sliderFilterSizeK_sliderMoved(int position)
{
    size = position; // k_size fro adaptive thresh
    if(size % 2 == 0)
        size +=1;
    ApplyFilter2D();
}

void MainWindow::on_sliderFilterThressMin_sliderMoved(int position)
{
    sizeX = position; // thresh min
    ApplyFilter2D();
}

void MainWindow::on_sliderFilterThressMax_3_sliderMoved(int position)
{
    sizeY = position; // thresh max
    ApplyFilter2D();
}

void MainWindow::on_comboBoxFilter_currentIndexChanged(int index)
{
    size = 3;
    ui->lineEditFilterDelta->setEnabled(false);
    ui->lineEditFilterX->setEnabled(false);
    ui->lineEditFilterY->setEnabled(false);
    ui->cbFilter2DFunc->setEnabled(false);
    ui->comboBoxThreshType->setEnabled(false);
    ui->comboBoxAdaptiveType->setEnabled(false);
    ui->sliderFilterThressMin->setEnabled(false);
    ui->sliderFilterThressMax_3->setEnabled(false);
    ui->sliderFilterSizeK->setEnabled(false);

    if(index == 0)
    {
        ui->lineEditFilterDelta->setEnabled(true);
        ui->lineEditFilterX->setEnabled(true);
        ui->lineEditFilterY->setEnabled(true);
        ui->cbFilter2DFunc->setEnabled(true);
    }

    else if(index == 1)
    {
        ui->comboBoxThreshType->clear();
        ui->comboBoxThreshType->addItem("BINARY");
        ui->comboBoxThreshType->addItem("BINARY_INV");
        ui->comboBoxThreshType->addItem("TRUNC");
        ui->comboBoxThreshType->addItem("TO ZERO");
        ui->comboBoxThreshType->addItem("TO ZERO_INV");
        ui->sliderFilterThressMin->setEnabled(true);
        ui->sliderFilterThressMax_3->setEnabled(true);
        ui->comboBoxThreshType->setEnabled(true);
    }

    else if(index == 2)
    {
        ui->comboBoxThreshType->clear();
        ui->comboBoxThreshType->addItem("BINARY");
        ui->comboBoxThreshType->addItem("BINARY_INV");
        ui->sliderFilterThressMax_3->setEnabled(true);
        ui->sliderFilterSizeK->setEnabled(true);
        ui->comboBoxAdaptiveType->setEnabled(true);
        ui->comboBoxThreshType->setEnabled(true);
    }

    ApplyFilter2D(0);
}

void MainWindow::on_comboBoxThreshType_currentIndexChanged(int index)
{
    qDebug()<<ui->comboBoxThreshType->currentIndex();
    ApplyFilter2D();
}

void MainWindow::on_comboBoxAdaptiveType_currentIndexChanged(int index)
{
    ApplyFilter2D();
}

void MainWindow::on_actionFarkl_Kaydet_triggered()
{
    mycv->SaveImage();
}

void MainWindow::on_actionYazd_r_triggered()
{
    QImage img;
    if(mycv->GetLoadedQImage(img))
    {
            QPrinter printer;
            QPrintDialog dialog(&printer, this);
                 if (dialog.exec())
                 {
                     QPainter painter(&printer);
                     QRect rect = painter.viewport();
                     QSize size = ui->labelLoadedPicture->pixmap()->size();
                     size.scale(rect.size(), Qt::KeepAspectRatio);
                     painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
                     painter.setWindow(ui->labelLoadedPicture->pixmap()->rect());
                     painter.drawPixmap(0, 0, *ui->labelLoadedPicture->pixmap());
                 }
            QMessageBox::information(this,"Yazdırma Sonucu", "İşlem Başarılı !");
    }
}

void MainWindow::on_horizontalSliderHMax_sliderMoved(int position)
{
    hmax = position;
    ApplyColorFilter();
}

void MainWindow::on_horizontalSliderHMin_sliderMoved(int position)
{
    hmin = position;
    ApplyColorFilter();
}

void MainWindow::on_horizontalSliderSatMax_sliderMoved(int position)
{
    smax = position;
    ApplyColorFilter();
}

void MainWindow::on_horizontalSliderSatMin_sliderMoved(int position)
{
    smin = position;
    ApplyColorFilter();
}

void MainWindow::on_horizontalSliderValMax_sliderMoved(int position)
{
    vmax = position;
    ApplyColorFilter();
}

void MainWindow::on_horizontalSliderValMin_sliderMoved(int position)
{
    vmin = position;
    ApplyColorFilter();
}

void MainWindow::on_pushButton_6_clicked()
{
    ApplyPast.append("Renk Filtreleme işlemi uygulandı.");
    mycv->ApplyColorFilter();
}

void MainWindow::on_action_lem_Ge_mi_i_triggered()
{
    apllypast = new Applypast(ApplyPast, this);
    apllypast->show();
}

void MainWindow::on_sliderFilterSizeK_actionTriggered(int action)
{

}

void MainWindow::on_actionResmi_Renklendir_triggered()
{
    mycv->ColorizeImageMethodNormal();
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{

}

void MainWindow::on_comboBoxFindConMod_currentIndexChanged(int index)
{
    ApplyfindContours();
}

void MainWindow::on_comboBoxFindConMethod_currentIndexChanged(int index)
{
    ApplyfindContours();
}

void MainWindow::on_lineEditcolorB_textChanged(const QString &arg1)
{
    if(arg1 == "")
        ui->lineEditcolorB->setText("0");
    else if(arg1.toInt() > 255)
        ui->lineEditcolorB->setText("255");
    else if(arg1.toInt() < 0)
        ui->lineEditcolorB->setText("0");
    ApplyfindContours();
}

void MainWindow::on_lineEditcolorG_textChanged(const QString &arg1)
{
    if(arg1 == "")
        ui->lineEditcolorG->setText("0");
    else if(arg1.toInt() > 255)
        ui->lineEditcolorG->setText("255");
    else if(arg1.toInt() < 0)
        ui->lineEditcolorG->setText("0");

    ApplyfindContours();
}

void MainWindow::on_lineEditcolorR_textChanged(const QString &arg1)
{
    if(arg1 == "")
        ui->lineEditcolorR->setText("0");
    else if(arg1.toInt() > 255)
        ui->lineEditcolorR->setText("255");
    else if(arg1.toInt() < 0)
        ui->lineEditcolorR->setText("0");
    ApplyfindContours();
}

void MainWindow::on_checkBoxfindConsNum_clicked()
{
    ApplyfindContours();
}

void MainWindow::on_checkBoxFindConLoaded_clicked()
{
    ApplyfindContours();
}

void MainWindow::on_comboBoxThickness_currentIndexChanged(int index)
{
    ApplyfindContours();
}

void MainWindow::on_pushButton_5_clicked()
{
    mycv->findContoursApply();
}

void MainWindow::ApplyImageFromFindContours()
{
    mycv->findContoursApply(true);
}

void MainWindow::on_actionYap_lan_lemleri_Geri_Al_triggered()
{
    mycv->TakeBackEverything();
}

void MainWindow::ApplyColorizedAndLoadedImage()
{
    mycv->ApplyColorizedImage();
}
