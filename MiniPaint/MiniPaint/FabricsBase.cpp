#include "stdafx.h"
#include "FabricsBase.h"



DrawObject* LineCreator::Create(HPEN hPen, HBRUSH hBrush)
{	
	return new MiniPaint::Line(hPen, hBrush);
}

DrawObject* PencilCreator::Create(HPEN hPen, HBRUSH hBrush)
{
	return new MiniPaint::Pencil(hPen, hBrush);
}

DrawObject* RectangleCreator::Create(HPEN hPen, HBRUSH hBrush)
{
	return new MiniPaint::Rectangle(hPen, hBrush);
}

DrawObject* EllipseCreator::Create(HPEN hPen, HBRUSH hBrush)
{
	return new MiniPaint::Ellipse(hPen, hBrush);
}

DrawObject* PolygonalLineCreator::Create(HPEN hPen, HBRUSH hBrush)
{
	return new MiniPaint::PolygonalLine(hPen, hBrush);
}

DrawObject* PolygonCreator::Create(HPEN hPen, HBRUSH hBrush)
{
	return new MiniPaint::Polygon(hPen, hBrush);
}

DrawObject* TextCreator::Create(HPEN hPen, HBRUSH hBrush)
{
	return new MiniPaint::Text(hPen, hBrush);
}