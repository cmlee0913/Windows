#pragma once
#include "resource.h" 

class CShape : public CWnd
{
public:
	virtual void Draw(CDC* dc, CDC* memDC, CDC* bitDC) = 0;

public:
	CShape();
	~CShape();
};

