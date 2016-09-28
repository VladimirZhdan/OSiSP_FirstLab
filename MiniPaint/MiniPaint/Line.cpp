#include "stdafx.h"
#include "Line.h"

using namespace MiniPaint;

Line::Line(HPEN hPen) : DrawObject(hPen)
{
	countDots = 2;
}

void Line::Draw(HDC hdc)
{
	COLORREF color = RGB(255, 0, 0);
	HPEN hPen = CreatePen(PS_SOLID, 3, color);
	HGDIOBJ hPenOld = (HPEN)SelectObject(hdc, hPen);
	
	MoveToEx(hdc, dots[0].x, dots[0].y, NULL);
	LineTo(hdc, dots[1].x, dots[1].y);	
	SelectObject(hdc, hPenOld);
}