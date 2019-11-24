
// ImageMatching_CorrelationCoefficient.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CImageMatching_CorrelationCoefficientApp:
// See ImageMatching_CorrelationCoefficient.cpp for the implementation of this class
//

class CImageMatching_CorrelationCoefficientApp : public CWinApp
{
public:
	CImageMatching_CorrelationCoefficientApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CImageMatching_CorrelationCoefficientApp theApp;