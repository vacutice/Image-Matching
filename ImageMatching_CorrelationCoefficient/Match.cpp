#include "stdafx.h"
#include "Match.h"
#include "math.h"  
#include "Moravec.h"  


CMatch::CMatch()
{
	windowsize = 7;  //设置匹配窗口的大小
	Threshold = 0.89;  //设置阈值
	Mpt2i = NULL; 
	num = 0;
}


CMatch::~CMatch()
{
}


void CMatch::showresult(const Mat LeftImgColor, const Mat RightImgColor, Mat &ResultImg)
{
	int rResult= LeftImgColor.rows > RightImgColor.rows ? LeftImgColor.rows : RightImgColor.rows;

	ResultImg.create(rResult, LeftImgColor.cols + RightImgColor.cols, LeftImgColor.type());
	for (int i = 0; i<LeftImgColor.rows; i++)
	{
		for (int j = 0; j<LeftImgColor.cols; j++)
		{
			ResultImg.at<Vec3b>(i, j) = LeftImgColor.at<Vec3b>(i, j);
		}
	}
	for (int i = 0; i<RightImgColor.rows; i++)
	{
		for (int j = 0; j<RightImgColor.cols; j++)
		{
			ResultImg.at<Vec3b>(i, j + LeftImgColor.cols) = RightImgColor.at<Vec3b>(i, j);
		}
	}
}
double CMatch::NCCScore(int lr, int lc, int rr, int rc)
{
	double gLeftAverage = 0;//左影像窗口灰度平均值  
	double gRightAverage = 0;//右影像窗口灰度平均值  
	int halfsize = windowsize / 2;
	for (int i = -halfsize; i<windowsize - halfsize; i++)
	{
		for (int j = -halfsize; j<windowsize - halfsize; j++)
		{
			gLeftAverage += LeftImgEpi.at<uchar>(lr + i, lc + j);
			gRightAverage += RightImgEpi.at<uchar>(rr + i, rc + j);
		}
	}
	gLeftAverage /= windowsize*windowsize;
	gRightAverage /= windowsize*windowsize;
	double a = 0;
	double b = 0;
	double c = 0;
	for (int i = -halfsize; i<windowsize - halfsize; i++)
	{
		for (int j = -halfsize; j<windowsize - halfsize; j++)
		{
			double left_av = LeftImgEpi.at<uchar>(lr + i, lc + j) - gLeftAverage;
			double right_av = RightImgEpi.at<uchar>(rr + i, rc + j) - gRightAverage;
			a += left_av*right_av;
			b += left_av*left_av;
			c += right_av*right_av;
		}
	}
	return a / sqrt(b*c);//返回相关系数的大小  
}
void CMatch::FeatureMatchMain(Mat LeftImg, Mat RightImg, Mat LeftImgColor, Mat RightImgColor)
{


	LeftImgEpi = LeftImg;
	RightImgEpi = RightImg;

	Point offset = Point(0, 170);

	Mat Result;
	showresult(LeftImgColor, RightImgColor, Result);//将两张彩色影像和合并1个  
	imshow("拼接结果", Result);
	cvWaitKey();
	Mat Interest;//兴趣矩阵  
	CMoravec CM;
	int FeatureNum;//特征点个数  
	CM.Moravec(LeftImgEpi, LeftImgColor);//Moravec特征提取  
	Mat mFeaturePoint = CM.resMorMat.clone();
	FeatureNum = CM.FeatureNum;
	Interest = CM.Interest.clone();
	Mpt2i = new struct MatchPt2i[FeatureNum];//给同名点结构体数组分配内存空间  
	int halfsize = windowsize / 2;
	int Lr = LeftImgEpi.rows;
	int Lc = LeftImgEpi.cols;
	int Rr = RightImgEpi.rows;
	int Rc = RightImgEpi.cols;
	//搜索匹配点  
	for (int i = 20+169; i<Lr - halfsize; i=i+5)
	{
		for (int j = 20; j<Lc - 20-237; j=j+5)
		{
			if (Interest.at<uchar>(i, j) == 0)
				//特征点作为模板中心  
			{
				double maxscore = 0;
				for (int r = i-169-20+5 ; r < i-169+ 20&&r<Rr; r++){
					for (int c = j +237 -  20+5 ; c< j+237 + 20&&c<Rc; c++)
					{
						double score = NCCScore(i, j, r, c);//计算相关系数  
						if (score>maxscore)
						{
							maxscore = score;//计算相关系数的最大值  
						}
					}
				}
				for (int r = i-169-20+5; r < i-169+20&&r<Rr; r++){
					for (int c = j+237- 20+5; c < Rr; c++)
					{
						double score = NCCScore(i, j, r, c);
						if ((score == maxscore) && (score>Threshold))
						{
							//用直线连接同名点  
							line(Result, Point(j, i), Point(c + LeftImgEpi.cols, r), cvScalar(0, 0, 255));
							//imwrite("match_result.bmp", Result);
							//imshow("拼接结果", Result);
							//cvWaitKey();
							//将匹配结果存入数组  
							Mpt2i[num].lpt = Point(j, i);
							Mpt2i[num].rpt = Point(c, r);
							num += 1;
						}
					}
				}
			}
		}
		i;
	}

	imwrite("match_result.bmp", Result);
	imwrite("feature_result.bmp", mFeaturePoint);
	imshow("角点检测结果", mFeaturePoint);
	imshow("匹配结果", Result);
	//将匹配结果写入文件  
	FILE *fp = fopen("match_point.txt", "w");
	if (fp == NULL)
	{
		return;
	}
	fprintf(fp, "%1i\n", num);
	for (int i = 0; i<num; i++)
	{
		fprintf(fp, "%04d %04d %04d %04d\n",
			Mpt2i[i].lpt.x, Mpt2i[i].lpt.y, Mpt2i[i].rpt.x, Mpt2i[i].rpt.y);
	}
	fclose(fp);
}