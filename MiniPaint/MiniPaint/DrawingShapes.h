#ifndef __DrawingShapes__
#define __DrawingShapes__

#include <vector>
#include "Shape.h"

class DrawingShapes
{
public:
	void StartDrawing(Shape *shape);
	void Drawing(POINT point);
	void DrawingAllShapes(HDC hdc);

private:
	std::vector<Shape*> shapes;
	bool endDrawing = true;
	Shape *currentShape;


};



#endif
