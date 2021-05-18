#include "pch.h"
#include "CCircle.h"

CCircle::CCircle() {

}

CCircle::CCircle(CPoint D_point, COLORREF M_color) {
	d_point = D_point;
	m_color = M_color;
}

CCircle::~CCircle() {

}

void CCircle::Draw(CDC* memDC) {
	CBrush brush(m_color);
	memDC->SelectObject(&brush);

	memDC->Ellipse(d_point.x - 5, d_point.y - 5, d_point.x + 5, d_point.y + 5);
}