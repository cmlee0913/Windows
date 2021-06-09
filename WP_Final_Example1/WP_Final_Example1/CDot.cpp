#include "pch.h"
#include "CDot.h"

CDot::CDot(CPoint point){
	d_point = point;
}

CDot::~CDot() {

}

void CDot::Draw(CDC* memDC) {
	CPen pen(0, 5, RGB(255, 0, 0));
	CPen* oldPen = memDC->SelectObject(&pen);

	memDC->MoveTo(d_point);
	memDC->LineTo(d_point);

	memDC->SelectObject(oldPen);
}