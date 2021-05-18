#include "pch.h"
#include "CRectangle.h"

CRectangle::CRectangle() {
	Color = 0;
}

CRectangle::CRectangle(CPoint L_Start_Pos, CPoint L_End_Pos, int color) {
	Color = color;
	L_Start = L_Start_Pos;
	L_End = L_End_Pos;
}

CRectangle::~CRectangle() {

}

void CRectangle::Draw(CDC* dc, CDC* memDC) {

	CRect rect(L_Start, L_End);
	CBrush Red(RGB(255, 0, 0));
	CBrush Green(RGB(0, 255, 0)); // 4¹ø
	CBrush Blue(RGB(0, 0, 255));

	switch (Color) {
	case 0:
		memDC->SelectObject(&Red);
		break; 

	case 1:
		memDC->SelectObject(&Green);
		break; 

	case 2:
		memDC->SelectObject(&Blue);
		break; }
	
	memDC->Rectangle(rect);
}

