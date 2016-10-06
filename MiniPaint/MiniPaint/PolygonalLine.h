#ifndef __PolygonalLine__
#define __PolygonalLine__

#include <Windows.h>
#include "DrawObject.h"

namespace MiniPaint
{
	class PolygonalLine : public DrawObject
	{
	public:
		PolygonalLine(HPEN hPen, HBRUSH hBrush);
		virtual void Draw(HDC hdc);
		virtual void AddExtraDot();
	};
}

#endif