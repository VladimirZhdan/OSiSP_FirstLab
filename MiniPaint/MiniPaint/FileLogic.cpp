#include "stdafx.h"
#include "FileLogic.h"
#include "DrawingShapes.h"

bool FileLogic::SaveAsEnhancedFile(HWND hWnd, TCHAR fileName[])
{
	HDC hdcRef = GetDC(hWnd);
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
	HDC hdcMeta;
	hdcMeta = CreateEnhMetaFile(hdcRef, (LPTSTR)fileName, NULL, NULL);
	if (hdcMeta)
	{
		FillRect(hdcMeta, &clientRect, CreateSolidBrush(RGB(255, 255, 255)));
		DrawingShapes* drawingShapes = DrawingShapes::getInstance();
		drawingShapes->RedrawAllShapes(hdcMeta);
		HENHMETAFILE hEmf = CloseEnhMetaFile(hdcMeta);
		DeleteEnhMetaFile(hEmf);
		ReleaseDC(hWnd, hdcRef);
		return true;
	}
	else
		return false;			
}

bool FileLogic::OpenEnhancedFile(HENHMETAFILE *hEnhMetaFile, TCHAR fileName[])
{
	HENHMETAFILE hEmf = GetEnhMetaFile((LPTSTR)fileName);
	if (hEmf)
	{
		*hEnhMetaFile = hEmf;
		return true;
	}
	else
		return false;

	
}