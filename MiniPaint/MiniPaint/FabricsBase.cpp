#include "stdafx.h"
#include "FabricsBase.h"



DrawObject* LineCreator::Create(HPEN hPen)
{	
	return new MiniPaint::Line(hPen);
}

DrawObject* PencilCreator::Create(HPEN hPen)
{
	return new MiniPaint::Pencil(hPen);
}

DrawObject* RectangleCreator::Create(HPEN hPen)
{
	return new MiniPaint::Rectangle(hPen);
}

DrawObject* EllipseCreator::Create(HPEN hPen)
{
	return new MiniPaint::Ellipse(hPen);
}

DrawObject* PolygonalLineCreator::Create(HPEN hPen)
{
	return new MiniPaint::PolygonalLine(hPen);
}

DrawObject* PolygonCreator::Create(HPEN hPen)
{
	return new MiniPaint::Polygon(hPen);
}

DrawObject* TextCreator::Create(HPEN hPen)
{
	return new MiniPaint::Text(hPen);
}