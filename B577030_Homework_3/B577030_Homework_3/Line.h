#pragma once
class Line
{
public:
	Line(CPoint past_point, CPoint draw_point);
	~Line();
	CPoint draw_point, past_point;
	void Draw(CDC* memDC);
	static bool dots;
};

