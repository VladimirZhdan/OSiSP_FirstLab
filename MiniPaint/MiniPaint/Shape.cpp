#include "stdafx.h"
#include "Shape.h"

Shape::Shape()
{
	endDrawing = false;
}

void Shape::AddDot(POINT point)
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

void Shape::ChangeIntermediateOrAddNewDot(POINT point)
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

bool Shape::isEndDrawing()
{
	return endDrawing;
}

void Shape::AddExtraDot()
{

}
