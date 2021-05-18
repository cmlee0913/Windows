#include "pch.h"
#include "CCircle.h"

CCircle::CCircle() {

}

CCircle::CCircle(CPoint Start_point, CPoint End_point, int Color) {
	color = Color;
	start_point = Start_point;
	end_point = End_point;
}

CCircle::~CCircle() {

}

void CCircle::Draw(CDC* dc, CDC* memDC, CDC* bitDC) {
	CRect rect(start_point, end_point);
	CBrush Red(RGB(255, 0, 0));
	CBrush Green(RGB(0, 255, 0));
	CBrush Blue(RGB(0, 0, 255));

	switch (color) {
	case 0:
		memDC->SelectObject(&Red);
		break;

	case 1:
		memDC->SelectObject(&Green);
		break;

	case 2:
		memDC->SelectObject(&Blue);
		break;
	}
	memDC->Ellipse(rect);
}

