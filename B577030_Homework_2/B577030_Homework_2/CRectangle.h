#pragma once
#include "CShape.h"

class CRectangle : public CShape
{
public:
	CPoint d_point;
	COLORREF m_color;
	virtual void Draw(CDC* memDC);

public:
	CRectangle(CPoint D_point, COLORREF M_color);
	CRectangle();
	~CRectangle();
};

