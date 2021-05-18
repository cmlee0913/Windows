#pragma once
#include "CShape.h"

class CCircle : public CShape {
public:
	int color;
	CPoint start_point;
	CPoint end_point;
	virtual void Draw(CDC* dc, CDC* memDC, CDC* bitDC) override;

public:
	CCircle(CPoint start_point, CPoint end_point, int Color);
	CCircle();
	~CCircle();
};

