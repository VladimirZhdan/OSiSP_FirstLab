#ifndef __PolygonalLine__
#define __PolygonalLine__

#include <Windows.h>
#include "Shape.h"

namespace MiniPaint
{
	class PolygonalLine : public Shape
	{
	public:
		PolygonalLine();
		virtual void Draw(HDC hdc);
		virtual void AddExtraDot();
	};
}

#endif