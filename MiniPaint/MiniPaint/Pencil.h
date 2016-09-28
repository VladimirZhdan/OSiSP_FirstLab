#ifndef __Pencil__
#define __Pencil__

#include <Windows.h>
#include "DrawObject.h"

namespace MiniPaint
{
	class Pencil : virtual public DrawObject
	{
	public:
		Pencil(HPEN hPen);
		virtual void Draw(HDC hdc);
	};
}

#endif