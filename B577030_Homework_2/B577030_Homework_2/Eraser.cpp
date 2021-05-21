#include "pch.h"
#include "Eraser.h"
#include "ChildView.h"

Eraser::Eraser(CPoint StartPos, CPoint EndPos) {
	

	if (StartPos.x < EndPos.x) {
		if (StartPos.y < EndPos.y) {
			startPos = StartPos;
			endPos = EndPos;
		}
		else {
			startPos.x = StartPos.x;
			startPos.y = EndPos.y;
			endPos.x = EndPos.x;
			endPos.y = StartPos.y;
		}
	}

	if (StartPos.x > EndPos.x) {
		if (StartPos.y > EndPos.y) {
			startPos = EndPos;
			endPos = StartPos;
		}
		else {
			startPos.x = EndPos.x;
			startPos.y = StartPos.y;
			endPos.x = StartPos.x;
			endPos.y = EndPos.y;
		}
	}

	eraser = CRect(startPos.x, startPos.y, endPos.x, endPos.y);
}

Eraser::Eraser() {

}

Eraser::~Eraser() {

}

void Eraser::drawEraser(CDC* memDC) {
	CPen pen(0, 3, RGB(255, 100, 0));
	CBrush brush(RGB(255, 255, 255));

	CPen* oldpen = memDC->SelectObject(&pen);
	memDC->SelectObject(&brush);

	memDC->Rectangle(eraser);
	memDC->SelectObject(oldpen);
}

void Eraser::eraseList(CList <CShape*>* s_list, COLORREF M_color) {
	POSITION pos = s_list->GetHeadPosition();
	POSITION nowpos;
	while (pos != NULL) {
		nowpos = pos;
		CShape* value = s_list->GetNext(pos);		// pos 위치의 데이터 반환 후, pos는 list의 다음 위치를 가르킴
		if (eraser.PtInRect(value->d_point) == true) {
			s_list->RemoveAt(nowpos);
			CChildView::shapecounter--;
		}
		else if (eraser.PtInRect(value->d_point) == true) {
			s_list->RemoveAt(nowpos);
			CChildView::shapecounter--;
		}
	}
}