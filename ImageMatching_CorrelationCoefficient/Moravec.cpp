#include "stdafx.h"
#include "Moravec.h"
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  

CMoravec::CMoravec()
{
	kSize = 5;//
	threshold = 20000;
}


CMoravec::~CMoravec()
{
}

//***********moravec角点检测函数*******************  
//srcImage   参数表示输入的图  
//kSize      参数表示核的边长  
//Threshold  参数表示设定的阈值的大小  
//*************************************************  
void CMoravec::Moravec(Mat srcImage, Mat srcImgColor){//srcImage是输入的影像

	//角点检测的结果图  
	resMorMat = srcImage.clone();
	//存储兴趣点位置
	Interest = Mat::ones(srcImage.rows, srcImage.cols, CV_8U);
	int r = kSize / 2;//kSize是兴趣值计算窗口
	//获取图像的高和宽  
	const int nRows = srcImage.rows;
	const int nCols = srcImage.cols;
	
	int nCount = 0;
	//保存角点的坐标  
	CvPoint *pPoint = new CvPoint[nRows*nCols];
	//遍历图像  
	for (int i = r; i < srcImage.rows - r; i++)
	{
		for (int j = r; j < srcImage.cols - r; j++)
		{
			int wV1, wV2, wV3, wV4;
			wV1 = wV2 = wV3 = wV4 = 0;
			//计算水平方向窗内的兴趣值  
			for (int k = -r; k <= r; k++)
			{
				for (int m = -r; m <= r; m++)
				{
					//判断移动的过程中是否越界，越界的话就跳过当前的循环，以免出错  
					int a = i + k;
					int b = j + m + 1;
					if (b >= srcImage.cols)
					{
						continue;
					}
					wV1 += (srcImage.at<uchar>(i + k, j + m + 1) - srcImage.at<uchar>(i + k, j + m))
						*(srcImage.at<uchar>(i + k, j + m + 1) - srcImage.at<uchar>(i + k, j + m));
				}
			}

			//计算垂直方向窗内的兴趣值  
			for (int k = -r; k <= r; k++)
			{
				for (int m = -r; m <= r; m++)
				{
					int a = i + k + 1;
					int b = j + m;
					if (a >= srcImage.rows)
					{
						continue;
					}
					wV2 += (srcImage.at<uchar>(i + k + 1, j + m) - srcImage.at<uchar>(i + k, j + m))
						*(srcImage.at<uchar>(i + k + 1, j + m) - srcImage.at<uchar>(i + k, j + m));
				}
			}

			//计算45°方向窗内的兴趣值  
			for (int k = -r; k <= r; k++)
			{
				for (int m = -r; m <= r; m++)
				{
					int a = i + k + 1;
					int b = j + m + 1;
					if (a >= srcImage.rows || b >= srcImage.cols)
					{
						continue;
					}
					wV3 += (srcImage.at<uchar>(i + k + 1, j + m + 1) - srcImage.at<uchar>(i + k, j + m))
						*(srcImage.at<uchar>(i + k + 1, j + m + 1) - srcImage.at<uchar>(i + k, j + m));
				}
			}

			//计算135°方向窗内的兴趣值  
			for (int k = -r; k <= r; k++)
			{
				for (int m = -r; m <= r; m++)
				{
					int a = i + k + 1;
					int b = j + m - 1;
					if (a >= srcImage.rows || b < 0)
					{
						continue;
					}
					wV4 += (srcImage.at<uchar>(a, b) - srcImage.at<uchar>(i + k, j + m))
						*(srcImage.at<uchar>(a, b) - srcImage.at<uchar>(i + k, j + m));
				}
			}
			int  value = min(min(wV1, wV2), min(wV3, wV4));
			//如果兴趣值大于阈值，那么将坐标存入数组中  
			if (value > threshold)
			{
				pPoint[nCount] = cvPoint(j, i);
				nCount++;
				Interest.at<uchar>(i, j) = 0;
			}
		}
	}
	FeatureNum = nCount;
	for (int i = 0; i < nCount; i++)
	{
		circle(resMorMat, pPoint[i], 5, Scalar(255, 0, 0),1,8,0);
	}
}