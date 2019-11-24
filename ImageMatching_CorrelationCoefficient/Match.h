#pragma once


#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/core/core.hpp"  
#include "Moravec.h"  
using namespace cv;

struct MatchPt2i//同名点结构体  
{
	Point2i lpt;//左核线影像上的点  
	Point2i rpt;//右核线影像上的点  
};

class CMatch
{
public:
	CMatch();
	~CMatch();

	Mat LeftImgEpi;  //左核线影像  
	Mat RightImgEpi; //右核线影像  
	int windowsize;  //模板窗口的大小  
	double Threshold;//相关系数的阈值  
	int num;         //匹配同名点个数  
	MatchPt2i *Mpt2i;//同名点结构体数组  
	
	double NCCScore(int lr, int lc, int rr, int rc);//计算相关系数  
	void showresult(const Mat LeftImgColor, const Mat RightImgColor, Mat &ResultImg);//展示结果影像
	void FeatureMatchMain(Mat LeftImg, Mat RightImg, Mat LeftImgColor, Mat RightImgColor);//影像匹配主函数  
};

