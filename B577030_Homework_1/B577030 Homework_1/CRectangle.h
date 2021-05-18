#pragma once
#include "CShape.h"

class CRectangle : public CShape {
public:
	int color;
	CPoint start_point;
	CPoint end_point;
	virtual void Draw(CDC* dc, CDC* memDC, CDC* bitDC) override;

public:
	CRectangle(CPoint start_point, CPoint end_point, int Color);
	CRectangle();
	~CRectangle();
};


