#pragma once
class CRectangle
{
public:
	CPoint L_Start, L_End;
	int Color;
	CRectangle();
	CRectangle(CPoint L_Start_Pos, CPoint L_End_Pos, int Color);
	~CRectangle();
	void Draw(CDC* dc, CDC* memDC);
};

