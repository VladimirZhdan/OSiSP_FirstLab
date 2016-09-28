#ifndef __DrawingShapes__
#define __DrawingShapes__

#include <vector>
#include "DrawObject.h"

class DrawingShapes
{
public:
	DrawingShapes(HWND hWnd);
	~DrawingShapes();
	void StartDrawing(DrawObject *shape);
	void AddDot(POINT point);
	void Drawing(POINT point);
	void AddExtraDot();
	void AddInformation(TCHAR inf);
	bool isEndDrawing();
private:	
	void RedrawAllShapes(HDC hdc);
	std::vector<DrawObject*> shapes;
	bool endDrawing = true;
	DrawObject *currentShape;
	HWND hWnd;


};


;
#endif
