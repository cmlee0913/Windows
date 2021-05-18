#pragma once
class CLine
{
public:
	CPoint Start_Pos, End_Pos;
	CLine();
	CLine(CPoint start_Pos, CPoint end_Pos);
	~CLine();
	void Draw(CDC* dc);
};

