#ifndef __Pencil__
#define __Pencil__

#include <Windows.h>
#include "DrawObject.h"

namespace MiniPaint
{
	class Pencil : public DrawObject
	{
	public:
		Pencil(HPEN hPen, HBRUSH hBrush);
		virtual void Draw(HDC hdc);
	};
}

#endif