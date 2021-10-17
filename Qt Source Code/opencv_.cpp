/****************************************************************************************
Program: PictureDesigner
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/


#include "opencv_.h"
#include <QDebug>
#include <QPixmap>
#include <QMessageBox>
#include "fileoperations.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include <opencv2/photo/photo.hpp>
#include "pictureoperations.h"
#include <QString>
#include "mainwindow.h"
#include <QLabel>
#include <QImage>
#include <QtMath>


Opencv_::Opencv_(MainWindow *mw, QLabel *mainLabel, QLabel *processLabel, QLabel *lbx, QLabel *lby, QLabel *lbinch, QLabel *lbch,
                 QLabel *lbx1, QLabel *lby1, QLabel *lbinch1, QLabel *lbch1, QLabel *statusLabel)
{
    this->mw = mw;
    this->fileOperations = new FileOperations();
    this->poLoaded = new PictureOperations();
    this->poProcess = new PictureOperations();
    this->mainImageLabel = mainLabel;
    this->processImageLabel = processLabel;
    this->lbx = lbx;
    this->lbx1 = lbx1;
    this->lby = lby;
    this->lby1 = lby1;
    this->lbinc = lbinch;
    this->lbinc1 = lbinch1;
    this->lbch = lbch;
    this->lbch1 = lbch1;
    this->statusLabel = statusLabel;
}


void Opencv_::LoadImage(QString filepath)
{
    loadedImage = cv::imread(filepath.toStdString(), cv::IMREAD_ANYCOLOR|cv::IMREAD_ANYDEPTH);

    cv::Mat tempLoaded;

    if(loadedImage.data)
    {
         loadedImage.copyTo(originalImage);

        if(loadedImage.channels() > 1)
        {
            loadedImage.copyTo(OriginalColoredImage);
            cv::cvtColor(loadedImage, tempLoaded,CV_BGR2RGB);
            QImageLoaded = new QImage(tempLoaded.data,tempLoaded.cols,tempLoaded.rows,tempLoaded.step,QImage::Format_RGB888);
        }

        else if(loadedImage.channels() == 1)
        {
            cv::cvtColor(loadedImage, tempLoaded,CV_GRAY2RGB);
            QImageLoaded = new QImage(tempLoaded.data,tempLoaded.cols,tempLoaded.rows,tempLoaded.step,QImage::Format_RGB888);
        }

        poLoaded->PutImageIntoLabel(*QImageLoaded, mainImageLabel);
        SetLoadedImageInfo();
        qDebug() << "LoadImage: Succes";
        return;
    }

    qDebug() << "Failed To Load Image From "<<filePath;

    QMessageBox::information(mw,"Resim Yükleme Hatası","Üzgünüm, yüklemeye çalıştığınız resim açılamıyor. Resmin dosya yolunun ve adının Türkçe karakter içermediğinden emin olun ve tekrar deneyin.");

    return;
}

void Opencv_::SaveImage()
{
    filePath = fileOperations->SaveImage(mw);
    if(filePath != "")
    {
        cv::imwrite(filePath.toStdString(),loadedImage);
        QMessageBox::information(mw,"Kaydetme Sonucu","Resim "+filePath+" dizinine kaydedildi !");
    }
}

void Opencv_::OpenImage()
{
    filePath = fileOperations->LoadImageFromFile(mw);
    if( filePath != "")
        LoadImage(filePath);
}

void Opencv_::BluredApply()
{
    if(bluredImage.data)
    {
        bluredImage.copyTo(loadedImage);
        cv::Mat tempLoaded;

        cv::cvtColor(loadedImage, tempLoaded,CV_BGR2RGB);
        QImageLoaded = new QImage(tempLoaded.data,tempLoaded.cols,tempLoaded.rows,tempLoaded.step,QImage::Format_RGB888);

        poLoaded->PutImageIntoLabel(*QImageLoaded, mainImageLabel);

        SetLoadedImageInfo();
        qDebug()<<"Blured Done";
    }

    else
        QMessageBox::information(mw,"Resim bulunamadı","bu işlemi yapabilmek için resim seçmeniz gerekmektedir.");
}

void Opencv_::EdgeApply()
{
    if(afterProcessImage.data)
    {
        afterProcessImage.copyTo(loadedImage);
        cv::Mat tempLoaded;

        cv::cvtColor(loadedImage, tempLoaded, CV_BGR2RGB);
        QImageLoaded = new QImage(tempLoaded.data,tempLoaded.cols,tempLoaded.rows,tempLoaded.step,QImage::Format_RGB888);

        poLoaded->PutImageIntoLabel(*QImageLoaded, mainImageLabel);

        SetLoadedImageInfo();
        qDebug()<<"Edge Done";
    }

    else
        QMessageBox::information(mw,"Resim bulunamadı","bu işlemi yapabilmek için resim seçmeniz gerekmektedir.");
}

void Opencv_::Filter2DApply()
{
    if(filter2dImage.data)
    {
        filter2dImage.copyTo(loadedImage);
        cv::Mat tempLoaded;

        if(loadedImage.channels()>1)
            cv::cvtColor(loadedImage, tempLoaded, CV_BGR2RGB);
        else
            cv::cvtColor(loadedImage, tempLoaded, CV_GRAY2RGB);

        QImageLoaded = new QImage(tempLoaded.data,tempLoaded.cols,tempLoaded.rows,tempLoaded.step,QImage::Format_RGB888);

        poLoaded->PutImageIntoLabel(*QImageLoaded, mainImageLabel);

        SetLoadedImageInfo();
        qDebug()<<"Filter2D Done";
    }

    else
        QMessageBox::information(mw,"Resim bulunamadı","bu işlemi yapabilmek için resim seçmeniz gerekmektedir.");
}

void Opencv_::ApplyMorphology()
{
    if(morphologyImage.data)
    {
        morphologyImage.copyTo(loadedImage);
        cv::Mat tempLoaded;

        if(loadedImage.channels()>1)
            cv::cvtColor(loadedImage, tempLoaded, CV_BGR2RGB);

        else
            cv::cvtColor(loadedImage, tempLoaded, CV_GRAY2RGB);

        QImageLoaded = new QImage(tempLoaded.data,tempLoaded.cols,tempLoaded.rows,tempLoaded.step,QImage::Format_RGB888);

        poLoaded->PutImageIntoLabel(*QImageLoaded, mainImageLabel);

        SetLoadedImageInfo();
        qDebug()<<"Morphology Done";
    }

    else
        QMessageBox::information(mw,"Resim bulunamadı","bu işlemi yapabilmek için resim seçmeniz ve resim üzerinde değişiklik yapmanız gerekmektedir.");

}

void Opencv_::ApplyColorFilter()
{
    if(colorFilteredImage.data)
    {
        colorFilteredImage.copyTo(loadedImage);
        cv::Mat tempLoaded;

        if(loadedImage.channels()>1)
            cv::cvtColor(loadedImage, tempLoaded, CV_BGR2RGB);

        else
            cv::cvtColor(loadedImage, tempLoaded, CV_GRAY2RGB);

        QImageLoaded = new QImage(tempLoaded.data,tempLoaded.cols,tempLoaded.rows,tempLoaded.step,QImage::Format_RGB888);

        poLoaded->PutImageIntoLabel(*QImageLoaded, mainImageLabel);

        SetLoadedImageInfo();
        qDebug()<<"ColorFilter Done";
        return;
    }

    QMessageBox::information(mw,"Resim bulunamadı","bu işlemi yapabilmek için resim seçmeniz ve resim üzerinde değişiklik yapmanız gerekmektedir.");
    return;
}

void Opencv_::findContoursApply(bool t)
{
    if(grayImage.data)
    {
        if(!t)
            grayImage.copyTo(loadedImage);

        else if(t)
        {
            cv::cvtColor(tempdrawcontoursImage,tempdrawcontoursImage,CV_RGB2BGR);
            tempdrawcontoursImage.copyTo(loadedImage);
        }

        cv::Mat tempLoaded;

        cv::cvtColor(loadedImage, tempLoaded,CV_BGR2RGB);
        QImageLoaded = new QImage(tempLoaded.data,tempLoaded.cols,tempLoaded.rows,tempLoaded.step,QImage::Format_RGB888);

        poLoaded->PutImageIntoLabel(*QImageLoaded, mainImageLabel);

        SetLoadedImageInfo();
        qDebug()<<"findContours Done";
    }

    else
        QMessageBox::information(mw,"Resim bulunamadı","bu işlemi yapabilmek için resim seçmeniz gerekmektedir.");

    return;
}

bool Opencv_::Filter2D(int index, int kernel, int anchorX, int anchorY, double delta,int adaptiveType, int threshType, int deltaMin, int deltaMax, int size)
{
    if(loadedImage.data)
    {
        if(index == 0)
        {
            float *kernelData = nullptr;

            if(kernel == 0)
            {
                float Data[] = {0,0,0,0,1,0,0,0,0};
                kernelData = Data;
            }

            else if(kernel == 1)
            {
                float Data[] = {1,0,-1,0,0,0,-1,0,1};
                kernelData = Data;
            }

            else if(kernel == 2)
            {
                float Data[] = {0,-1,0,-1,4,-1,0,-1,0};
                kernelData = Data;
            }

            else if(kernel == 3)
            {
                float Data[] = {-1,-1,-1,-1,8,-1,-1,-1,-1};
                kernelData = Data;
            }

            else if(kernel == 4)
            {
                float Data[] = {0,-1,0,-1,5,-1,0,-1,0};
                kernelData = Data;
            }

            cv::Size arraySize(3,3);
            cv::Mat kernel=cv::Mat(arraySize, CV_32F, kernelData);
            cv::Point anchor(anchorX,anchorY);

            cv::filter2D(loadedImage,filter2dImage,-1,kernel,anchor,delta);
            statusLabel->setText("Anchor(x,y) = "+ QString::number(anchor.x)+","+QString::number(anchor.y)+","+"Delta = "+QString::number(delta));
        }

        else if(index == 1)
        {
            cv::Mat tempthImage;
            loadedImage.copyTo(tempthImage);

            if(tempthImage.channels()>1)
                cv::cvtColor(tempthImage, tempthImage, CV_BGR2GRAY);

            cv::threshold(tempthImage, filter2dImage,deltaMin,deltaMax,threshType | cv::THRESH_OTSU);
            statusLabel->setText("Thresh min:"+QString::number(deltaMin)+",Thresh max:"+QString::number(deltaMin));
        }

        else if(index == 2)
        {
            cv::Mat tempthImage;
            loadedImage.copyTo(tempthImage);

            if(tempthImage.channels()>1)
                cv::cvtColor(tempthImage, tempthImage, CV_BGR2GRAY);

            if(threshType != 0 && threshType != 1)
                threshType = 0;

            cv::adaptiveThreshold(tempthImage,filter2dImage, deltaMax, adaptiveType, threshType, size, 1);
            statusLabel->setText("Delta Max:"+QString::number(deltaMax)+",Size:"+QString::number(size));
        }

        SetLoadedImageInfo(filter2dImage);

        cv::Mat temp;

        if(filter2dImage.channels()>1)
            cv::cvtColor(filter2dImage, temp, CV_BGR2RGB);
        else
            cv::cvtColor(filter2dImage, temp, CV_GRAY2RGB);

        QImageLoaded = new QImage(temp.data,temp.cols,temp.rows, temp.step,QImage::Format_RGB888);

        poProcess->PutImageIntoLabel(*QImageLoaded, processImageLabel);

        qDebug()<<"Filter2D: Success";

        return true;

    }

    qDebug()<<"Filter2D: Exception: Image data is empty";
    QMessageBox::information(mw,"Resim Yükleme Hatası","Filtreleme işlemini gerçekleştirmek için lütfen resim seçin.");
    return false;
}

bool Opencv_::EdgeDetection(int index, bool dxS, bool dyS, int ksize, double scale, double delta,int thressMin, int thressMax)
{
    if(loadedImage.data)
    {

        if(index == 0) //SOBEL
        {
            int dx = 0, dy = 0;

            if(dxS)
                dx=1;
            else if(!dxS)
                dx = 0;
            if(dyS)
                dy = 1;
            else if(!dyS)
                dy = 0;

            cv::Sobel(loadedImage, afterProcessImage,-1,dx,dy,ksize,scale,delta);
            qDebug()<<"Sobel success";
            statusLabel->setText("dx:"+QString::number(dx)+",dy:"+QString::number(dy)+",Size:"+QString::number(ksize));

        }

        else if(index == 1) //LAPLACIAN
        {
            cv::Laplacian(loadedImage,afterProcessImage,-1,ksize,scale,delta);
            qDebug()<<"Laptacian Success";
            statusLabel->setText("Ksize:"+QString::number(ksize)+",Scale:"+QString::number(scale));
        }

        else if(index == 2) //SCHARR
        {
            int dx = 0, dy = 0;

            if(dxS)
                dx=1;
            else if(!dxS)
                dx = 0;
            if(dyS)
                dy = 1;
            else if(!dyS)
                dy = 0;

            cv::Scharr(loadedImage,afterProcessImage,-1,dx,dy,scale,delta);
            qDebug()<<"Scharr success";
            statusLabel->setText("dx:"+QString::number(dx)+",dy:"+QString::number(dy)+",Scale:"+QString::number(scale));
        }

        else if(index == 3) // CANNY
        {
            cv::Mat temp;
            loadedImage.copyTo(temp);
            cv::cvtColor(temp,temp,CV_BGR2GRAY);
            cv::Canny(temp,afterProcessImage,thressMin,thressMax,3,false);
            statusLabel->setText("Thresh min:"+QString::number(thressMin)+",Thresh max:"+QString::number(thressMax));
        }


        cv::Mat iafterProcessImage;

        afterProcessImage.copyTo(iafterProcessImage);

        SetLoadedImageInfo(iafterProcessImage);

        if(iafterProcessImage.channels()>1)
            cv::cvtColor(iafterProcessImage, iafterProcessImage, CV_BGR2RGB);
        else
            cv::cvtColor(iafterProcessImage, iafterProcessImage, CV_GRAY2RGB);

        QImageLoaded = new QImage(iafterProcessImage.data,iafterProcessImage.cols,iafterProcessImage.rows,iafterProcessImage.step,QImage::Format_RGB888);

        poProcess->PutImageIntoLabel(*QImageLoaded, processImageLabel);

        return true;
    }

    qDebug()<<"Function: EdgeDetection Exception: Image data is empty !";

    return false;
}

bool Opencv_::Blur(int index, int kSizeX, int kSizeY, int ancX, int ancY, int sigmaX, int sigmaY, int k_size, int sigmaColor, int sigmaSpace)
{
    if(loadedImage.data)
    {
        loadedImage.copyTo(TemploadedImage);

        if(loadedImage.channels()==1)
            cv::cvtColor(TemploadedImage,TemploadedImage, CV_GRAY2BGR);

        if(index == 0)
        {
            cv::blur(TemploadedImage, bluredImage, cv::Size(kSizeX,kSizeY) , cv::Point(ancX,ancY));
            statusLabel->setText("SizeX:"+QString::number(kSizeX)+",SizeY:"+QString::number(kSizeY));
        }

        else if(index == 1)
        {
            cv::GaussianBlur(TemploadedImage, bluredImage, cv::Size(kSizeX, kSizeY),sigmaX, sigmaY);
            statusLabel->setText("SizeX:"+QString::number(kSizeX)+",SizeY:"+QString::number(kSizeY)+",Sigma(x,y):"+QString::number(sigmaX)+","+QString::number(sigmaY));
        }

        else if(index == 2)
        {
            cv::medianBlur(TemploadedImage, bluredImage, k_size);
            statusLabel->setText("Size:"+QString::number(k_size));
        }

        else if(index == 3)
        {
            cv::boxFilter(TemploadedImage, bluredImage, -1, cv::Size(kSizeX, kSizeY),cv::Point(ancX,ancY));
            statusLabel->setText("SizeX:"+QString::number(kSizeX)+",SizeY:"+QString::number(kSizeY));
        }

        else if(index == 4)
        {
            cv::bilateralFilter(TemploadedImage, bluredImage, k_size, sigmaColor, sigmaSpace);
            statusLabel->setText("Size:"+QString::number(k_size)+",SigmaCol:"+QString::number(sigmaColor)+",SigmaSpa:"+QString::number(sigmaSpace));
        }

        cv::Mat ibluredImage;
        bluredImage.copyTo(ibluredImage);

        SetLoadedImageInfo(ibluredImage);

        cv::cvtColor(ibluredImage, ibluredImage, CV_BGR2RGB);

        QImageLoaded = new QImage(ibluredImage.data,ibluredImage.cols,ibluredImage.rows,ibluredImage.step,QImage::Format_RGB888);

        poProcess->PutImageIntoLabel(*QImageLoaded, processImageLabel);

        qDebug()<<"Function Blur: Success";

        return true;
    }

    qDebug()<<"Funciton Blur: Image data is empty !";
    return false;
}

bool Opencv_::Morphology(int index, int shape, int sizeX, int sizeY, int ancX, int ancY, int time)
{
    if(loadedImage.data)
    {
        cv::Mat kernel = cv::getStructuringElement(shape,cv::Size(sizeX, sizeY), cv::Point(ancX,ancY));

        cv::morphologyEx(loadedImage, morphologyImage, index, kernel, cv::Point(-1,-1),time);

        statusLabel->setText("SizeX:"+QString::number(sizeX)+",SizeY:"+QString::number(sizeY)+", Time:"+QString::number(time));

        cv::Mat imorphologyImage;

        morphologyImage.copyTo(imorphologyImage);

        SetLoadedImageInfo(imorphologyImage);

        if(imorphologyImage.channels()>1)
            cv::cvtColor(imorphologyImage, imorphologyImage, CV_BGR2RGB);
        else
            cv::cvtColor(imorphologyImage, imorphologyImage, CV_GRAY2RGB);

        QImageLoaded = new QImage(imorphologyImage.data, imorphologyImage.cols, imorphologyImage.rows, imorphologyImage.step,QImage::Format_RGB888);

        poProcess->PutImageIntoLabel(*QImageLoaded, processImageLabel);

        return true;
    }

    qDebug()<<"Function Morphology Excepiton: Loaded image is empty !";

    return false;
}

void Opencv_::SetLoadedImageInfo()
{
    if(loadedImage.data)
    {
        lbx->setText(QString::number(loadedImage.cols));
        lby->setText(QString::number(loadedImage.rows));
        lbch->setText(QString::number(loadedImage.channels()));
        if(loadedImage.channels() > 1)
        lbinc->setText("RGB");
        else
            lbinc->setText("GRAY");
        qDebug()<<"SetImageInfo Success";
        return;
    }

    qDebug()<<"SetImageInfo Excepiton: Loaded image is empty !";

    return;
}

void Opencv_::SetLoadedImageInfo(cv::Mat image)
{
    if(image.data)
    {
        lbx1->setText(QString::number(image.cols));
        lby1->setText(QString::number(image.rows));
        lbch1->setText(QString::number(image.channels()));
        if(image.channels() > 1)
        lbinc1->setText("RGB");
        else
            lbinc1->setText("GRAY");
        qDebug()<<"SetImageInfo Success";
        return;
    }

    qDebug()<<"SetImageInfo 1/ Excepiton: Loaded image is empty !";

    return;
}

bool Opencv_::GetLoadedQImage(QImage &image)
{
    if(loadedImage.data)
    {

        cv::Mat temp;
        loadedImage.copyTo(temp);
        if(temp.channels()>1)
            cv::cvtColor(temp,temp,CV_BGR2RGB);
        else
            cv::cvtColor(temp,temp,CV_GRAY2RGB);

        QImage *imageTemp = new QImage(temp.data, temp.cols, temp.rows, temp.step,QImage::Format_RGB888);

        image = *imageTemp;

        return true;
    }

    QMessageBox::information(mw,"Yazdırma Hatası","Yazdırma işlemini gerçekleştirebilmek için resim seçilmiş olmalıdır !");

    return false;
}

void Opencv_::ColorFilter(QLabel *imageLabel, int hmin, int smin, int vmin, int hm, int sm, int vm)
{
    if(loadedImage.data)
    {
        if(loadedImage.channels()>1)
        {
            loadedImage.copyTo(colorFilteredImage);
            cv::Mat hsvImage;
            cv::Mat grayScale;
            cv::Mat rgbImage;
            cv::Mat rgbImage2;

            cv::cvtColor(loadedImage, hsvImage, CV_BGR2HSV);
            cv::inRange(hsvImage, cv::Scalar(hmin,smin,vmin),cv::Scalar(hm,sm,vm),grayScale);
            cv::cvtColor(grayScale, grayScale, CV_GRAY2BGR);
            cv::cvtColor(grayScale, rgbImage, CV_BGR2RGB);
            QImage *qimage = new QImage(rgbImage.data,rgbImage.cols, rgbImage.rows,rgbImage.step,QImage::Format_RGB888);
            imageLabel->setPixmap(QPixmap::fromImage(*qimage).scaled(imageLabel->size(),Qt::KeepAspectRatio));
            colorFilteredImage = colorFilteredImage & grayScale;
            cv::cvtColor(colorFilteredImage, rgbImage2, CV_BGR2RGB);
            QImage *q2image = new QImage(rgbImage2.data,rgbImage2.cols, rgbImage2.rows,rgbImage2.step,QImage::Format_RGB888);
            poProcess->PutImageIntoLabel(*q2image, processImageLabel);
            SetLoadedImageInfo(hsvImage);
            statusLabel->setText("(min,max)|H:"+QString::number(hmin)+","+QString::number(hm)+",S:"+QString::number(smin)+","+QString::number(sm)+",V:"+QString::number(vmin)+","+QString::number(vm));
        }

        else
        {
            QMessageBox::information(mw,"Renk Uzayı Hatası","Tek kanallı(siyah-beyaz) görüntüler üzerinde renk filtreleme işlemi yapılamaz.");
        }

        return;
    }

    QMessageBox::information(mw,"Resim Seçilmemiş","Bu işlemi yapabilmeniz için resim seçmiş olmanız gerekmektedir.");

    return;
}

void Opencv_::ColorizeImageMethodNormal()
{
   if(!loadedImage.empty())
   {
        if(OriginalColoredImage.channels()>1)
        {
            if(loadedImage.channels()==1)
                cv::cvtColor(loadedImage,loadedImage, CV_GRAY2BGR);
            tempImColoredAndOlded = loadedImage & OriginalColoredImage;
            cv::cvtColor(tempImColoredAndOlded, tempImColoredAndOlded, CV_BGR2RGB);
            QImage *qim = new QImage(tempImColoredAndOlded.data, tempImColoredAndOlded.cols,tempImColoredAndOlded.rows,tempImColoredAndOlded.step,QImage::Format_RGB888);
            resimonizle = new ResimOnizle(1,mw,qim,mw);
            cv::cvtColor(tempImColoredAndOlded, tempImColoredAndOlded, CV_RGB2BGR);
            resimonizle->show();
            return;
        }

        QMessageBox::information(mw,"Resmi Renklendir NORMAL","Bu işlemi yapabilmeniz seçilen resim renkli olmalıdır.");
        return;
   }

   QMessageBox::information(mw,"Resmi Renklendir NORMAL","Bu işlemi yapabilmeniz için resim seçmiş olmanız gerekmektedir.");
   return;
}

void Opencv_::ApplyColorizedImage()
{
    if(!tempImColoredAndOlded.empty() && tempImColoredAndOlded.data)
    {
        tempImColoredAndOlded.copyTo(loadedImage);

        QImage *q2image = new QImage(tempImColoredAndOlded.data, tempImColoredAndOlded.cols, tempImColoredAndOlded.rows,tempImColoredAndOlded.step,QImage::Format_RGB888);
        poLoaded->PutImageIntoLabel(*q2image, mainImageLabel);
        qDebug()<<"ApplyColorizedImage: Success";
        return;
    }

    QMessageBox::information(mw,"NORMAL FUNCAPPLYCOLORIZED","Hay aksi, bilinmeyen bir hata oluştu.");
    return;
}

bool Opencv_::findContours(QLCDNumber *countLabel, int mod, int method, int b, int g, int r, int thickness,
                  bool isNumbered, bool isColored)
{
   if(loadedImage.empty())
   {
       QMessageBox::information(mw,"Resim seçilmemiş !","Hay aksi ! Bu işlemi gerçekleştirilebilmeniz için resim seçmiş olmanız gerekir.");
       qDebug()<<"findContours: Loaded image is empty !";
       return false;
   }

   if(loadedImage.channels()>1)
       cv::cvtColor(loadedImage, grayImage, CV_BGR2GRAY);
   else if(loadedImage.channels()== 1)
       loadedImage.copyTo(grayImage);
   else
   {
       QMessageBox::information(mw,"Resim Biçimi Hatası !","Hay aksi ! Yüklenen resmin kanal sayısı uyumsuz.");
       return false;
   }

   originalImage.copyTo(tempdrawcontoursImage);

   std::vector<std::vector<cv::Point> > contours;
   std::vector<cv::Vec4i> hieararchy;

   cv::findContours(grayImage, contours, hieararchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

   cv::RotatedRect rect;

   cv::cvtColor(grayImage,grayImage, CV_GRAY2BGR);

   for(int i = 0; i < contours.size(); i++)
   {
       cv::drawContours(grayImage,contours,i,cv::Scalar(b,g,r),thickness,8, hieararchy);
       rect = cv::minAreaRect(contours[i]);
       if(isColored)
       {
           cv::drawContours(tempdrawcontoursImage,contours,i,cv::Scalar(b,g,r),thickness,8, hieararchy);
       }

       if(isNumbered)
       {
           cv::putText(grayImage, std::to_string(i+1),rect.center,CV_FONT_NORMAL, 1.5, cv::Scalar(b,g,r),2);

           if(isColored)
           {
              cv::putText(tempdrawcontoursImage, std::to_string(i+1),rect.center,CV_FONT_NORMAL, 1.5, cv::Scalar(b,g,r),2);
           }
       }
   }

   cv::cvtColor(grayImage,grayImage,CV_BGR2RGB);

   QImage *q2image = new QImage(grayImage.data, grayImage.cols, grayImage.rows,grayImage.step,QImage::Format_RGB888);

   poProcess->PutImageIntoLabel(*q2image, processImageLabel);

   countLabel->display((int)contours.size());

   if(isColored)
   {
        cv::cvtColor(tempdrawcontoursImage,tempdrawcontoursImage,CV_BGR2RGB);
        QImage *q22image = new QImage(tempdrawcontoursImage.data, tempdrawcontoursImage.cols, tempdrawcontoursImage.rows,tempdrawcontoursImage.step,QImage::Format_RGB888);
        resimonizle = new ResimOnizle(0,mw, q22image, mw);
        resimonizle->show();
   }

   qDebug()<<"findContours: Success";

   return true;
}

void Opencv_::TakeBackEverything()
{
    if(!originalImage.empty() && originalImage.data)
    {
        cv::Mat tempLoaded;

        originalImage.copyTo(loadedImage);

        if(loadedImage.channels() > 1)
        {
            loadedImage.copyTo(OriginalColoredImage);
            cv::cvtColor(loadedImage, tempLoaded,CV_BGR2RGB);
            QImageLoaded = new QImage(tempLoaded.data,tempLoaded.cols,tempLoaded.rows,tempLoaded.step,QImage::Format_RGB888);
        }

        else if(loadedImage.channels() == 1)
        {
            cv::cvtColor(loadedImage, tempLoaded,CV_GRAY2RGB);
            QImageLoaded = new QImage(tempLoaded.data,tempLoaded.cols,tempLoaded.rows,tempLoaded.step,QImage::Format_RGB888);
        }

        poLoaded->PutImageIntoLabel(*QImageLoaded, mainImageLabel);
        SetLoadedImageInfo();
        qDebug() << "LoadImage: Succes";

        return;
    }
}













