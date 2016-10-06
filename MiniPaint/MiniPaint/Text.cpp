#include "stdafx.h"
#include "Text.h"

using namespace MiniPaint;

Text::Text(int thickness, COLORREF colorPen, COLORREF colorBrush) : DrawObject(thickness, colorPen, colorBrush)
{
	countDots = 2;
}

void Text::AddInformation(TCHAR inf)
{
	switch (inf)
	{
		case VK_BACK:
			if (textValue.size() > 0)
				textValue.erase(textValue.size() - 1, 1);
			break;
		case VK_ESCAPE:
			this->AddDot(dots[0]);
			break;
		default:
			textValue += inf;
			break;
	}	
}

void Text::Draw(HDC hdc)
{
	HGDIOBJ prevPen = SelectObject(hdc, hPen);
	HGDIOBJ prevBrush = SelectObject(hdc, hBrush);
	TextOut(hdc, dots[0].x, dots[0].y, textValue.data(), textValue.size());
	SelectObject(hdc, prevPen);
	SelectObject(hdc, prevBrush);
}