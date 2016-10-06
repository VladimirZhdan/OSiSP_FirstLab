#include "stdafx.h"
#include "DrawObject.h"

DrawObject::DrawObject(HPEN hPen, HBRUSH hBrush)
{
	endDrawing = false;
	this->hPen = hPen;
	this->hBrush = hBrush;
}

void DrawObject::AddDot(POINT point)
{				
	if (dots.size() == countDots && (!endDrawing))
	{
		endDrawing = true;		
	}

	if (!endDrawing)
	{
		dots.push_back(point);
	}
}

void DrawObject::ChangeIntermediateOrAddNewDot(POINT point)
{
	int currentDotsCount = dots.size();
	if (currentDotsCount == 1)
	{
		dots.push_back(point);
	}
	else
	{
		dots[currentDotsCount - 1] = point;
	}	
}

bool DrawObject::isEndDrawing()
{
	return endDrawing;
}

void DrawObject::AddExtraDot()
{

}

void DrawObject::AddInformation(TCHAR inf)
{

}

RECT* DrawObject::GetRect()
{
	RECT* result = new RECT();
	POINT first, last;
	int size = dots.size();
	first = dots[0];
	last = dots[size - 1];
	result->left = min(first.x, last.x);
	result->right = max(first.x, last.x);
	result->top = min(first.y, last.y);
	result->bottom = max(first.y, last.y);
	return result;
}

void DrawObject::ChangeCoordinates(int deltaX, int deltaY)
{
	for (int i = 0; i < dots.size(); i++) {
		dots[i].x += deltaX;
		dots[i].y += deltaY;
	}
}

