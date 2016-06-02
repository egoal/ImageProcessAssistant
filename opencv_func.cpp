#include "opencv_func.hpp"
#include <cmath>
#include <cassert>
#include <fstream>
#include <algorithm>

using namespace std;
using namespace cv;

float f_mean(const Mat& mat,const Rect& r){
	float meanVal	=	0;
	for(int i = 0;i<r.height;++i){
		const uchar* pRow	=	mat.ptr(i+r.y);
		for(int j = 0;j<r.width;++j)
			meanVal	+=	pRow[j+r.x];
	}
	meanVal	=	meanVal/(r.width*r.height);

	return meanVal;
}

void f_calcMedianMat(Mat* pics,int npics,Mat& bg){
	assert(pics[0].channels() == 1 && npics > 0);

	uchar* pl	=	new uchar[npics];
	for(int r=0;r<pics[0].rows;++r){
		for(int c=0;c<pics[0].cols;++c){
			for(int i=0;i<npics;++i){
				pl[i]	=	pics[i].at<uchar>(r,c);
			}
			bg.at<uchar>(r,c)	=	getMedian<uchar>(pl,npics);
		}
	}
	
	delete[] pl;
}

void f_setMatRectVal(Mat& mat,const Rect& region,uchar val){
	assert(mat.channels() == 1);

	Rect A	=	region & Rect(0,0,mat.cols,mat.rows);

	for(int r = A.y; r<A.y+A.height-1;++r){
		uchar* ptr	=	mat.ptr(r);
		memset(ptr+A.x,val,sizeof(uchar)*A.width);
	}
}

int Hlow	=	0;
int Hhigh	=	256;
int Slow	=	0;
int Shigh	=	256;
void sliderCallback(int, void*){}

void f_adjustChannelThreshold(const Mat& src,int* val){
	Mat cache	=	src.clone();
	const string winName	=	"cache";
	imshow(winName, cache);

	createTrackbar("Hlow: ",winName,&Hlow,255,sliderCallback,&cache);
	createTrackbar("Hhigh: ",winName,&Hhigh,255,sliderCallback,&cache);
	createTrackbar("Slow: ",winName,&Slow,255,sliderCallback,&cache);
	createTrackbar("Shigh: ",winName,&Shigh,255,sliderCallback,&cache);

	waitKey();

	cout<<Hhigh<<" "<<Hlow<<" "<<Shigh<<" "<<Slow<<endl;
}

/*
   double[] a = new double[5];
   double[] b = new double[5];
   a[0] = (-p1.x + 3 * p2.x - 3 * p3.x + p4.x) / 6.0;
   a[1] = (3 * p1.x - 6 * p2.x + 3 * p3.x) / 6.0;
   a[2] = (-3 * p1.x + 3 * p3.x) / 6.0;
   a[3] = (p1.x + 4 * p2.x + p3.x) / 6.0;
   b[0] = (-p1.y + 3 * p2.y - 3 * p3.y + p4.y) / 6.0;
   b[1] = (3 * p1.y - 6 * p2.y + 3 * p3.y) / 6.0;
   b[2] = (-3 * p1.y + 3 * p3.y) / 6.0;
   b[3] = (p1.y + 4 * p2.y + p3.y) / 6.0;
   splinex[0] = a[3];
   spliney[0] = b[3];
   int i;
   for (i = 1; i <= divisions - 1; i++)
   {
   float t = System.Convert.ToSingle(i) / System.Convert.ToSingle(divisions);
   splinex[i] = (a[2] + t * (a[1] + t * a[0]))*t+a[3] ;
   spliney[i] = (b[2] + t * (b[1] + t * b[0]))*t+b[3] ;
*/
const float A[][4]	={-1, 3, -3, 1, 3, -6, 3, 0, -3, 0, 3, 0, 1, 4, 1, 0};
void f_bsp3(cv::Point* points,float* a,float* b){
	assert(points && a && b);
	for(int i=0;i<4;++i){
		a[i]	=	0;
		b[i]	=	0;
		for(int u=0;u<4;++u){
			a[i]	+=	A[i][u]*points[i].x;
			b[i]	+=	A[i][u]*points[i].y;
		}
	}
}


void f_grabFrame(int camid, const std::string& folder){
	VideoCapture cap(camid);
	assert(cap.isOpened());
	Mat frame;
	const string winName	=	"win";
	char imgName[10];
	int imgIndex	=	0;
	namedWindow(winName);
	while(true){
		cap>>frame;
		if(!frame.data)
			break;

		imshow(winName,frame);

		int key	=	waitKey(33);
		switch(key)
		{
		case ' ':
			sprintf_s(imgName,10,"%04d.jpg",imgIndex++);
			if(!imwrite(folder+imgName,frame))
				cerr<<"failed to save file!"<<endl;
			else
				cout<<"new image saved: "<<folder<<imgName<<endl;
			break;
		case 27:
			return;
		default:
			break;
		}
	}
}

void f_grabProcessedFrame(int camid,const std::string& folder,void(*func)(cv::Mat& mat)){
	VideoCapture cap(camid);
	assert(cap.isOpened());
	Mat frame;
	const string winName	=	"win";
	char imgName[10];
	int imgIndex	=	0;
	namedWindow(winName);
	while(true){
		cap>>frame;
		if(!frame.data)
			break;

		func(frame);
		imshow(winName,frame);

		int key	=	waitKey(33);
		switch(key)
		{
		case ' ':
			sprintf_s(imgName,10,"%04d.jpg",imgIndex++);
			if(!imwrite(folder+imgName,frame))
				cerr<<"failed to save file!"<<endl;
			else
				cout<<"new image saved: "<<folder<<imgName<<endl;
			break;
		case 27:
			return;
		default:
			break;
		}
	}
}

void f_drawRay(cv::Mat& drawing,const cv::Point2f& p1,const cv::Point2f& p2,cv::Scalar color,int w){
	Point dP	=	p2-p1;
	Point2f pd1(0,(0-p1.x)*dP.y/dP.x+p1.y);
	Point2f pd2(drawing.cols,(drawing.cols-p1.x)*dP.y/dP.x+p1.y);
	line(drawing,pd1,pd2,color,w);
}

Mat f_makeUChar(const cv::Mat& fmat){
	assert(fmat.channels()==1);
	Mat re(fmat.size(),CV_8UC1);

	double maxVal,minVal;
	Point minLoc,maxLoc;
	minMaxLoc(fmat,&minVal,&maxVal,&minLoc,&maxLoc);

	if(minVal==maxVal){
		re.setTo(0);
	}
	else{
		const int type	=	fmat.type();
		for(int r=0;r<fmat.rows;++r){
			uchar* pRe	=	re.ptr<uchar>(r);
			const float* pFMat	=	fmat.ptr<float>(r);
			for(int c=0;c<fmat.cols;++c){
				pRe[c]	=	(pFMat[c]-minVal)/(maxVal-minVal)*255;
			}
		}
	}

	return re;
}

bool f_saveTextFile(const cv::Mat& mat,std::string filename){
	ofstream fout(filename,ios::out);
	if(!fout.is_open())
		return false;

	for(int r=0;r<mat.rows;++r){
		const float* ptr	=	mat.ptr<float>(r);
		for(int c=0;c<mat.cols;++c){
			fout<<ptr[c]<<" ";
		}
		fout<<"\n";
	}
	fout.close();

	return true;
}

Mat f_bar(float* data,int length,Scalar color,float barWR,Size imgSize,Size margin){
	int barWidth	=	imgSize.width/length;
	Mat plotImg(imgSize.height+margin.height*2,barWidth*length+margin.width*2,
		CV_8UC3,Scalar::all(255));

	float maxval	=	numeric_limits<float>::min();
	for(int i=0;i<length;++i){
		if(data[i]>maxval)
			maxval	=	data[i];
	}

	for(int i=0;i<length;++i){
		int height	=	data[i]/maxval*imgSize.height;

		rectangle(plotImg,Point(margin.width+barWidth*i+barWidth*(1-barWR)/2,plotImg.rows-margin.height),
			Point(margin.width+barWidth*i+barWidth*barWR+barWidth*(1-barWR)/2,plotImg.rows-(height+margin.height)),
			color,FILLED);
	}

	return plotImg;
}
