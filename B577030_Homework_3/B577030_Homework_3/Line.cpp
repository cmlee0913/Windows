#include "pch.h"
#include "Line.h"

bool Line::dots = false;

Line::Line(CPoint p_point, CPoint point) {
	past_point = p_point;
	draw_point = point;
}

Line::~Line() {

}

void Line::Draw(CDC* memDC) {

	if (past_point != CPoint(0, 0)) {
		if (Line::dots == true) {
			CPen pen(PS_DOT, 1, RGB(0, 0, 0));
			CPen* oldpen = memDC->SelectObject(&pen);
			memDC->MoveTo(past_point);
			memDC->LineTo(draw_point);
			memDC->SelectObject(oldpen);
		}
		else if (Line::dots == false) {
			memDC->MoveTo(past_point);
			memDC->LineTo(draw_point);
		}
	}
}