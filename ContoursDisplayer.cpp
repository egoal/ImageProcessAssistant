#include "ContoursDisplayer.h"
#include "ui_ContoursDisplayer.h"
#include "ImageUtility.h"
#include <fstream>
#include "MacroData.h"
#include <ctime>
#include <QMessageBox>

using namespace cv;
using namespace std;

ContoursDisplayer::ContoursDisplayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContoursDisplayer)
{
    ui->setupUi(this);

    connect(ui->AreaHigh, SIGNAL(valueChanged(int)),this,SLOT(onSliderDragged(int)));
    connect(ui->AreaLow, SIGNAL(valueChanged(int)),this,SLOT(onSliderDragged(int)));
    connect(ui->LengthHigh, SIGNAL(valueChanged(int)),this,SLOT(onSliderDragged(int)));
    connect(ui->LengthLow, SIGNAL(valueChanged(int)),this,SLOT(onSliderDragged(int)));
    connect(ui->sliderLineWidth,SIGNAL(valueChanged(int)),this, SLOT(onSliderDragged(int)));
    connect(ui->ALHigh,SIGNAL(valueChanged(int)),this,SLOT(onSliderDragged(int)));
    connect(ui->ALLow,SIGNAL(valueChanged(int)),this,SLOT(onSliderDragged(int)));
}

ContoursDisplayer::~ContoursDisplayer()
{
    delete ui;
}

void ContoursDisplayer::setBinaryImage(const cv::Mat& bw){
    bwImg   =   bw.clone();

    areaVec.clear();
    lengthVec.clear();
    ui->AreaHigh->setValue(100);
    ui->AreaLow->setValue(0);
    ui->LengthHigh->setValue(100);
    ui->LengthLow->setValue(0);
    ui->sliderLineWidth->setValue(2);
}

void ContoursDisplayer::findContours(){
    if(!bwImg.data)
        return;


    cv::findContours(bwImg,contours,hierarchy,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE);

    valContourSize  =   contours.size();
    maxLength   =   maxArea =   maxAL   =   numeric_limits<float>::min();
    minLength   =   minArea =   minAL   =   numeric_limits<float>::max();
    for(int i=0;i<contours.size();++i){
        float area	=	contourArea(contours[i]);
        float length	=	arcLength(contours[i],true);
        float al    =   area/length;

        areaVec.push_back(area);
        lengthVec.push_back(length);

        if(area>maxArea)
            maxArea =   area;
        else if(area<minArea)
            minArea =   area;

        if(length>maxLength)
            maxLength   =   length;
        else if(length<minLength)
            minLength   =   length;

        if(al>maxAL)
            maxAL   =   al;
        else if(al<minAL)
            minAL   =   al;
    }

    ui->AreaRange->setText(QString("%1 - %2").arg(minArea).arg(maxArea));
    ui->LengthRange->setText(QString("%1 - %2").arg(minLength).arg(maxLength));
    ui->ALRange->setText(QString("%1 - %2").arg(minAL).arg(maxAL));

    onSliderDragged(0);

    update_drawing();
    update_gui();
}

void ContoursDisplayer::showImage(const Mat &mat){
    QImage img  =   fromMat2QImage(mat);
    ui->lblImg->setPixmap(QPixmap::fromImage(img));
}

void ContoursDisplayer::update_drawing(){
    drawing   =   Mat(bwImg.rows, bwImg.cols, CV_8UC3, Scalar::all(255));
    valContourSize  =   0;
    for(int i=0;i<contours.size();++i){
        Scalar color    =   Scalar(0,0,0);
        if(areaVec[i]<valAreaHigh && areaVec[i]>valAreaLow
                && lengthVec[i]<valLengthHigh && lengthVec[i]>valLengthLow
                && areaVec[i]/lengthVec[i] > valALLow && areaVec[i]/lengthVec[i]< valALHigh){
            color   =   Scalar(0,0,255);
            ++valContourSize;
        }

        drawContours(drawing, contours, i, color, lineWidth);
    }

    cv::resize(drawing,drawing,cv::Size(ui->lblImg->width(), ui->lblImg->height()));

    showImage(drawing);
}

void ContoursDisplayer::update_gui(){
    ui->editContourCount->setText(QString("%1").arg(valContourSize));

    ui->editAreaHigh->setText(QString("%1").arg(valAreaHigh));
    ui->editAreaLow->setText(QString("%1").arg(valAreaLow));
    ui->editLengthHigh->setText(QString("%1").arg(valLengthHigh));
    ui->editLengthLow->setText(QString("%1").arg(valLengthLow));
    ui->editALHigh->setText(QString("%1").arg(valALHigh));
    ui->editALLow->setText(QString("%1").arg(valALLow));
}

void ContoursDisplayer::onSliderDragged(int){
    lineWidth   =   ui->sliderLineWidth->value();
    valAreaHigh =   ui->AreaHigh->value()/100.0f*maxArea;
    valAreaLow  =   ui->AreaLow->value()/100.0f*maxArea;
    valLengthHigh   =   ui->LengthHigh->value()/100.0f*maxLength;
    valLengthLow    =   ui->LengthLow->value()/100.0f*maxLength;
    valALHigh   =   ui->ALHigh->value()/100.0f*maxAL;
    valALLow    =   ui->ALLow->value()/100.0f*maxAL;

    update_drawing();
    update_gui();
}

void ContoursDisplayer::on_pushButton_clicked()
{
    time_t t    =   time(nullptr);
    tm* timeinfo    =   localtime(&t);

    ofstream fout(GD::getInstance()->contourResultFile,ios::out|ios::app);
    fout<<"======"
       <<"\nData: "<<asctime(timeinfo)
       <<"\nFile: "<<GD::getInstance()->currentFileName
       <<"\nArea: "<<valAreaLow<<" - "<<valAreaHigh
      <<"\nLength: "<<valLengthLow<<" - "<<valLengthHigh
     <<"\nArea/Length: "<<valALLow<<" - "<<valALHigh
     <<"\nContours: "<<valContourSize<<endl;
    fout.close();

    QString info    =   tr("Result saved!\n  at: ")+QString::fromStdString(GD::getInstance()->contourResultFile);
    QMessageBox::information(this, tr("Tips"),info);
}
