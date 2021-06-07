
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once
#include "CShape.h"
#include "Line.h"

// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:
	CPoint draw_point, past_point, replay_point;
	CList <CShape*> s_list;
	CList <Line*> l_list;
	bool l_click, r_click;
	bool timer_on;
	enum Type s_type;
	CButton clear_button, save_button, load_button, replay_button, stop_button;
	CScrollBar m_HBar;
	int index = 0;
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
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void clear_buttonClicked();
	afx_msg void save_buttonClicked();
	afx_msg void load_buttonClicked();
	afx_msg void replay_buttonClicked();
	afx_msg void stop_buttonClicked();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

