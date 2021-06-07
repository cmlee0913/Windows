
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "B577030_Homework_3.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	draw_point = CPoint(0, 0);
	l_click = false;
	r_click = false;
	timer_on = false;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(101, clear_buttonClicked)
	ON_BN_CLICKED(102, save_buttonClicked)
	ON_BN_CLICKED(103, load_buttonClicked)
	ON_BN_CLICKED(104, replay_buttonClicked)
	ON_BN_CLICKED(105, stop_buttonClicked)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_HSCROLL()
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

	POSITION pos1 = s_list.GetHeadPosition();
	POSITION pos2 = l_list.GetHeadPosition();

	if (l_click) {
		s_list.AddTail(new CShape(past_point, draw_point, Quadrangle));
		l_list.AddTail(new Line(past_point, draw_point));
	}
	else if (r_click) {
		s_list.AddTail(new CShape(past_point, draw_point, Circle));
		l_list.AddTail(new Line(past_point, draw_point));
	}

	m_HBar.SetScrollRange(0, s_list.GetSize() - 1);


	while (pos2 != NULL) {
		Line* value = l_list.GetNext(pos2);		// pos 위치의 데이터 반환 후, pos는 list의 다음 위치를 가르킴
		value->Draw(&memDC);
	}
	if (!timer_on) {
		while (pos1 != NULL) {
			CShape* value = s_list.GetNext(pos1);		// pos 위치의 데이터 반환 후, pos는 list의 다음 위치를 가르킴
			value->Draw(&memDC);
		}
	}
	else if (timer_on) {
		memDC.RoundRect(replay_point.x - 40, replay_point.y - 40, replay_point.x + 40, replay_point.y + 40, 0, 0);
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
	past_point = draw_point;
	draw_point = point;
	Invalidate();

	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	l_click = false;
	Invalidate();

	CWnd::OnLButtonUp(nFlags, point);
}

void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	r_click = true;
	past_point = draw_point;
	draw_point = point;
	Invalidate();

	CWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	r_click = false;
	Invalidate();

	CWnd::OnRButtonUp(nFlags, point);
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	clear_button.Create(_T("CLEAR"), // Caption 문자열 
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,// 윈도우/버튼 style 
		CRect(0, 0, 100, 30), // 크기와 위치 
		this, // 부모 윈도우
		101); // ID

	save_button.Create(_T("SAVE"), // Caption 문자열 
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,// 윈도우/버튼 style 
		CRect(100, 0, 200, 30), // 크기와 위치 
		this, // 부모 윈도우
		102); // ID

	load_button.Create(_T("LOAD"), // Caption 문자열 
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,// 윈도우/버튼 style 
		CRect(200, 0, 300, 30), // 크기와 위치 
		this, // 부모 윈도우
		103); // ID

	replay_button.Create(_T("REPLAY"), // Caption 문자열 
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,// 윈도우/버튼 style 
		CRect(300, 0, 400, 30), // 크기와 위치 
		this, // 부모 윈도우
		104); // ID

	stop_button.Create(_T("STOP"), // Caption 문자열 
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,// 윈도우/버튼 style 
		CRect(400, 0, 500, 30), // 크기와 위치 
		this, // 부모 윈도우
		105); // ID

	m_HBar.Create(SBS_HORZ, CRect(500, 0, 900, 30), this, 106);
	m_HBar.ShowWindow(true);
	m_HBar.SetScrollPos(0);

	return 0;
}

void CChildView::clear_buttonClicked()
{
	s_list.RemoveAll();
	l_list.RemoveAll();
	draw_point = CPoint(0, 0);
	Invalidate();
}

void CChildView::save_buttonClicked()
{
	CFile file(_T("Save.dat"), CFile::modeWrite | CFile::modeCreate);

	CArchive ar(&file, CArchive::store);

	s_list.Serialize(ar);
	l_list.Serialize(ar);
}

void CChildView::load_buttonClicked()
{
	CFile file(_T("Save.dat"), CFile::modeRead);
	CArchive ar(&file, CArchive::load);

	s_list.RemoveAll();
	s_list.Serialize(ar);
	l_list.RemoveAll();
	l_list.Serialize(ar);

	Invalidate();
}

void CChildView::replay_buttonClicked()
{
	replay_point = s_list.GetHead()->draw_point;
	Line::dots = true;
	timer_on = true;
	if (timer_on) {
		SetTimer(0, 10, NULL);
	}
	Invalidate();
}

void CChildView::stop_buttonClicked()
{
	Line::dots = false;
	timer_on = false;
	if (!timer_on) {
		KillTimer(0);
	}
	replay_point = s_list.GetHead()->draw_point;
	Invalidate();
}

void CChildView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{ // Scroll bar의 box 위치 업데이트
	int nScrollPos;
	CPen redPen, * oldpen;
	redPen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));

	
	if (nSBCode == SB_THUMBTRACK || nSBCode == SB_THUMBPOSITION) {
		pScrollBar->SetScrollPos(nPos);
		CShape* shape = s_list.GetAt(s_list.FindIndex(nPos));
			//if (shape->s_type == Quadrangle) {
			//	oldpen = dc.SelectObject(&redPen);
			//	dc.Rectangle(shape->draw_point.x - 40, shape->draw_point.y - 40, shape->draw_point.x + 40, shape->draw_point.y + 40);
			//	dc.SelectObject(oldpen);
			//}
			//else if (shape->s_type == Circle) {
			//	oldpen = dc.SelectObject(&redPen);
			//	dc.Ellipse(shape->draw_point.x - 40, shape->draw_point.y - 40, shape->draw_point.x + 40, shape->draw_point.y + 40);
			//	dc.SelectObject(oldpen);
			//}
		this->Invalidate();
	}

	switch (nSBCode)
	{
	case SB_LINELEFT:
		nScrollPos = pScrollBar->GetScrollPos();
		if (nScrollPos > 0)
		{
			pScrollBar->SetScrollPos(--nScrollPos);
			this->Invalidate();
		}
		break;
	case SB_LINERIGHT:
		nScrollPos = pScrollBar->GetScrollPos();
		if (nScrollPos < s_list.GetSize() - 1)
		{
			pScrollBar->SetScrollPos(++nScrollPos);
			this->Invalidate();
		}
	} 
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{

	return true;
}



void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 0)
	{
		CPoint start_point = s_list.GetAt(s_list.FindIndex(index))->draw_point;
		CPoint next_point = s_list.GetAt(s_list.FindIndex(index + 1))->draw_point;
		replay_point.x += (float)(next_point.x - start_point.x) * 0.01;
		replay_point.y += (float)(next_point.y - start_point.y) * 0.01;
		Invalidate();
		if (replay_point == next_point) {
			index++;
		}
	}

	CWnd::OnTimer(nIDEvent);
}

