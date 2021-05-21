#pragma once
#include "pch.h"
#include "CShape.h"

class Eraser : public CShape
{
public:
	Eraser(CPoint startPos, CPoint endPos);
	Eraser();
	~Eraser();
	CPoint startPos, endPos;
	CRect eraser;
	void drawEraser(CDC* memDC);
	void eraseList(CList <CShape*>* s_list, COLORREF M_color);
};

