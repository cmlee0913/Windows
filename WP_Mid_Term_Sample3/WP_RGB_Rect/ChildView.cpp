
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "WP_RGB_Rect.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	LUse = false;
	Rectangle = new CRectangle * [100];
	for (int i = 0; i < 100; i++) {
		Rectangle[i] = { NULL };
	}
}

CChildView::~CChildView()
{
	for (int i = 0; i < 100; i++) {
		Rectangle[i] = { NULL };
		delete[] Rectangle[i];
	}
	delete[] Rectangle;
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
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

	if (rectangleCounter > 0) {
		for (int i = 0; i < rectangleCounter; i++) {
			Rectangle[i]->Draw(&dc, &memDC);
		}
	}

	if (LUse == true) {
		Rectangle[rectangleCounter] = new CRectangle(L_Start_Pos, L_End_Pos, Color); // 3번
		Rectangle[rectangleCounter]->Draw(&dc, &memDC);

		dc.BitBlt(0, 0,
			clientRect.Width(), clientRect.Height(),
			&memDC,
			0, 0,
			SRCCOPY);
	}
	int b = 10;
	int* a = &b;

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
	LUse = true;
	L_Start_Pos = point;

	__super::OnLButtonDown(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (LUse == true) { //1번
		Invalidate();
		L_End_Pos = point;
	}
	
	__super::OnMouseMove(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (LUse == true) {
		LUse = false;
	}
	L_End_Pos = point;

	rectangleCounter++;
	Invalidate();
	__super::OnLButtonUp(nFlags, point);
}




void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
	if (nChar == 82) {
		Color = 0;
	}
	else if (nChar == 71) {
		Color = 1;
	}
	else if (nChar == 66) {
		Color = 2;
	}

	Rectangle[rectangleCounter-1] = new CRectangle(L_Start_Pos, L_End_Pos, Color); //2번
	Invalidate();
	__super::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return true;
}
