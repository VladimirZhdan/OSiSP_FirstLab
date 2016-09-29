#include "stdafx.h"
#include "DrawingShapes.h"

DrawingShapes* DrawingShapes::instance = new DrawingShapes();

DrawingShapes::DrawingShapes()
{

}

void DrawingShapes::InitInstance(HWND hWnd)
{
	instance->hWnd = hWnd;
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
}

void DrawingShapes::StartDrawing(DrawObject *shape)
{
	if (shape != NULL)
	{		
		currentShape = shape;		
	}
}

void DrawingShapes::AddDot(POINT point)
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
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
	PAINTSTRUCT paintStruct;
	HDC hdc = BeginPaint(hWnd, &paintStruct);
	HDC bufferHDC = CreateCompatibleDC(hdc);
	int windowWidth = clientRect.right - clientRect.left;
	int windowHeight = clientRect.bottom - clientRect.top;	
	HBITMAP bitmap = CreateCompatibleBitmap(bufferHDC ,windowWidth, windowHeight);
	SelectObject(bufferHDC, bitmap);
	FillRect(bufferHDC, &clientRect, WHITE_BRUSH);
	// Draw from Enhanced MetaFile
	if (hEnhMetaFile != NULL)
	{
		PlayEnhMetaFile(bufferHDC, hEnhMetaFile, &clientRect);
	}		
	//
	//draw to buffer
	//
	RedrawAllShapes(bufferHDC);
	if (!endDrawing)
	{
		currentShape->ChangeIntermediateOrAddNewDot(point);
		currentShape->Draw(bufferHDC);
	}
	BitBlt(hdc, 0, 0, windowWidth, windowHeight, bufferHDC, 0, 0, SRCCOPY);
	EndPaint(hWnd, &paintStruct);
	DeleteDC(bufferHDC);
	DeleteObject(bitmap);	
}

void DrawingShapes::RedrawAllShapes(HDC hdc)
{	
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
