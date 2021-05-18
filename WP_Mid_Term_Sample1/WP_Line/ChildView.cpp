
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "WP_Line.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	Line_Num = 0;
	LUse = false;

	Line = new CLine*[100];
	for (int i = 0; i < 100; i++) {
		Line[i] = { NULL };
	}
}

CChildView::~CChildView()
{
	for (int i = 0; i < 100; i++) {
		Line[i] = { NULL };
		delete[] Line[i];
	}
	delete[] Line;
	Line = { NULL };
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this);
	CRect clientRect;
	GetClientRect(clientRect);

	// 더블 버퍼링 관련 변수

	CDC memDC;

	CBitmap* oldBit;
	CBitmap bmpBuff;

	memDC.CreateCompatibleDC(&dc);
	bmpBuff.CreateCompatibleBitmap(&dc, clientRect.Width(), clientRect.Height());

	oldBit = memDC.SelectObject(&bmpBuff);

	memDC.PatBlt(0, 0, clientRect.Width(), clientRect.Height(), WHITENESS);

	CString sTxt;

	
	for (int i = 0; i < Line_Num; i++) {
		Line[i]->Draw(&memDC);
	}

	
	sTxt.Format(L"%d", Line_Num);
	TextOut(memDC, 10, 10, sTxt, sTxt.GetLength()); // 핵심 1
	

	if (LUse == true) {
		Line[Line_Num] = new CLine(Start_Point, End_Point);

		Line[Line_Num]->Draw(&memDC); // 핵심 2

		dc.BitBlt(0, 0,
			clientRect.Width(), clientRect.Height(),
			&memDC,
			0, 0,
			SRCCOPY);
	}

	dc.BitBlt(0, 0,
		clientRect.Width(), clientRect.Height(),
		&memDC,
		0, 0,
		SRCCOPY);

	memDC.SelectObject(&oldBit);
	memDC.DeleteDC();
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	Start_Point = point;
	LUse = true;
	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	End_Point = point;
	if (LUse == true) {
		Invalidate();
	}
	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	LUse = false;
	Line_Num++;
	Invalidate(); // 핵심 3
	CWnd::OnLButtonUp(nFlags, point);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	//
	return true;
}
