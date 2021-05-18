#include "pch.h"
#include "CLine.h"


CLine::CLine() {

}

CLine::CLine(CPoint start_Pos, CPoint end_Pos) {
	Start_Pos = start_Pos;
	End_Pos = end_Pos;
}

CLine::~CLine() {

}

void CLine::Draw(CDC* memDC) {

	MoveToEx(*memDC, Start_Pos.x, Start_Pos.y, NULL); // ÇÙ½É 2

	LineTo(*memDC, End_Pos.x, End_Pos.y);
}