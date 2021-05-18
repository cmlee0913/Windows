#pragma once
#include "CShape.h"

class CCircle : public CShape
{
public:
	CPoint d_point;
	COLORREF m_color;
	virtual void Draw(CDC* memDC);

public:
	CCircle(CPoint D_point, COLORREF M_color);
	CCircle();
	~CCircle();
};

