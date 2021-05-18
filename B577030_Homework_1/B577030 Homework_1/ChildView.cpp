#include "pch.h"
#include "framework.h"
#include "B577030 Homework_1.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CChildView::CChildView() // 변수 할당
{
	LUse = false;
	RUse = false;

	Circle = new CCircle * [100];
	for (int i = 0; i < 100; i++) {
		Circle[i] = { NULL };
	}
	Rectangle = new CRectangle * [100];
	for (int i = 0; i < 100; i++) {
		Rectangle[i] = { NULL };
	}
}

CChildView::~CChildView() // 메모리 해제
{
	for (int i = 0; i < 100; i++) {
		delete[] Circle[i];
	}
	delete[] Circle;
	for (int i = 0; i < 100; i++) {
		delete[] Rectangle[i];
	}
	delete[] Rectangle;
}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_MBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

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

	// 기억한 도형들 그리기

	if (CircleCounter > 0) {
		for (int i = 0; i < CircleCounter; i++) {
			Circle[i]->Draw(&dc, &memDC, &bitDC);
		}
	}

	if (RectCounter > 0) {
		for (int i = 0; i < RectCounter; i++) {
			Rectangle[i]->Draw(&dc, &memDC, &bitDC);
		}
	}

	// 도형 새로 그리기 

	if (LUse == true) {
		Circle[CircleCounter] = new CCircle(L_Start_Pos, L_End_Pos, Color);

		Circle[CircleCounter]->Draw(&dc, &memDC, &bitDC);
	}

	if (RUse == true) {
		Rectangle[RectCounter] = new CRectangle(R_Start_Pos, R_End_Pos, Color);

		Rectangle[RectCounter]->Draw(&dc, &memDC, &bitDC);
	}
	
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

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	LUse = true;
	L_Start_Pos = point;
	Invalidate();
	CWnd::OnLButtonDown(nFlags, point);
} 

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (LUse == true) {
		LUse = false;
	}
	CircleCounter++;
	Invalidate();
	CWnd::OnLButtonUp(nFlags, point);
}

void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	R_Start_Pos = point;
	RUse = true;
	Invalidate();
	CWnd::OnRButtonDown(nFlags, point);
}

void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (RUse == true) {
		RUse = false;
	}

	RectCounter++;
	Invalidate();
	CWnd::OnRButtonUp(nFlags, point);
}

void CChildView::OnMButtonDown(UINT nFlags, CPoint point)
{

	CWnd::OnMButtonDown(nFlags, point);
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{

	if (LUse == true || RUse == true) {
		Invalidate();
		L_End_Pos = point;
		R_End_Pos = point;
	}

	CWnd::OnMouseMove(nFlags, point);
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	/*return CWnd::OnEraseBkgnd(pDC);*/
	return false;
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

	Circle[CircleCounter - 1] = new CCircle(L_Start_Pos, L_End_Pos, Color); //2번
	Invalidate();
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
