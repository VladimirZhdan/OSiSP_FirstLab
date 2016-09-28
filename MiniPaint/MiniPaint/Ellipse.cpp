#include "stdafx.h"
#include "Ellipse.h"

using namespace MiniPaint;

Ellipse::Ellipse(HPEN hPen) : DrawObject(hPen)
{
	countDots = 2;
}

void Ellipse::Draw(HDC hdc)
{
	//SelectObject(hdc, hPen);
	::Ellipse(hdc, dots[0].x, dots[0].y, dots[1].x, dots[1].y);
}
