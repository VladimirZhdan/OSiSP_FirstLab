#ifndef __Rectangle__
#define __Rectangle__

#include <Windows.h>
#include "Shape.h"

namespace MiniPaint
{
	class Rectangle : public Shape
	{
	public:
		Rectangle();
		virtual void Draw(HDC hdc);
	};
}

#endif 