#ifndef __Shape__
#define __Shape__

#include "Windows.h"
#include <vector>

class Shape
{
public:	
	Shape();
	void AddDot(POINT point);
	void ChangeIntermediateOrAddNewDot(POINT point);
	virtual void AddExtraDot();
	virtual void Draw(HDC hdc) = 0;
	bool isEndDrawing();
protected:	
	std::vector<POINT> dots;
	int countDots;
	bool endDrawing;
private:	

};

#endif
