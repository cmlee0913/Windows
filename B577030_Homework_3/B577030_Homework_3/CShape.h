#pragma once

enum Type {
	Quadrangle,
	Circle
};

class CShape
{
public:
	CShape(CPoint past_point, CPoint draw_point, enum Type s_type);
	CShape(bool select);
	~CShape();
	CPoint draw_point, past_point;
	bool isSelect = false;
	enum Type s_type;
	void Draw(CDC* memDC);
};

