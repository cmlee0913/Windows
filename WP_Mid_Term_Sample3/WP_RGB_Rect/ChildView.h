
// ChildView.h: CChildView 클래스의 인터페이스
//
#include "CRectangle.h"

#pragma once


// CChildView 창

class CChildView : public CWnd, CRectangle
{
// 생성입니다.
public:
	CChildView();
	bool LUse;
	CPoint L_Start_Pos, L_End_Pos;
	CRectangle** Rectangle;
	int rectangleCounter = 0;
	CDC memDC;
	int Color = 0;

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

