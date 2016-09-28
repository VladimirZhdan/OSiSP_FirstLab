#ifndef __Line__
#define __Line__

#include "Windows.h"
#include "DrawObject.h"

namespace MiniPaint
{
	class Line : virtual public DrawObject
	{
	public:
		Line(HPEN hPen);
		virtual void Draw(HDC hdc);
	};
}

#endif
