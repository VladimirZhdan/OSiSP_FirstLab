#include "stdafx.h"
#include "FabricsBase.h"



DrawObject* LineCreator::Create(int thickness, COLORREF colorPen, COLORREF colorBrush)
{	
	return new MiniPaint::Line(thickness, colorPen, colorBrush);
}

DrawObject* PencilCreator::Create(int thickness, COLORREF colorPen, COLORREF colorBrush)
{
	return new MiniPaint::Pencil(thickness, colorPen, colorBrush);
}

DrawObject* RectangleCreator::Create(int thickness, COLORREF colorPen, COLORREF colorBrush)
{
	return new MiniPaint::Rectangle(thickness, colorPen, colorBrush);
}

DrawObject* EllipseCreator::Create(int thickness, COLORREF colorPen, COLORREF colorBrush)
{
	return new MiniPaint::Ellipse(thickness, colorPen, colorBrush);
}

DrawObject* PolygonalLineCreator::Create(int thickness, COLORREF colorPen, COLORREF colorBrush)
{
	return new MiniPaint::PolygonalLine(thickness, colorPen, colorBrush);
}

DrawObject* PolygonCreator::Create(int thickness, COLORREF colorPen, COLORREF colorBrush)
{
	return new MiniPaint::Polygon(thickness, colorPen, colorBrush);
}

DrawObject* TextCreator::Create(int thickness, COLORREF colorPen, COLORREF colorBrush)
{
	return new MiniPaint::Text(thickness, colorPen, colorBrush);
}