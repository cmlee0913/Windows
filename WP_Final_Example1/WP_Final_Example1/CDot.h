#pragma once
class CDot
{
public:
	CPoint d_point;
	void Draw(CDC* memDC);
public:
	CDot(CPoint point);
	~CDot();
};

