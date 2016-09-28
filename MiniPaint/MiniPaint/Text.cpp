#include "stdafx.h"
#include "Text.h"

using namespace MiniPaint;

Text::Text(HPEN hPen) : DrawObject(hPen)
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
	TextOut(hdc, dots[0].x, dots[0].y, textValue.data(), textValue.size());
}