#include "stdafx.h"
#include "DrawingShapes.h"

void DrawingShapes::StartDrawing(Shape *shape)
{
	if (shape != NULL)
	{
		endDrawing = false;
		currentShape = shape;		
	}
}

void DrawingShapes::Drawing(POINT point)
{
	if (!endDrawing)
	{
		currentShape->AddDot(point);
		if (currentShape->isEndDrawing())
		{
			shapes.push_back(currentShape);			
			///ADD CODE
			endDrawing = true;
		}
	}

}



void DrawingShapes::DrawingAllShapes(HDC hdc)
{
	//Clear Window
	for (int i = 0; i < shapes.size(); i++)
		shapes[i]->Draw(hdc);	
}
