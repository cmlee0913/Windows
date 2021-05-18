
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "WP_Timer.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_pt = CPoint(100, 100);
	m_dy = 10;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_TIMER()
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
	dc.Ellipse(m_pt.x, m_pt.y, m_pt.x + 50, m_pt.y + 50);
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
	if (nIDEvent == 0) {
		CRect client;
		GetClientRect(&client);
		if (m_pt.y + 50 > client.bottom) {
			m_dy = -m_dy;
		}
		if (m_pt.y < 0) {
			m_dy = -m_dy;
		}
		m_pt.y = m_pt.y + m_dy;
		
		Invalidate();
	}

	CWnd::OnTimer(nIDEvent);
}
