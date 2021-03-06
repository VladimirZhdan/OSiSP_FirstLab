#include "stdafx.h"
#include "Line.h"

using namespace MiniPaint;

Line::Line(int thickness, COLORREF colorPen, COLORREF colorBrush) : DrawObject(thickness, colorPen, colorBrush)
{
	countDots = 2;
}

void Line::Draw(HDC hdc)
{
	HGDIOBJ prevPen = SelectObject(hdc, hPen);
	HGDIOBJ prevBrush = SelectObject(hdc, hBrush);
	MoveToEx(hdc, dots[0].x, dots[0].y, NULL);
	LineTo(hdc, dots[1].x, dots[1].y);	
	SelectObject(hdc, prevPen);
	SelectObject(hdc, prevBrush);
}