#ifndef __Polygon__
#define __Polygon__

#include <Windows.h>
#include "Shape.h"

namespace MiniPaint
{
	class Polygon : public Shape
	{
	public:
		Polygon();
		virtual void Draw(HDC hdc);
		virtual void AddExtraDot();

	};
}

#endif