#pragma once
// 20151226
// 一些常用的opencv小函数，也许造了不少轮子

#include <opencv2/opencv.hpp>
#include <cmath>
#include <string>
#include <memory>

// calc average gray scale in the box
extern float f_mean(const cv::Mat& mat,const cv::Rect& r);

template<typename T=cv::Point>
inline float f_length2d(const T& p){
	return std::sqrt(p.x*p.x+p.y*p.y);
}

template<typename T=cv::Point>
inline float f_length2(const T& p){
	return p.x*p.x+p.y*p.y;
}

// 201601
// 中位数
template <typename T>
T getMedian(T* ptr,std::size_t size,bool replace = true){
	T* cache	=	nullptr;
	if(!replace){
		cache	=	new T[size];
		std::memcpy(cache,ptr,size*sizeof(T));
	}
	else
		cache	=	ptr;

	std::sort(cache,cache+size);
	int pos	=	size%2==0?size/2:(size+1)/2;

	T re	=	cache[pos];
	if(!replace)
		delete[] cache;

	return re;
}

// 中位数计算平均
extern void f_calcMedianMat(cv::Mat* pics, int npics, cv::Mat& bg);

// 统一某一区域的值
extern void f_setMatRectVal(cv::Mat& mat,const cv::Rect& region,uchar val);
	// 20160511 use Mat::setTo instead

inline cv::Rect f_scaledRect(const cv::Rect& rect, float x, float y){
	return cv::Rect(rect.x-rect.width*(x-1)/2,rect.y-rect.height*(y-1)/2,rect.width*x,rect.height*y);
}
inline cv::Rect f_boundedRect(const cv::Rect& rect,int wx,int wy){
	return cv::Rect(rect.x-wx,rect.y-wy,rect.width+2*wx,rect.height+2*wy);
}

// 通过滑块调整通道阈值(H)
extern void f_adjustChannelThreshold(const cv::Mat& src, int* val);

// 201602
// 3次B样条曲线拟合
extern void f_bsp3(cv::Point* points, float* a, float* b);

// 201603
// 获得图到本地
extern void f_grabFrame(int camid = 0, const std::string& folder = "");

// 获取处理过的图片，f_grabFrame的改版
extern void f_grabProcessedFrame(int camid,const std::string& folder,void(*func)(cv::Mat& mat));

// 201605
#define IMSHOW(m) imshow(#m, m)
static cv::Mat cache;
#define IM_SHOW(m) \
	cv::resize(m,cache,Size(480*m.cols/m.rows,480)); imshow(#m,cache)

// calculate distance form point: pos to line: p1->p2
inline float f_disPoint2Line(const cv::Point2f& pos,const cv::Point2f& p1,const cv::Point2f& p2){
	cv::Point2f vPos	=	pos-p1;
	cv::Point2f vDir	=	p2-p1;

	return fabs(vPos.x*vDir.y-vDir.x*vPos.y)/f_length2d<cv::Point2f>(vDir);
}

extern void f_drawRay(cv::Mat& drawing,const cv::Point2f& p1,const cv::Point2f& p2,cv::Scalar color,int width=1);

// convert input mat to uchar mat(for displaying)
extern cv::Mat f_makeUChar(const cv::Mat& fmat);

// simple debug for matlab load
// slow when data size is large
extern bool f_saveTextFile(const cv::Mat& mat, std::string filename);

// 201606
// show data histogram
extern cv::Mat f_bar(float* data,int length,
	cv::Scalar color = cv::Scalar(0,0,0),
	float barWR = 0.8f,
	cv::Size imgSize = cv::Size(640,480),
	cv::Size margin = cv::Size(20,20));