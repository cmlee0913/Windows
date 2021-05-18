
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "WP_Mid_Term_Sample5.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_pt = CPoint(100, 100);
	m_dx = 10;
	m_dy = 10;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
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

	memDC.Rectangle(m_pt.x - 25, m_pt.y - 25, m_pt.x + 25, m_pt.y + 25);

	dc.BitBlt(0, 0,
		clientRect.Width(), clientRect.Height(),
		&memDC,
		0, 0,
		SRCCOPY);

	memDC.SelectObject(&oldBit);

	memDC.DeleteDC();
}



int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetTimer(0, 33, NULL);

	return 0;
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	CRect client;
	GetClientRect(&client);

	if (nIDEvent == 0) {
		if (m_pt.y + 25 > client.bottom) {
			m_dy = -m_dy;
		}
		if (m_pt.y - 25 < client.top) {
			m_dy = -m_dy;
		}
		if (m_pt.x + 25 > client.right) {
			m_dx = -m_dx;
		}
		if (m_pt.x - 25 < client.left) {
			m_dx = -m_dx;
		}
		m_pt.x = m_pt.x + m_dx;
		m_pt.y = m_pt.y + m_dy;

		Invalidate();
	}

	CWnd::OnTimer(nIDEvent);
}


void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case VK_UP:
		m_dx = 0;
		m_dy = -10;
		break;
	case VK_LEFT:
		m_dx = -10;
		m_dy = 0;
		break;
	case VK_RIGHT:
		m_dx = 10;
		m_dy = 0;
		break;
	case VK_DOWN:
		m_dx = 0;
		m_dy = 10;
		break;
	}
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return true;
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	click_pt = point;

	m_dx = (point.x - m_pt.x) * 0.1f;
	m_dy = (point.y - m_pt.y) * 0.1f;

	CWnd::OnLButtonDown(nFlags, point);
}

