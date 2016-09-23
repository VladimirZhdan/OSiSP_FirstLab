#include "stdafx.h"
#include "Shape.h"

Shape::Shape()
{
	endDrawing = false;
}

void Shape::AddDot(POINT point)
{
	dots.push_back(point);
	if (dots.size() == countDots && (!endDrawing))
	{
		endDrawing = true;
		EndCreateShape();
	}
}

bool Shape::isEndDrawing()
{
	return endDrawing;
}

void Shape::EndCreateShape()
{

}
