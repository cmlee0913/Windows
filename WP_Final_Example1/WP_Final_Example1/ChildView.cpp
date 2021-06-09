
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "WP_Final_Example1.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	l_click = false;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
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
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
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

	p_list.AddTail(new CDot(draw_point));

	POSITION pos = p_list.GetHeadPosition();

	while (pos != NULL) {
		CDot* value = p_list.GetNext(pos);		// pos 위치의 데이터 반환 후, pos는 list의 다음 위치를 가르킴
		value->Draw(&memDC);
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
	l_click = true;

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	l_click = false;

	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	p_list.RemoveTail();

	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CWnd::OnRButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (l_click) {
		draw_point = point;
		Invalidate();
	}

	CWnd::OnMouseMove(nFlags, point);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return true;
}
