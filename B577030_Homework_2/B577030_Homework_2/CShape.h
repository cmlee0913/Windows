#pragma once
#include "resource.h" 

class CShape
{
public:
	CPoint d_point;
	COLORREF m_color;
	virtual void Draw(CDC* memDC);

public:
	CShape();
	~CShape();
};

