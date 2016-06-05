#ifndef CONTOURSDISPLAYER_H
#define CONTOURSDISPLAYER_H

#include <opencv2/opencv.hpp>
#include <QWidget>
#include <vector>

namespace Ui {
class ContoursDisplayer;
}

class ContoursDisplayer : public QWidget
{
    Q_OBJECT

public:
    explicit ContoursDisplayer(QWidget *parent = 0);
    ~ContoursDisplayer();

    void setBinaryImage(const cv::Mat& bw);
    void findContours();

private slots:
    void onSliderDragged(int);
    void on_pushButton_clicked();

private:
    Ui::ContoursDisplayer *ui;

    cv::Mat bwImg;
    cv::Mat drawing;

    int lineWidth{1};

    void showImage(const cv::Mat& mat);

    float valAreaHigh;
    float valAreaLow;
    float maxArea;
    float minArea;
    float valLengthHigh;
    float valLengthLow;
    float maxLength;
    float minLength;
    float valALLow;
    float valALHigh;
    float maxAL;
    float minAL;
    int valContourSize;

    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i > hierarchy;
    std::vector<float> areaVec;
    std::vector<float> lengthVec;

    void update_drawing();
    void update_gui();
};

#endif // CONTOURSDISPLAYER_H
