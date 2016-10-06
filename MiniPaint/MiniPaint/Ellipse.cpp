#include "stdafx.h"
#include "Ellipse.h"

using namespace MiniPaint;

Ellipse::Ellipse(HPEN hPen, HBRUSH hBrush) : DrawObject(hPen, hBrush)
{
	countDots = 2;
}

void Ellipse::Draw(HDC hdc)
{
	HGDIOBJ prevPen = SelectObject(hdc, hPen);
	HGDIOBJ prevBrush = SelectObject(hdc, hBrush);
	::Ellipse(hdc, dots[0].x, dots[0].y, dots[1].x, dots[1].y);
	SelectObject(hdc, prevPen);
	SelectObject(hdc, prevBrush);
}
