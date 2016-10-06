#ifndef __Rectangle__
#define __Rectangle__

#include <Windows.h>
#include "DrawObject.h"

namespace MiniPaint
{
	class Rectangle : public DrawObject
	{
	public:
		Rectangle(HPEN hPen, HBRUSH hBrush);
		virtual void Draw(HDC hdc);
	};
}

#endif 