#include "ContoursDisplayer.h"
#include "ui_ContoursDisplayer.h"
#include "ImageUtility.h"

using namespace cv;
using namespace std;

ContoursDisplayer::ContoursDisplayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContoursDisplayer)
{
    ui->setupUi(this);
}

ContoursDisplayer::~ContoursDisplayer()
{
    delete ui;
}

void ContoursDisplayer::findContours(){
    if(!bwImg.data)
        return;

    drawing   =   Mat(bwImg.rows, bwImg.cols, CV_8UC3, Scalar::all(255));
    vector<vector<Point> > contours;
    vector<Vec4i > hierarchy;
    cv::findContours(bwImg,contours,hierarchy,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE);

    for(int i=0;i<contours.size();++i){
        Scalar color    =   Scalar(255,0,0);
        int width   =   1;

        drawContours(drawing, contours, i, color, width);
    }

    showImage(drawing);
}

void ContoursDisplayer::showImage(const Mat &mat){
    QImage img  =   fromMat2QImage(mat);
    ui->lblImg->setPixmap(QPixmap::fromImage(img));
}
