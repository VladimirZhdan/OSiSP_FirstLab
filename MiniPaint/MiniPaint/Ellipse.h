#ifndef __Ellipse__
#define __Ellipse__

#include <Windows.h>
#include "DrawObject.h"

namespace MiniPaint
{
	class Ellipse : public DrawObject
	{
	public:
		Ellipse(int thickness, COLORREF colorPen, COLORREF colorBrush);
		virtual void Draw(HDC hdc);
	};

}

#endif