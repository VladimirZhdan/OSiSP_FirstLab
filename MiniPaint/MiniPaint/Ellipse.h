#ifndef __Ellipse__
#define __Ellipse__

#include <Windows.h>
#include "Shape.h"

namespace MiniPaint
{
	class Ellipse : public Shape
	{
	public:
		Ellipse();
		virtual void Draw(HDC hdc);
	};

}

#endif