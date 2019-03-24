
// ImageMatching_CorrelationCoefficientDlg.h : header file
//

#pragma once
#include <opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
using namespace cv;

// CImageMatching_CorrelationCoefficientDlg dialog
class CImageMatching_CorrelationCoefficientDlg : public CDialogEx
{
// Construction
public:
	CImageMatching_CorrelationCoefficientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_IMAGEMATCHING_CORRELATIONCOEFFICIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:


	Mat m_leftimg;            //��Ӱ��ҶȾ���  
	Mat m_rightimg;           //��Ӱ��ҶȾ���  
	Mat m_leftimgcolor;       //��Ӱ���ɫ  
	Mat m_rightimgcolor;      //��Ӱ���ɫ  

	bool bLeftOpened;           //�����Ӱ���Ƿ����  
	bool bRightOpened;          //�����Ӱ���Ƿ����  

	CString strFileLeftImage;
	CString strFileRightImage;
	afx_msg void OnBnClickedButtonOpenl();
	afx_msg void OnBnClickedButtonOpenr();
	afx_msg void OnBnClickedButtonMatch();
};
