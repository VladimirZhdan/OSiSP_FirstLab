#include "stdafx.h"
#include "PolygonalLine.h"

using namespace MiniPaint;

PolygonalLine::PolygonalLine(int thickness, COLORREF colorPen, COLORREF colorBrush) : DrawObject(thickness, colorPen, colorBrush)
{
	countDots = 2;
}

void PolygonalLine::Draw(HDC hdc)
{
	HGDIOBJ prevPen = SelectObject(hdc, hPen);
	HGDIOBJ prevBrush = SelectObject(hdc, hBrush);
	for (int i = 0; i < countDots - 1; i++)
	{
		MoveToEx(hdc, dots[i].x, dots[i].y, NULL);
		LineTo(hdc, dots[i + 1].x, dots[i + 1].y);
	}
	SelectObject(hdc, prevPen);
	SelectObject(hdc, prevBrush);
}

void PolygonalLine::AddExtraDot()
{
	dots.push_back(dots[countDots - 1]);
	countDots++;	
}
