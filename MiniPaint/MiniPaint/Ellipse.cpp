#include "stdafx.h"
#include "Ellipse.h"

using namespace MiniPaint;

Ellipse::Ellipse()
{
	countDots = 2;
}

void Ellipse::Draw(HDC hdc)
{
	::Ellipse(hdc, dots[0].x, dots[0].y, dots[1].x, dots[1].y);
}
