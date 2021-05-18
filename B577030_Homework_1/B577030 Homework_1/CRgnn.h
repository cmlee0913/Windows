#pragma once
#include "CShape.h"

class CRgnn : public CShape {
public:
	CPoint* point;
	int num;
	virtual void Draw(CDC* dc, CDC* memDC, CDC* bitDC) override;

public:
	CRgnn(CPoint* Point, int Num);
	CRgnn();
	~CRgnn();
};

