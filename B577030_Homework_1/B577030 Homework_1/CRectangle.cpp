#include "pch.h"
#include "CRectangle.h"

CRectangle::CRectangle() {
	
}

CRectangle::CRectangle(CPoint Start_point, CPoint End_point, int Color) {
	color = Color;
	start_point = Start_point;
	end_point = End_point;
}

CRectangle::~CRectangle() {

}

void CRectangle::Draw(CDC* dc, CDC* memDC, CDC* bitDC) {
	CRect rect(start_point, end_point);

	CBitmap bitmap;
	BITMAP bmpinfo;

	bitmap.LoadBitmap(IDB_BITMAP1);
	bitmap.GetBitmap(&bmpinfo);

	memDC->StretchBlt(start_point.x, start_point.y,
		end_point.x - start_point.x,
		end_point.y - start_point.y,
		bitDC, 0, 0,
		bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
}