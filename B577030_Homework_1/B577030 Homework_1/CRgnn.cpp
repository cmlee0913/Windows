#include "pch.h"
#include "CRgnn.h"

CRgnn::CRgnn() {

}

CRgnn::CRgnn(CPoint* Point, int Num) {
	point = Point;
	num = Num;
}

CRgnn::~CRgnn() {

}

void CRgnn::Draw(CDC* dc, CDC* memDC, CDC* bitDC) {
	CRgn rgn;
	rgn.CreatePolygonRgn(point, num, ALTERNATE);

	CBrush brush(RGB(0, 255, 0));
	memDC->SelectObject(&brush);
	memDC->PaintRgn(&rgn);
}
