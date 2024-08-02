
// Project_To_GrimDlg.h: 헤더 파일
//
#include "CImagePad.h"
#pragma once


// CProjectToGrimDlg 대화 상자
class CProjectToGrimDlg : public CDialogEx
{

private:
	CImage m_image; // 이미지파일
	// 생성입니다.
public:
	CProjectToGrimDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.




	CImagePad* m_pImagePad;




	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJECT_TO_GRIM_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	CBitmapButton* m_oBtnOnOff;

	// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	int Circle_ct;
	int DrawCount;
	void UpdateDedplay();
	void DrawCircle();
	void DrawFn(int radius, int Pitch, int x ,int y, unsigned char* fm);
	void DrawRadius_To_Center(CImage& m_image);
	void PrintCircleInfo(int radius, double x ,double y);
	void HideCircleInfo();
	
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedFiileLoad();
};
	 
