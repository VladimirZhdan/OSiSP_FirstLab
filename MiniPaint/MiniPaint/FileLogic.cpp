#include "stdafx.h"
#include "FileLogic.h"


bool FileLogic::SaveAsEnhancedFile(HWND hWnd, TCHAR fileName[])
{
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);

	return FileLogic::SaveEnhancedFile(hWnd, fileName, &clientRect);
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

bool FileLogic::PrintAsEnhancedFile(HWND hWnd, TCHAR fileName[])
{	
	DrawingShapes* drawingShapes = DrawingShapes::getInstance();
	RECT *clientRect = drawingShapes->GetRectOfLastObject();		
	drawingShapes->DeleteLastShape();

	return FileLogic::SaveEnhancedFile(hWnd, fileName, clientRect);
}

bool FileLogic::SaveEnhancedFile(HWND hWnd, TCHAR fileName[], RECT *clientRect){
	if (clientRect != NULL) {
		HDC hdcRef = GetDC(hWnd);
		HDC hdcMeta;

		int iWidthMM, iHeightMM, iWidthPels, iHeightPels;
		iWidthMM = GetDeviceCaps(hdcRef, HORZSIZE);
		iHeightMM = GetDeviceCaps(hdcRef, VERTSIZE);
		iWidthPels = GetDeviceCaps(hdcRef, HORZRES);
		iHeightPels = GetDeviceCaps(hdcRef, VERTRES);
		clientRect->left = (clientRect->left * iWidthMM * 100) / iWidthPels;
		clientRect->top = (clientRect->top * iHeightMM * 100) / iHeightPels;
		clientRect->right = (clientRect->right * iWidthMM * 100) / iWidthPels;
		clientRect->bottom = (clientRect->bottom * iHeightMM * 100) / iHeightPels;

		hdcMeta = CreateEnhMetaFile(hdcRef, (LPTSTR)fileName, clientRect, NULL);
		if (hdcMeta)
		{			
			FillRect(hdcMeta, clientRect, WHITE_BRUSH);
			DrawingShapes* drawingShapes = DrawingShapes::getInstance();
			drawingShapes->RedrawAllShapes(hdcMeta, clientRect);
			HENHMETAFILE hEmf = CloseEnhMetaFile(hdcMeta);
			DeleteEnhMetaFile(hEmf);
			ReleaseDC(hWnd, hdcRef);
			return true;
		}
		else
			return false;
	}
	else
		return false;
}