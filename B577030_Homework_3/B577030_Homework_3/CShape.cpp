#include "pch.h"
#include "CShape.h"


CShape::CShape(CPoint p_point, CPoint point, enum Type type) {
	past_point = p_point;
	draw_point = point;
	s_type = type;
}

CShape::CShape(bool select) {
	isSelect = select;
}

CShape::~CShape() {

}

void CShape::Draw(CDC* memDC) {
	if (s_type == Quadrangle) {
		memDC->Rectangle(draw_point.x - 40, draw_point.y - 40, draw_point.x + 40, draw_point.y + 40);
	}
	else if (s_type == Circle) {
		memDC->Ellipse(draw_point.x - 40, draw_point.y - 40, draw_point.x + 40, draw_point.y + 40);
	}
}