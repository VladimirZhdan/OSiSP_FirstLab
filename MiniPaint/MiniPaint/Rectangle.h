#ifndef __Rectangle__
#define __Rectangle__

#include <Windows.h>
#include "DrawObject.h"

namespace MiniPaint
{
	class Rectangle : virtual public DrawObject
	{
	public:
		Rectangle(HPEN hPen);
		virtual void Draw(HDC hdc);
	};
}

#endif 