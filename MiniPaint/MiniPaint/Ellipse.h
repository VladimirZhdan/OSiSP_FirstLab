#ifndef __Ellipse__
#define __Ellipse__

#include <Windows.h>
#include "DrawObject.h"

namespace MiniPaint
{
	class Ellipse : virtual public DrawObject
	{
	public:
		Ellipse(HPEN hPen);
		virtual void Draw(HDC hdc);
	};

}

#endif