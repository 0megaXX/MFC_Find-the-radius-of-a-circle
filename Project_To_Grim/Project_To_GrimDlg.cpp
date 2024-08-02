
// Project_To_GrimDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Project_To_Grim.h"
#include "Project_To_GrimDlg.h"
#include "afxdialogex.h"

#include <iostream>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <time.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#pragma comment(linker ,"/entry:WinMainCRTStartup /subsystem:console")
#endif


using namespace std;

CString g_strFileImage = _T("c:\\img\\CircleImage_"); //저장경로 사용자 별로 다름 사용전 수정바람

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CProjectToGrimDlg 대화 상자



CProjectToGrimDlg::CProjectToGrimDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJECT_TO_GRIM_DIALOG, pParent)
	, Circle_ct(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProjectToGrimDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HowManyCircle, Circle_ct);
}

BEGIN_MESSAGE_MAP(CProjectToGrimDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CProjectToGrimDlg::OnBnClickedButton1)
	
	ON_EN_CHANGE(IDC_HowManyCircle, &CProjectToGrimDlg::OnEnChangeEdit1)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_Fiile_Load, &CProjectToGrimDlg::OnBnClickedFiileLoad)
END_MESSAGE_MAP()


// CProjectToGrimDlg 메시지 처리기

BOOL CProjectToGrimDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	
	m_pImagePad = new CImagePad; // 이미지를 띄우는 다이얼로그
	m_pImagePad->Create(IDD_CImagePad, this);
	//m_pImagePad->SetWindowPos(NULL, 0, 70, 0, 0, SWP_NOSIZE | SWP_NOZORDER); //부모기준 생성위치 
	
	m_pImagePad->ShowWindow(SW_SHOW);

	m_pImagePad->MoveWindow(10, 70, 750, 540); //위치 지정

	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CProjectToGrimDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CProjectToGrimDlg::OnPaint()
{
	if (IsIconic()) 
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CProjectToGrimDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CProjectToGrimDlg::OnBnClickedButton1() // 배경을 그리는 버튼
{
	
	
	HideCircleInfo(); // 그릴때는 원의 정보 출력안함

	UpdateData();
	int ct = Circle_ct; // 그리는 횟수
	SetDlgItemInt(IDC_HowManyCircle,ct); // 횟수를 갱신
	UpdateData(0); // 갱신
	srand(time(NULL));
	cout << ct << endl; // 갱신확인용 

	for (int a=1;a<=ct;a++)
	{


		if (m_image != NULL) //이미 이미지가 존재한다면 이미지 삭제
			m_image.Destroy();

		int nWidth = 640;
		int nHeight = 480;
		int nBpp = 8;

		m_image.Create(nWidth, -nHeight, nBpp); //이미지생성

		if (nBpp == 8) {
			static RGBQUAD rgb[256];
			for (int a = 0; a < 256; a++)
				rgb[a].rgbRed = rgb[a].rgbGreen = rgb[a].rgbBlue = a;

			m_image.SetColorTable(0, 256, rgb);

		} //흰색 초기화

		int nPitch = m_image.GetPitch();
		unsigned char* fm = (unsigned char*)m_image.GetBits(); // 이미지의 첫 포인터 가져옴
		memset(fm, 0xff, nWidth * nHeight); //얘도 초기화

		DrawCircle();
		UpdateDedplay();

		CString subName = g_strFileImage;
		subName.AppendFormat(_T("%d"), a); // a - '0'을 문자열로 변환하여 카운트 추가
		subName.Append(_T(".bmp")); // 확장자 추가
		cout << subName << endl; // 확인용
		m_image.Save(subName);
		Sleep(100);
	}

}

void CProjectToGrimDlg::UpdateDedplay() // 화면에 뿌리기
{

	//CClientDC dc1(this);
	//m_image.Draw(dc1, 80, 80); // 시작위치
	CClientDC dc2(m_pImagePad);
	m_image.Draw(dc2, 0, 0); // 시작위치로 부터 그림 뿌리기
	
}

void CProjectToGrimDlg::DrawCircle()
{
	

	// 파일을 생성할때는 반지름을 알 필요가 없기에 안보이게 변경

	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();

	//이미지 크기에 맞춰 이미지패드의 크기를 조정
	m_pImagePad->SetWindowPos(NULL, 0, 0, nWidth, nHeight, SWP_NOZORDER | SWP_NOMOVE);
	int radius;
	radius = (rand() % 100) + 5; // 반지름은 15~105 사이의 랜덤값.

	int x, y;

	do
	{
		x = (rand() % nWidth);
		y = (rand() % nHeight);

	} while (x - radius < 0 || x + radius >= nWidth || y - radius < 0 || y + radius >= nHeight);
	// x y를 기준으로 반지름을 펼쳤을때 그림의 영역을 안넘길때 까지 x y를 탐색

	cout << x << ' ' << y << endl; //확인용

	unsigned char* fm = (unsigned char*)m_image.GetBits(); // 이미지의 첫 포인터 가져옴
	DrawFn(radius, nPitch, x, y, fm); //x y 를 중심으로 원그리기
		
	
}

void CProjectToGrimDlg::DrawFn(int radius, int Pitch, int x, int y, unsigned char* fm)
{

	int nGray = 80;
	for (int a = -radius; a <= radius; a++)
		for (int b = -radius; b <= radius; b++)
			if (a * a + b * b <= radius * radius) // 원의 내부에 있는지 확인
			{
				int px = x + a;
				int py = y + b;
				fm[py * Pitch + px] = nGray; 

			}
}

void CProjectToGrimDlg::DrawRadius_To_Center(CImage& m_image)
{
	unsigned char* fm = (unsigned char*)m_image.GetBits(); // 정보 가져오기

	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();

	int nTh = 0x80;
	CRect rect(0, 0, nWidth, nHeight); // 그림 크기만큼 범위
	
	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;

	int BackGroundColor = fm[0];
	// 그림판의 범위를 넘는 원은 존재하지 않기때문에 이미지의 맨 좌측 상단은 반드시 배경색이다
	// 그렇기에 배경색을 기준으로 배경색과 다른 색은 원의 색
	
	for (int a = rect.top; a < rect.bottom; a++)
		for (int b = rect.left; b < rect.right; b++)
			if (fm[a * nPitch + b] != BackGroundColor) // 배경색과 다르다면 
			{
				nSumX += b;
				nSumY += a;
				nCount++;	
			}


	if (nCount == 0) return; // 만약 원이 없다면 종료


	double dCenterX = nSumX / nCount;
	double dCenterY = nSumY / nCount;

	cout << dCenterX << ' ' << dCenterY;



	double maxDistance = 0;
	 /*for (int a = rect.top; a < rect.bottom; a++)
	{
		for (int b = rect.left; b < rect.right; b++)
		{
			if (fm[a * nPitch + b] != BackGroundColor)
				// 배경색과 다르단 것은 원의 일부라는 말
			{
				double distance = sqrt(pow(dCenterX - b, 2) + pow(dCenterY - a, 2)); // 반지름은

				maxDistance = max(maxDistance ,distance); // 최대 긴 길이가 테두리로부터의 반지름
				
			}
		}
	}*/

	for (int a = rect.top; a < rect.bottom; a++)
	{
		for (int b = rect.left; b < rect.right; b++)
		{
			if (fm[a * nPitch + b] != BackGroundColor) 
				// 배경색과 다른 색을 만나는 순간은 원의 테두리에서 만났다는 것, 테두리로부터 반지름은 어떤위치든 길이가 같음
			{
				maxDistance = sqrt(pow(dCenterX - b, 2) + pow(dCenterY - a, 2)); 
				break;
			}
		}
		
	}

	int radius = (int)maxDistance;
	cout << "Radius: " << radius << endl;

	int center_radius = radius / 7;

	/*for (int a = dCenterY - center_radius; a < dCenterY + center_radius; a++)
		for (int b = dCenterX - center_radius; b < dCenterX + center_radius; b++)
		{

			fm[a * nPitch + b] = 0;
		}*/

	for (int a = -center_radius; a <= center_radius; a++)
		for (int b = -center_radius; b <= center_radius; b++)
			if (a * a + b * b <= center_radius * center_radius) // 원의 내부에 있는지 확인
			{
				int px = (int)dCenterX + b;
				int py = (int)dCenterY + a;
				fm[py * nPitch + px] = 0; // 검정색으로 색칠
				
			}
		

	int x0 = (int)dCenterX;
	int y0 = (int)dCenterY;
	int x1 = x0 + radius; // 중점으로 부터 X축으로 반지름을 그림
	int y1 = y0;

	// 직선 그리기 (x0, y0)에서 (x1, y1)까지
	for (int x = x0; x <=x1; ++x)
	{
		int y = y0; // y좌표는 고정
		if (x < nWidth)
			fm[y * nPitch + x] = 0; // 줄긋기
		
	}

	PrintCircleInfo(radius, dCenterX, dCenterY); // 반지름을 명시적으로 화면에 출력
	
	
}

void CProjectToGrimDlg::PrintCircleInfo(int radius ,double x, double y) // 이미지 불러오면 해당 이미지의 원의 반지름 중심 x,y출력
{
	CFont font;
	LOGFONT logfont;
	::ZeroMemory(&logfont, sizeof(logfont));
	logfont.lfHeight = 18; // 글자 너무 작아서 넣음
	font.CreateFontIndirect(&logfont);
	GetDlgItem(IDC_STATIC_RA)->SetFont(&font);
	GetDlgItem(IDC_STATIC_RADIUS)->SetFont(&font);
	GetDlgItem(IDC_STATIC_CenX)->SetFont(&font);
	GetDlgItem(IDC_STATIC_CenXrs)->SetFont(&font);
	GetDlgItem(IDC_STATIC_CenY)->SetFont(&font);
	GetDlgItem(IDC_STATIC_CenYrs)->SetFont(&font);
	SetDlgItemText(IDC_STATIC_RA, _T("Radius is "));
	SetDlgItemInt(IDC_STATIC_RADIUS, radius);
	SetDlgItemText(IDC_STATIC_CenX, _T("Center X pos is "));
	SetDlgItemInt(IDC_STATIC_CenXrs, (int)x);
	SetDlgItemText(IDC_STATIC_CenY, _T("Center Y pos is "));
	SetDlgItemInt(IDC_STATIC_CenYrs, (int)y);
	font.Detach();
	

}

void CProjectToGrimDlg::HideCircleInfo()
{
	SetDlgItemText(IDC_STATIC_RA, _T(""));
	SetDlgItemText(IDC_STATIC_RADIUS, _T(""));
	SetDlgItemText(IDC_STATIC_CenX, _T(""));
	SetDlgItemText(IDC_STATIC_CenXrs, _T(""));
	SetDlgItemText(IDC_STATIC_CenY, _T(""));
	SetDlgItemText(IDC_STATIC_CenYrs, _T(""));
}




void CProjectToGrimDlg::OnEnChangeEdit1()
{
}

void CProjectToGrimDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if(m_pImagePad==NULL)
		delete m_pImagePad;
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CProjectToGrimDlg::OnBnClickedFiileLoad() // 이미지 로드
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CFileDialog dlg(TRUE, _T("bmp"), NULL, 
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("Bitmap Files (*.bmp)|*.bmp||")); 
	// 탐색기에서 bmp파일 열기 \\는 목록의 끝

	if (dlg.DoModal() == IDOK) //확인을 눌렀다면 IDOK 아니면 IDCANCEL
	{
		CString filePath = dlg.GetPathName(); // 사용자가 선택한 파일의 경로를 반환

		
		if (m_image) // 기존 이미지가 제거
		{
			m_image.Destroy();
		}

		// 선택한 BMP 파일을 m_image에 로드
		HRESULT hr = m_image.Load(filePath);

		if (FAILED(hr)) 
		{
			AfxMessageBox(_T("이미지 로드 실패"));
			return;
		}
		
		//이미지 크기정보 불러오기
		int nWidth = m_image.GetWidth(); 
		int nHeight = m_image.GetHeight();
		

		//이미지 크기에 맞춰 이미지패드의 크기를 조정
		m_pImagePad->SetWindowPos(NULL, 0, 0, nWidth, nHeight, SWP_NOZORDER | SWP_NOMOVE);
		
		// 이미지를 화면에 업데이트
		DrawRadius_To_Center(m_image);
		UpdateDedplay();
		
	}
}
