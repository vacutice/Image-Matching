#pragma once
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/core/core.hpp" 
#include <algorithm>
using namespace cv;
class CMoravec
{


public:
	Mat LeftImgEpi;
	Mat LeftImgColor;
	int kSize;
	double threshold;
	Mat Interest;
	int FeatureNum;
	Mat resMorMat;

public:
	CMoravec();
	~CMoravec();
	void Moravec(Mat LeftImgEpi, Mat LeftImgColor);
};

