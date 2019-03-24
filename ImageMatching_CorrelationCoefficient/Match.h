#pragma once


#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/core/core.hpp"  
#include "Moravec.h"  
using namespace cv;

struct MatchPt2i//ͬ����ṹ��  
{
	Point2i lpt;//�����Ӱ���ϵĵ�  
	Point2i rpt;//�Һ���Ӱ���ϵĵ�  
};

class CMatch
{
public:
	CMatch();
	~CMatch();

	Mat LeftImgEpi;  //�����Ӱ��  
	Mat RightImgEpi; //�Һ���Ӱ��  
	int windowsize;  //ģ�崰�ڵĴ�С  
	double Threshold;//���ϵ������ֵ  
	int num;         //ƥ��ͬ�������  
	MatchPt2i *Mpt2i;//ͬ����ṹ������  
	
	double NCCScore(int lr, int lc, int rr, int rc);//�������ϵ��  
	void showresult(const Mat LeftImgColor, const Mat RightImgColor, Mat &ResultImg);//չʾ���Ӱ��
	void FeatureMatchMain(Mat LeftImg, Mat RightImg, Mat LeftImgColor, Mat RightImgColor);//Ӱ��ƥ��������  
};

