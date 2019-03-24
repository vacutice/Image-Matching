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

//***********moravec�ǵ��⺯��*******************  
//srcImage   ������ʾ�����ͼ  
//kSize      ������ʾ�˵ı߳�  
//Threshold  ������ʾ�趨����ֵ�Ĵ�С  
//*************************************************  
void CMoravec::Moravec(Mat srcImage, Mat srcImgColor){//srcImage�������Ӱ��

	//�ǵ���Ľ��ͼ  
	resMorMat = srcImage.clone();
	//�洢��Ȥ��λ��
	Interest = Mat::ones(srcImage.rows, srcImage.cols, CV_8U);
	int r = kSize / 2;//kSize����Ȥֵ���㴰��
	//��ȡͼ��ĸߺͿ�  
	const int nRows = srcImage.rows;
	const int nCols = srcImage.cols;
	
	int nCount = 0;
	//����ǵ������  
	CvPoint *pPoint = new CvPoint[nRows*nCols];
	//����ͼ��  
	for (int i = r; i < srcImage.rows - r; i++)
	{
		for (int j = r; j < srcImage.cols - r; j++)
		{
			int wV1, wV2, wV3, wV4;
			wV1 = wV2 = wV3 = wV4 = 0;
			//����ˮƽ�����ڵ���Ȥֵ  
			for (int k = -r; k <= r; k++)
			{
				for (int m = -r; m <= r; m++)
				{
					//�ж��ƶ��Ĺ������Ƿ�Խ�磬Խ��Ļ���������ǰ��ѭ�����������  
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

			//���㴹ֱ�����ڵ���Ȥֵ  
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

			//����45�㷽���ڵ���Ȥֵ  
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

			//����135�㷽���ڵ���Ȥֵ  
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
			//�����Ȥֵ������ֵ����ô���������������  
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