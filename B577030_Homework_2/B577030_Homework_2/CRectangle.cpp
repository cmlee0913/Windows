#include "pch.h"
#include "CRectangle.h"

CRectangle::CRectangle() {

}

CRectangle::CRectangle(CPoint D_point, COLORREF M_color) {
	d_point = D_point;
	m_color = M_color;
}

CRectangle::~CRectangle() {

}

void CRectangle::Draw(CDC* memDC) {
	CBrush brush(m_color);
	memDC->SelectObject(&brush);

	memDC->Rectangle(d_point.x - 5, d_point.y - 5, d_point.x + 5, d_point.y + 5);
}