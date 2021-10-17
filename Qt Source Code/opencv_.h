/****************************************************************************************
Program: PictureDesigner
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/


#ifndef OPENCV__H
#define OPENCV__H

#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgcodecs.hpp"
#include "fileoperations.h"
#include "pictureoperations.h"
#include <QString>
#include "mainwindow.h"
#include <QLabel>
#include <QLCDNumber>
#include <QImage>
#include <QtMath>
#include "resimonizle.h"

class Opencv_
{

public:
    Opencv_(MainWindow *mw, QLabel *mainLabel, QLabel *processLabel, QLabel *lbx, QLabel *lby, QLabel *lbinch, QLabel *lbch,
            QLabel *lbx1, QLabel *lby1, QLabel *lbinch1, QLabel *lbch1, QLabel *statusLabel);
    void LoadImage(QString filePath);
    void SaveImage();
    void OpenImage();
    void BluredApply();
    void EdgeApply();
    void Filter2DApply();
    void ApplyMorphology();
    void ApplyColorFilter();
    void ColorFilter(QLabel *imageLabel, int hmin = 0, int smin = 0, int vmin = 0, int hm = 0, int sm = 0, int vm = 0);
    void ColorizeImageMethodNormal();
    void findContoursApply(bool t = false);
    void TakeBackEverything();
    void ApplyColorizedImage();
    bool GetLoadedQImage(QImage &image);
    bool Filter2D(int index = 0, int kernel = 1, int anchorX = -1, int anchorY = -1, double delta = 0,int adaptiveType = 0, int threshType = 0, int deltaMin = 0, int deltaMax = 0, int size = 3);
    bool EdgeDetection(int index = 0, bool dxS = true, bool dyS = true, int ksize = 3, double scale = 1, double delta = 0, int thressMin = 0, int thressMax = 0);
    bool Blur(int index = 0, int kSizeX = 1, int kSizeY = 1, int ancX = -1, int ancY = -1, int sigmaX = 2, int sigmaY = 2, int k_size = 1,int sigmaColor = 0, int sigmaSpace = 0);
    bool Morphology(int index = 0, int shape = 0, int sizeX = 1, int sizeY =  1, int ancX =  1, int ancY =  1, int time = 1);
    bool findContours(QLCDNumber *countLabel, int mod = 0, int method = 0, int b = 0, int g = 255, int r = 0, int thickness = 1, bool isNumbered = false, bool isColored = false);

private:
    QString filePath;
    MainWindow *mw;
    QLabel *mainImageLabel;
    QLabel *processImageLabel;
    QLabel *lbx;
    QLabel *lbx1;
    QLabel *lby;
    QLabel *lby1;
    QLabel *lbinc;
    QLabel *lbinc1;
    QLabel *lbch;
    QLabel *lbch1;
    QLabel *statusLabel;
    QImage *QImageLoaded;
    QImage *QImageProcess;
    FileOperations *fileOperations;
    PictureOperations *poLoaded;
    PictureOperations *poProcess;
    cv::Mat loadedImage;
    cv::Mat filter2dImage;
    cv::Mat bluredImage;
    cv::Mat afterProcessImage;
    cv::Mat TemploadedImage;
    cv::Mat morphologyImage;
    cv::Mat colorFilteredImage;
    cv::Mat OriginalColoredImage;
    cv::Mat originalImage;
    cv::Mat grayImage;
    cv::Mat tempdrawcontoursImage;
    cv::Mat tempImColoredAndOlded;
    ResimOnizle *resimonizle;
    void SetLoadedImageInfo();
    void SetLoadedImageInfo(cv::Mat image);
};

#endif // OPENCV__H
