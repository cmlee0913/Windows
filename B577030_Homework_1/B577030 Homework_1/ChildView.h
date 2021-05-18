
// ChildView.h: CChildView 클래스의 인터페이스
//
#pragma once
#include "CCircle.h"
#include "CRectangle.h"
#include "CRgnn.h"
#include "CShape.h"
// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();
	bool LUse, RUse;
	CPoint L_Start_Pos, L_End_Pos, R_Start_Pos, R_End_Pos;
	CCircle** Circle;
	CRectangle** Rectangle;
	int CircleCounter = 0;
	int RectCounter = 0;
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
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

