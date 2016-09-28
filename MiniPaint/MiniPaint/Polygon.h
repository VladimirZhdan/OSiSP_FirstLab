#ifndef __Polygon__
#define __Polygon__

#include <Windows.h>
#include "DrawObject.h"

namespace MiniPaint
{
	class Polygon : virtual public DrawObject
	{
	public:
		Polygon(HPEN hPen);
		virtual void Draw(HDC hdc);
		virtual void AddExtraDot();

	};
}

#endif