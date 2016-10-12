#include "stdafx.h"
#include "DrawingShapes.h"

DrawingShapes* DrawingShapes::instance = new DrawingShapes();

DrawingShapes::DrawingShapes()
{

}

void DrawingShapes::InitInstance(HWND hWnd)
{
	instance->hWnd = hWnd;
	instance->zoom = 1;
}

DrawingShapes* DrawingShapes::getInstance()
{
	if (instance->hWnd != NULL)
		return instance;
	else
		return NULL;
}

DrawingShapes::~DrawingShapes()
{
	for (int i = shapes.size() - 1; i >= 0; i--)
	{
		delete shapes[i];
		shapes.pop_back();
	}
	if (!endDrawing && (currentShape != NULL))
	{
		delete currentShape;
	}
}

void DrawingShapes::StartDrawing(DrawObject *shape)
{
	if (!endDrawing)
	{
		endDrawing = true;
		shapes.push_back(currentShape);
	}
		
	if (shape != NULL)
	{		
		currentShape = shape;		
	}
}

void DrawingShapes::AddDot(POINT point)
{		
	point.x /= this->zoom;
	point.y /= this->zoom;
	if (currentShape != NULL)
	{
		if (endDrawing)
		{
			endDrawing = false;
		}
		currentShape->AddDot(point);
		if (currentShape->isEndDrawing())
		{
			shapes.push_back(currentShape);
			endDrawing = true;
		}
	}
}

void DrawingShapes::AddExtraDot()
{
	currentShape->AddExtraDot();
}

void DrawingShapes::AddInformation(TCHAR inf)
{
	currentShape->AddInformation(inf);
}

void DrawingShapes::Drawing(POINT point)
{	
	point.x = point.x / this->zoom;
	point.y = point.y / this->zoom;
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
	clientRect.right /= this->zoom;
	clientRect.bottom /= this->zoom;
	int windowWidth = clientRect.right - clientRect.left;
	int windowHeight = clientRect.bottom - clientRect.top;
	PAINTSTRUCT paintStruct;
	HDC hdc = BeginPaint(hWnd, &paintStruct);
	HDC bufferHDC = CreateCompatibleDC(hdc);	
	HBITMAP bitmap = CreateCompatibleBitmap(hdc, windowWidth, windowHeight);
	__try
	{		
		HGDIOBJ oldBitmap = SelectObject(bufferHDC, bitmap);
		FillRect(bufferHDC, &clientRect, (HBRUSH)WHITE_BRUSH);

		//
		//draw to buffer
		//
		RedrawAllShapes(bufferHDC, &clientRect);
		if (!endDrawing)
		{
			currentShape->ChangeIntermediateOrAddNewDot(point);
			currentShape->Draw(bufferHDC);
		}		

		//zoom logic
		if (this->zoom != 1)
		{
			XFORM xForm;
			xForm.eM11 = xForm.eM22 = this->zoom;
			xForm.eM12 = xForm.eM21 = xForm.eDx = xForm.eDy = 0;
			SetGraphicsMode(hdc, GM_ADVANCED);
			SetWorldTransform(hdc, &xForm);
		}

		BitBlt(hdc, 0, 0, windowWidth, windowHeight, bufferHDC, 0, 0, SRCCOPY);		
		SelectObject(bufferHDC, oldBitmap);		
	}
	__finally 
	{
		DeleteDC(bufferHDC);
		DeleteObject(bitmap);
		EndPaint(hWnd, &paintStruct);
	}
}

void DrawingShapes::RedrawAllShapes(HDC hdc, RECT *clientRect)
{	
	// Draw from Enhanced MetaFile
	if (hEnhMetaFile != NULL)
	{
		clientRect->right *= this->zoom;
		clientRect->bottom *= this->zoom;
		clientRect->left += this->deltaMetaFileRect.left;
		clientRect->right += this->deltaMetaFileRect.right;
		clientRect->top+= this->deltaMetaFileRect.top;
		clientRect->bottom += this->deltaMetaFileRect.bottom;
		PlayEnhMetaFile(hdc, hEnhMetaFile, clientRect);
	}
	// Draw shapes

	for (int i = 0; i < shapes.size(); i++)
		shapes[i]->Draw(hdc);	
}

bool DrawingShapes::isEndDrawing()
{
	return endDrawing;
}

void DrawingShapes::setMetaFile(HENHMETAFILE hEnhMetaFile)
{
	this->hEnhMetaFile = hEnhMetaFile;
}

void DrawingShapes::DeleteLastShape()
{
	int size = shapes.size();
	if (size > 0)
	{
		delete shapes[size - 1];
		shapes.pop_back();
	}
}

RECT* DrawingShapes::GetRectOfLastObject()
{
	int size = shapes.size();
	if (size > 0)
	{
		return (shapes[size - 1])->GetRect();
	}
	else
		return NULL;
}

void DrawingShapes::ChangeCoordinatesOfDrawObjects(int deltaX, int deltaY)
{
	for (int i = 0; i < shapes.size(); i++)
	{
		shapes[i]->ChangeCoordinates(deltaX / this->zoom, deltaY / this->zoom);		
	}
	this->ChangeCoordinatesOfMetaFileRect(deltaX / this->zoom, deltaY / this->zoom);
}

void DrawingShapes::ChangeCoordinatesOfMetaFileRect(int deltaX, int deltaY)
{
	this->deltaMetaFileRect.left += deltaX;
	this->deltaMetaFileRect.right += deltaX;
	this->deltaMetaFileRect.top += deltaY;
	this->deltaMetaFileRect.bottom += deltaY;
}

void DrawingShapes::Zooming(float zoom)
{
	if (((this->zoom * zoom) <= 64) && ((this->zoom * zoom) >= 0.25))
	{
		this->zoom *= zoom;		
	}
}
		