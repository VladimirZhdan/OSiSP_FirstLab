#ifndef __Text__
#define __Text__

#include "Windows.h"
#include "DrawObject.h"
#include <xstring>

typedef std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> > String;

namespace MiniPaint
{
	class Text : virtual public DrawObject
	{
	public:
		Text(HPEN hPen, HBRUSH hBrush);
		virtual void Draw(HDC hdc);
		virtual void AddInformation(TCHAR inf);
	private:
		String textValue;
	};
}

#endif