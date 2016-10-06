#ifndef __Polygon__
#define __Polygon__

#include <Windows.h>
#include "DrawObject.h"

namespace MiniPaint
{
	class Polygon : public DrawObject
	{
	public:
		Polygon(int thickness, COLORREF colorPen, COLORREF colorBrush);
		virtual void Draw(HDC hdc);
		virtual void AddExtraDot();

	};
}

#endif