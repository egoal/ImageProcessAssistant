#ifndef CONTOURSDISPLAYER_H
#define CONTOURSDISPLAYER_H

#include <opencv2/opencv.hpp>
#include <QWidget>

namespace Ui {
class ContoursDisplayer;
}

class ContoursDisplayer : public QWidget
{
    Q_OBJECT

public:
    explicit ContoursDisplayer(QWidget *parent = 0);
    ~ContoursDisplayer();

    void setBinaryImage(const cv::Mat& bw){
        bwImg   =   bw.clone();
    }
    void findContours();

private:
    Ui::ContoursDisplayer *ui;

    cv::Mat bwImg;
    cv::Mat drawing;

    void showImage(const cv::Mat& mat);
};

#endif // CONTOURSDISPLAYER_H
