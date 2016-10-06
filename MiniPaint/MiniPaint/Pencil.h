#ifndef __Pencil__
#define __Pencil__

#include <Windows.h>
#include "DrawObject.h"

namespace MiniPaint
{
	class Pencil : public DrawObject
	{
	public:
		Pencil(int thickness, COLORREF colorPen, COLORREF colorBrush);
		virtual void Draw(HDC hdc);
	};
}

#endif