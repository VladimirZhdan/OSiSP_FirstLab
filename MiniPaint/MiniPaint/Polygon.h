#ifndef __Polygon__
#define __Polygon__

#include <Windows.h>
#include "DrawObject.h"

namespace MiniPaint
{
	class Polygon : public DrawObject
	{
	public:
		Polygon(HPEN hPen, HBRUSH hBrush);
		virtual void Draw(HDC hdc);
		virtual void AddExtraDot();

	};
}

#endif