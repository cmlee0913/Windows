#pragma once
#include "CShape.h"

class CCircle : public CShape
{
public:
	virtual void Draw(CDC* memDC);

public:
	CCircle(CPoint D_point, COLORREF M_color);
	CCircle();
	~CCircle();
};

