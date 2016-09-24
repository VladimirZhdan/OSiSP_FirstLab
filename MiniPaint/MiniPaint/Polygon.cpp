#include "stdafx.h"
#include "Polygon.h"

using namespace MiniPaint;

Polygon::Polygon()
{
	countDots = 2;

}

void Polygon::Draw(HDC hdc)
{
	for (int i = 0; i < countDots - 1; i++)
	{
		MoveToEx(hdc, dots[i].x, dots[i].y, NULL);
		LineTo(hdc, dots[i + 1].x, dots[i + 1].y);
	}
	MoveToEx(hdc, dots[countDots - 1].x, dots[countDots - 1].y, NULL);
	LineTo(hdc, dots[0].x, dots[0].y);
}

void Polygon::AddExtraDot()
{
	dots.push_back(dots[countDots - 1]);
	countDots++;
}