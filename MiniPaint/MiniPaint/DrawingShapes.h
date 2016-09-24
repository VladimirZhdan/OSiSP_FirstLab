#ifndef __DrawingShapes__
#define __DrawingShapes__

#include <vector>
#include "Shape.h"

class DrawingShapes
{
public:
	DrawingShapes(HWND hWnd);
	void StartDrawing(Shape *shape);
	void AddDot(POINT point);
	void Drawing(POINT point);
	void AddExtraDot();
private:	
	void RedrawAllShapes(HDC hdc);
	std::vector<Shape*> shapes;
	bool endDrawing = true;
	Shape *currentShape;
	HWND hWnd;


};


;
#endif
