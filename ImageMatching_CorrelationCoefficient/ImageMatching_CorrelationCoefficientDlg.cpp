#include "stdafx.h"
#include "ImageMatching_CorrelationCoefficient.h"
#include "ImageMatching_CorrelationCoefficientDlg.h"
#include "afxdialogex.h"
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include "Match.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CImageMatching_CorrelationCoefficientDlg dialog



CImageMatching_CorrelationCoefficientDlg::CImageMatching_CorrelationCoefficientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CImageMatching_CorrelationCoefficientDlg::IDD, pParent)
	, strFileLeftImage(_T(""))
	, strFileRightImage(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageMatching_CorrelationCoefficientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LEFTIMAGE, strFileLeftImage);
	DDX_Text(pDX, IDC_EDIT_RIGHTIMAGE, strFileRightImage);
}

BEGIN_MESSAGE_MAP(CImageMatching_CorrelationCoefficientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OpenL, &CImageMatching_CorrelationCoefficientDlg::OnBnClickedButtonOpenl)
	ON_BN_CLICKED(IDC_BUTTON_OpenR, &CImageMatching_CorrelationCoefficientDlg::OnBnClickedButtonOpenr)
	ON_BN_CLICKED(IDC_BUTTON_Match, &CImageMatching_CorrelationCoefficientDlg::OnBnClickedButtonMatch)
END_MESSAGE_MAP()


// CImageMatching_CorrelationCoefficientDlg message handlers

BOOL CImageMatching_CorrelationCoefficientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CImageMatching_CorrelationCoefficientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CImageMatching_CorrelationCoefficientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CImageMatching_CorrelationCoefficientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CImageMatching_CorrelationCoefficientDlg::OnBnClickedButtonOpenl()
{
	// TODO: Add your control notification handler code here
	TCHAR path[255];
	SHGetSpecialFolderPath(0, path, CSIDL_DESKTOPDIRECTORY, 0);
	UpdateData(TRUE);
	CFileDialog FileDlg(TRUE, path, L"*.jpg;*.bmp", OFN_HIDEREADONLY | OFN_READONLY, L"*.jpg;*.bmp", NULL);
	//CFileDialog FileDlg(TRUE, L"*.jpg;*.bmp", L"*.jpg;*.bmp", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"影像文件()");
	if (FileDlg.DoModal() != IDOK)
	{
		return;
	}
	strFileLeftImage = FileDlg.GetPathName();
	bLeftOpened = TRUE;         //标记已经读入影像  
	UpdateData(FALSE);  //将影像名字显示到对话框中  
	USES_CONVERSION;
	std::string str1(W2A(strFileLeftImage));
	m_leftimg = imread(str1, CV_LOAD_IMAGE_GRAYSCALE);//打开影像  
	m_leftimgcolor = imread(str1, CV_LOAD_IMAGE_COLOR);//打开影像  
	//imshow("左影像",m_leftimg); //图像显示  
	//cvWaitKey();
}


void CImageMatching_CorrelationCoefficientDlg::OnBnClickedButtonOpenr()
{
	// TODO: Add your control notification handler code here
	TCHAR path[255];
	SHGetSpecialFolderPath(0, path, CSIDL_DESKTOPDIRECTORY, 0);
	UpdateData(TRUE);
	CFileDialog FileDlg(TRUE, path, L"*.jpg;*.bmp", OFN_HIDEREADONLY | OFN_READONLY, L"*.jpg;*.bmp", NULL);
	//CFileDialog FileDlg(TRUE, L"*.jpg;*.bmp", L"*.jpg;*.bmp", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"影像文件()");
	if (FileDlg.DoModal() != IDOK)
	{
		return;
	}
	strFileRightImage = FileDlg.GetPathName();
	bRightOpened = TRUE;         //标记已经读入影像  
	UpdateData(FALSE);  //将影像名字显示到对话框中  
	USES_CONVERSION;
	std::string str1(W2A(strFileRightImage));
	m_rightimg = imread(str1, CV_LOAD_IMAGE_GRAYSCALE);//打开影像  
	m_rightimgcolor = imread(str1, CV_LOAD_IMAGE_COLOR);//打开影像  
	//imshow("右影像",m_rightimg); //图像显示  
	//cvWaitKey();
}


void CImageMatching_CorrelationCoefficientDlg::OnBnClickedButtonMatch()
{
	// TODO: Add your control notification handler code here
	if (bLeftOpened == FALSE)
	{
		MessageBox(_T("请读入左影像"));
		return;
	}
	if (bRightOpened == FALSE)
	{
		MessageBox(_T("请读入右影像"));
		return;
	}

	CMatch CM;
	CM.FeatureMatchMain(m_leftimg, m_rightimg, m_leftimgcolor, m_rightimgcolor);
}
