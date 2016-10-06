#include "stdafx.h"
#include "Pencil.h"

using namespace MiniPaint;

Pencil::Pencil(HPEN hPen, HBRUSH hBrush) : DrawObject(hPen, hBrush)
{
	countDots = 2;//more!!!
}

void Pencil::Draw(HDC hdc)
{
	HGDIOBJ prevPen = SelectObject(hdc, hPen);
	HGDIOBJ prevBrush = SelectObject(hdc, hBrush);
	for (int i = 0; i < countDots - 1; i++)
	{
		MoveToEx(hdc, dots[i].x, dots[i].y, NULL);
		LineTo(hdc, dots[i + 1].x, dots[i + 1].y);
	}
	if (!endDrawing)
	{		
		dots.push_back(dots[countDots - 1]);
		countDots++;
	}	
	SelectObject(hdc, prevPen);
	SelectObject(hdc, prevBrush);
}