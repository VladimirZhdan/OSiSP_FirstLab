#ifndef __Line__
#define __Line__

#include "Windows.h"
#include "DrawObject.h"

namespace MiniPaint
{
	class Line : public DrawObject
	{
	public:
		Line(HPEN hPen, HBRUSH hBrush);
		virtual void Draw(HDC hdc);
	};
}

#endif
