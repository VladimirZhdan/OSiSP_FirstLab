#ifndef __Shape__
#define __Shape__

#include "Windows.h"
#include <vector>

class Shape
{
public:	
	Shape();
	void AddDot(POINT point);
	virtual void EndCreateShape();
	virtual void Draw(HDC hdc) = 0;
	bool isEndDrawing();

protected:	
	std::vector<POINT> dots;
	int countDots;

private:
	bool endDrawing;

};

#endif
