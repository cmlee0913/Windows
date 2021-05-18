#pragma once
#include "resource.h" 

class CShape
{
public:
	virtual void Draw(CDC* memDC);

public:
	CShape();
	~CShape();
};

