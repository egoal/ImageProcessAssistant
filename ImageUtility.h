#pragma once

#include <QImage>
#include <opencv2/opencv.hpp>

//way to convert QImage and cv::Mat
extern cv::Mat fromQImage2Mat(const QImage& img);
extern QImage fromMat2QImage(const cv::Mat& mat);

//simple vector function
//assist for distance
extern float crossProduct2D(const cv::Point2f& p1, const cv::Point2f& p2);
extern float length2D(const cv::Point2f& p);

//display cv::Mat for by cv::imshow for debug
// void IMSHOW(const std::string& winName,const cv::Mat&  mat);
