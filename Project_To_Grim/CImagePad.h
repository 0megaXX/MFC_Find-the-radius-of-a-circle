#pragma once
#include "afxdialogex.h"


// CImagePad 대화 상자

class CImagePad : public CDialogEx
{
	DECLARE_DYNAMIC(CImagePad)

public:
	CImagePad(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CImagePad();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CImagePad };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
