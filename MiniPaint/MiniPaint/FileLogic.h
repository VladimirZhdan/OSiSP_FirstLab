#ifndef __FileLogic__
#define __FileLogic__

#include <Windows.h>

class FileLogic
{
public:
	static bool SaveAsEnhancedFile(HWND hWnd, TCHAR fileName[]);
	static bool OpenEnhancedFile(HENHMETAFILE *hEnhMetaFile, TCHAR fileName[]);
};


#endif