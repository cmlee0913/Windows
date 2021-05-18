
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "B577030_Homework_2.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	draw_point = CPoint(-5, -5);
	m_color = RGB(0, 0, 0);
	m_bDrawCir = false;
	m_bDrawRect = true;
	l_click = false;
	r_click = false;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_UPDATE_COMMAND_UI(ID_RED, &CChildView::OnUpdateRed)
	ON_UPDATE_COMMAND_UI(ID_GREEN, &CChildView::OnUpdateGreen)
	ON_UPDATE_COMMAND_UI(ID_BLUE, &CChildView::OnUpdateBlue)
	ON_COMMAND(ID_RED, &CChildView::OnRed)
	ON_COMMAND(ID_GREEN, &CChildView::OnGreen)
	ON_COMMAND(ID_BLUE, &CChildView::OnBlue)
	ON_COMMAND(ID_ECLI, &CChildView::OnEcli)
	ON_COMMAND(ID_RECT, &CChildView::OnRect)
	ON_UPDATE_COMMAND_UI(ID_ECLI, &CChildView::OnUpdateEcli)
	ON_UPDATE_COMMAND_UI(ID_RECT, &CChildView::OnUpdateRect)
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_BLACK, &CChildView::OnBlack)
	ON_UPDATE_COMMAND_UI(ID_BLACK, &CChildView::OnUpdateBlack)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
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

	CString sTxt;
	sTxt.Format(_T("%d"), shapecounter);
	TextOut(memDC, 10, 10, sTxt, sTxt.GetLength());

	POSITION pos = s_list.GetHeadPosition();

	while (pos != NULL) {
		CShape* value = s_list.GetNext(pos);		// pos 위치의 데이터 반환 후, pos는 list의 다음 위치를 가르킴
		value->Draw(&memDC);
	}

	if (l_click && m_bDrawCir) {
		s_list.AddTail(new CCircle(draw_point, m_color));
		shapecounter++;
	}

	if (l_click && m_bDrawRect) {
		s_list.AddTail(new CRectangle(draw_point, m_color));
		shapecounter++;
	}

	if (r_click) {
		CRect eraser(erase_start, erase_end);
		memDC.Rectangle(eraser);
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
	Invalidate();

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	Invalidate();
	l_click = false;

	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	r_click = true;
	erase_start = point;
	Invalidate();

	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	Invalidate();
	erase_end = point;
	r_click = false;

	CWnd::OnRButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	draw_point = point;
	erase_end = point;

	if (l_click || r_click) {
		Invalidate();
	}

	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnUpdateRed(CCmdUI* pCmdUI)
{
	if (m_color == RGB(255, 0, 0))
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnUpdateGreen(CCmdUI* pCmdUI)
{
	if (m_color == RGB(0, 255, 0))
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnUpdateBlue(CCmdUI* pCmdUI)
{
	if (m_color == RGB(0, 0, 255))
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnUpdateBlack(CCmdUI* pCmdUI)
{
	if (m_color == RGB(0, 0, 0))
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnUpdateEcli(CCmdUI* pCmdUI)
{
	if (m_bDrawCir)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnUpdateRect(CCmdUI* pCmdUI)
{
	if (m_bDrawRect)
		pCmdUI->SetCheck(true);
	else
		pCmdUI->SetCheck(false);
}


void CChildView::OnRed()
{
	m_color = RGB(255, 0, 0);
}


void CChildView::OnGreen()
{
	m_color = RGB(0, 255, 0);
}


void CChildView::OnBlue()
{
	m_color = RGB(0, 0, 255);
}


void CChildView::OnBlack()
{
	m_color = RGB(0, 0, 0);
}


void CChildView::OnEcli()
{
	m_bDrawRect = false;
	m_bDrawCir = true;
}


void CChildView::OnRect()
{
	m_bDrawRect = true;
	m_bDrawCir = false;
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}


