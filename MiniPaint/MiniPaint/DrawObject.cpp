#include "stdafx.h"
#include "DrawObject.h"

DrawObject::DrawObject(HPEN hPen)
{
	endDrawing = false;
	this->hPen = hPen;
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
