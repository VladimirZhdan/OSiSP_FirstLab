#ifndef __PolygonalLine__
#define __PolygonalLine__

#include <Windows.h>
#include "DrawObject.h"

namespace MiniPaint
{
	class PolygonalLine : virtual public DrawObject
	{
	public:
		PolygonalLine(HPEN hPen);
		virtual void Draw(HDC hdc);
		virtual void AddExtraDot();
	};
}

#endif