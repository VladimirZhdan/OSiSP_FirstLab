#ifndef __Pencil__
#define __Pencil__

#include <Windows.h>
#include "Shape.h"

class Pencil : public Shape
{
public:
	Pencil();
	virtual void Draw(HDC hdc);
};

#endif