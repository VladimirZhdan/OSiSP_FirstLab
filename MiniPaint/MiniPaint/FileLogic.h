#ifndef __FileLogic__
#define __FileLogic__

#include <Windows.h>
#include "DrawingShapes.h"

class FileLogic
{
public:
	static bool SaveAsEnhancedFile(HWND hWnd, TCHAR fileName[]);
	static bool OpenEnhancedFile(HENHMETAFILE *hEnhMetaFile, TCHAR fileName[]);
	static bool PrintAsEnhancedFile(HWND hWnd, TCHAR fileName[]);
private:
	static bool SaveEnhancedFile(HWND hWnd, TCHAR fileName[], RECT *clientRect);
};


#endif