#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "MacroData.h"
#include <QtWidgets>
#include "ImageUtility.h"
#include <iostream>
#include "SliderInput.h"
#include <vector>
#include "opencv_func.hpp"
#include "ContoursDisplayer.h"

using namespace cv;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    checkMenuWithCurrentImage();
}

MainWindow::~MainWindow()
{
    delete ui;
    if(contoursDisplayer)
        delete contoursDisplayer;
}

void MainWindow::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    if(showImage && !qimgShow.isNull()){
        QRect r  =   qimgShow.rect();
        r.moveCenter(QPoint(width()/2, height()/2+10));
        painter.drawImage(r,qimgShow);
    }
}

void MainWindow::resizeEvent(QResizeEvent *e){
    displayImage(currentImg);
}

void MainWindow::on_actionOpen_triggered()
{
    QString openFile    =   QFileDialog::getOpenFileName(this,tr("Select a image file"),
                                QString::fromStdString(GD::getInstance()->lastOpenFolder),
                                tr("Images (*.png *.jpg *.bmp)") );
    if(openFile.isEmpty())
        return;
    auto fileInfo   =   QFileInfo(openFile);
    GD::getInstance()->lastOpenFolder   =   fileInfo.absolutePath().toStdString();
    GD::getInstance()->updateToFile();

    imgFileName =   openFile.toStdString();
    srcImg  =   imread(imgFileName);
    if(!srcImg.data){
        QMessageBox::warning(this,tr("warnning"),tr("cannot open file %1").arg(openFile));
        return;
    }

    currentImg  =   srcImg.clone();
    displayImage(currentImg);

    checkMenuWithCurrentImage();
}

void MainWindow::on_actionSave_triggered()
{
    if(!currentImg.data)
        return;

    QString filename    =   QFileDialog::getSaveFileName(this, tr("Save file"),
                            QString::fromStdString(GD::getInstance()->lastSaveFolder),
                            tr("Images (*.png *.jpg *.bmp)"));
    if(filename.isEmpty())
        return;
    auto fileinfo   =   QFileInfo(filename);
    GD::getInstance()->lastSaveFolder   =   fileinfo.absolutePath().toStdString();
    GD::getInstance()->updateToFile();

    imwrite(filename.toStdString(), currentImg);

}

void MainWindow::checkMenuWithCurrentImage(){
    if(!currentImg.data){
        ui->menuEdit->setEnabled(false);
        ui->actionSave->setEnabled(false);
        return;
    }

    ui->menuEdit->setEnabled(true);
    ui->actionSave->setEnabled(true);
    switch(currentImg.channels()){
    case 1:
        ui->menuGray->setEnabled(true);
        ui->menuHue->setEnabled(false);
        break;
    case 3:
        ui->menuHue->setEnabled(true);
        ui->menuGray->setEnabled(false);
        break;
    default:
        cout<<"unexcepted channels!"<<endl;
        break;
    }
}

void MainWindow::displayImage(const Mat &img){
    QImage&& qimg    =   fromMat2QImage(img);

    // scale to fit window
    float scale_w   =   this->centralWidget()->width()/(float)qimg.width();
    float scale_h   =   this->centralWidget()->height()/(float)qimg.height();
    scale   =   scale_w<scale_h?scale_w:scale_h;
    qimgShow    =   qimg.scaled(qimg.size()*scale);

    this->repaint();
}

void MainWindow::on_actionFit_triggered()
{
    if(qimgShow.isNull())
        return;
    this->resize(qimgShow.size()+QSize(25,50));
}

// edit
// reset
void MainWindow::on_actionReset_triggered()
{
    currentImg  =   srcImg.clone();
    checkMenuWithCurrentImage();

    displayImage(currentImg);
}

// size
void MainWindow::on_actionSize_triggered()
{

}

// hue
void MainWindow::on_actionMakeGray_triggered()
{
    cvtColor(currentImg, currentImg, CV_BGR2GRAY);
    displayImage(currentImg);

    checkMenuWithCurrentImage();
}

// gray
void MainWindow::on_actionMakeBinary_triggered()
{
    Mat cache;
    int thresh  =   threshold(currentImg,cache, 0, 255, CV_THRESH_OTSU);
    displayImage(cache);
    SliderInput* si =   new SliderInput(&thresh, 0, 255, "threshold");
    connect(si, &SliderInput::value_changed, [&](int t){
        threshold(currentImg, cache, thresh, 255, CV_THRESH_BINARY);
        displayImage(cache);
    });
    int re  =   si->exec();
    if(re==QDialog::Accepted){
        currentImg  =   cache;
    }

    displayImage(currentImg);
}


void MainWindow::on_actionInverse_triggered()
{
    for(int r=0;r<currentImg.rows;++r){
        uchar* pImg =   currentImg.ptr<uchar>(r);
        for(int c=0;c<currentImg.cols;++c){
            pImg[c] =   255-pImg[c];
        }
    }

    displayImage(currentImg);
}

void MainWindow::on_actionFindContours_triggered()
{
    if(!contoursDisplayer)
        contoursDisplayer   =   new ContoursDisplayer();
    contoursDisplayer->setBinaryImage(currentImg);
    contoursDisplayer->findContours();
    contoursDisplayer->show();
}


