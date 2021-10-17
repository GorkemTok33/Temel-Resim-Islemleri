/****************************************************************************************
Program: PictureDesigner
Author: Görkem Tok
Language: C++
Platform: Qt Creator
Contact: ceng.gorkem.tok@gmail.com
License: MIT
****************************************************************************************/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QPainter>
#include <QMainWindow>
#include "aboutprogram.h"
#include <QList>
#include "applypast.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void ApplyImageFromFindContours();
    void ApplyColorizedAndLoadedImage();
    ~MainWindow();

private slots:
    void on_actionA_triggered();

    void on_pushButton_clicked();

    void on_lineEditFilterX_textChanged(const QString &arg1);

    void on_lineEditFilterY_textChanged(const QString &arg1);

    void on_lineEditFilterDelta_textChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_cbEdge_currentIndexChanged(int index);

    void on_sliderThressMin_sliderMoved(int position);

    void on_sliderScale_sliderMoved(int position);

    void on_sliderThressMax_sliderMoved(int position);

    void on_lineEditEdgeFoundDelta_textChanged(const QString &arg1);

    void on_checkBoxXT_clicked();

    void on_checkBoxYT_clicked();

    void on_comboBoxBlurFunctions_currentIndexChanged(int index);

    void on_horizontalSliderBlurScaleX_sliderMoved(int position);

    void on_horizontalSliderBlurScaleY_sliderMoved(int position);

    void on_horizontalSliderBlurSigmaColor_2_sliderMoved(int position);

    void on_horizontalSliderBlurSigmaColor_sliderMoved(int position);

    void on_horizontalSliderBlurSigmaSpace_sliderMoved(int position);

    void on_pushButton_3_clicked();

    void on_lineEditBlurancX_textChanged(const QString &arg1);

    void on_lineEditBlurancY_textChanged(const QString &arg1);

    void on_lineEditBlurSigmaX_textChanged(const QString &arg1);

    void on_lineEditBlurSigmaY_textChanged(const QString &arg1);

    void on_cbFilter2DFunc_currentIndexChanged(int index);

    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_2_sliderMoved(int position);

    void on_horizontalSlider_3_sliderMoved(int position);

    void on_comboBoxMorphoFunc_currentIndexChanged(int index);

    void on_comboBoxMorphoShape_currentIndexChanged(int index);

    void on_pushButton_4_clicked();

    void on_actionProgram_Hakk_nda_triggered();

    void on_sliderFilterSizeK_sliderMoved(int position);

    void on_sliderFilterThressMin_sliderMoved(int position);

    void on_sliderFilterThressMax_3_sliderMoved(int position);

    void on_comboBoxFilter_currentIndexChanged(int index);

    void on_comboBoxThreshType_currentIndexChanged(int index);

    void on_comboBoxAdaptiveType_currentIndexChanged(int index);

    void on_actionFarkl_Kaydet_triggered();

    void on_actionYazd_r_triggered();

    void on_horizontalSliderHMax_sliderMoved(int position);

    void on_horizontalSliderHMin_sliderMoved(int position);

    void on_horizontalSliderSatMax_sliderMoved(int position);

    void on_horizontalSliderSatMin_sliderMoved(int position);

    void on_horizontalSliderValMax_sliderMoved(int position);

    void on_horizontalSliderValMin_sliderMoved(int position);

    void on_pushButton_6_clicked();

    void on_action_lem_Ge_mi_i_triggered();

    void on_sliderFilterSizeK_actionTriggered(int action);

    void on_actionResmi_Renklendir_triggered();

    void on_comboBox_2_currentIndexChanged(int index);

    void on_comboBoxFindConMod_currentIndexChanged(int index);

    void on_comboBoxFindConMethod_currentIndexChanged(int index);

    void on_lineEditcolorB_textChanged(const QString &arg1);

    void on_lineEditcolorG_textChanged(const QString &arg1);

    void on_lineEditcolorR_textChanged(const QString &arg1);

    void on_checkBoxfindConsNum_clicked();

    void on_checkBoxFindConLoaded_clicked();

    void on_comboBoxThickness_currentIndexChanged(int index);

    void on_pushButton_5_clicked();

    void on_actionYap_lan_lemleri_Geri_Al_triggered();

private:
    Ui::MainWindow *ui;
    aboutProgram *aboutMe;
    Applypast *apllypast;
    int size = 0;
    int scale = 0;
    int indexCb = 0;
    int thressMin = 0;
    int thressMax = 0;
    int sizeX = 1;
    int sizeY = 1;
    int currentFunctionIndexcb = 0;
    int hmin = 0;
    int hmax = 0;
    int smin = 0;
    int smax = 0;
    int vmin = 0;
    int vmax = 0;
    void ApplyEdgeFound();
    void ApplyBlur();
    void AllFalseBlur();
    void ApplyFilter2D();
    void ApplyFilter2D(int currentIndex);
    void ApplyMorphology();
    void ApplyColorFilter();
    void ApplyfindContours();
    QList<QString> ApplyPast;
};
#endif // MAINWINDOW_H
