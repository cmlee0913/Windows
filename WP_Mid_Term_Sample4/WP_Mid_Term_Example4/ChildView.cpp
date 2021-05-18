
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "WP_Mid_Term_Example4.h"
#include "ChildView.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
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

	// 비트맵(트리플 버퍼링?) 관련 변수

	CDC bitDC;

	CBitmap* bitoldBit;
	CBitmap bitBit;

	CBitmap bitmap;
	BITMAP bmpinfo;

	bitDC.CreateCompatibleDC(&dc);
	bitBit.CreateCompatibleBitmap(&dc, clientRect.Width(), clientRect.Height());

	bitmap.LoadBitmap(IDB_BITMAP1);
	bitmap.GetBitmap(&bmpinfo);

	bitoldBit = bitDC.SelectObject(&bitmap);

	memDC.StretchBlt((clientRect.Width() / 2) - (clientRect.Height() / 2), 0,  // 핵심 1
		clientRect.Height(),
		clientRect.Height(),
		&bitDC, 0, 0,
		bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);

	dc.BitBlt(0, 0,
		clientRect.Width(), clientRect.Height(),
		&memDC,
		0, 0,
		SRCCOPY);

	memDC.SelectObject(&oldBit);
	bitDC.SelectObject(&bitoldBit);

	memDC.DeleteDC();
	bitDC.DeleteDC();
}



BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	Invalidate();

	CWnd::OnMouseMove(nFlags, point);
}
