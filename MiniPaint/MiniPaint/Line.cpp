#include "stdafx.h"
#include "Line.h"

Line::Line()
{
	countDots = 2;
}

void Line::Draw(HDC hdc)
{
	MoveToEx(hdc, dots[0].x, dots[0].y, NULL);
	LineTo(hdc, dots[1].x, dots[1].y);
}