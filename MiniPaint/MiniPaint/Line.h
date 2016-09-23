#ifndef __Line__
#define __Line__

#include "Windows.h"
#include "Shape.h"

class Line : virtual public Shape
{
public:
	Line();
	virtual void Draw(HDC hdc);	
};

#endif
