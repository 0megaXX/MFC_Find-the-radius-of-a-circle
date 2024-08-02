// CImagePad.cpp: 구현 파일
//

#include "pch.h"
#include "Project_To_Grim.h"
#include "afxdialogex.h"
#include "CImagePad.h"


// CImagePad 대화 상자

IMPLEMENT_DYNAMIC(CImagePad, CDialogEx)

CImagePad::CImagePad(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CImagePad, pParent)
{

}

CImagePad::~CImagePad()
{
}

void CImagePad::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CImagePad, CDialogEx)
END_MESSAGE_MAP()


// CImagePad 메시지 처리기
