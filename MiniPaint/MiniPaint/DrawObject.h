	#ifndef __DrawObject__
#define __DrawObject__

#include "Windows.h"
#include <vector>

class DrawObject
{
public:	
	DrawObject(HPEN hPen, HBRUSH hBrush);
	void AddDot(POINT point);
	void ChangeIntermediateOrAddNewDot(POINT point);
	virtual void AddExtraDot();
	virtual void Draw(HDC hdc) = 0;
	virtual void AddInformation(TCHAR inf);
	RECT* GetRect();
	bool isEndDrawing();
	void ChangeCoordinates(int deltaX, int deltaY);
		
protected:	
	std::vector<POINT> dots;
	int countDots;
	bool endDrawing;
	HPEN hPen;
	HBRUSH hBrush;
};

#endif
