#include "stdafx.h"
#include "FabricsBase.h"



Shape* LineCreator::Create()
{	
	return new Line();
}

Shape* PencilCreator::Create()
{
	return new Pencil();
}

Shape* RectangleCreator::Create()
{
	return new MiniPaint::Rectangle();
}

Shape* EllipseCreator::Create()
{
	return new MiniPaint::Ellipse();
}

Shape* PolygonalLineCreator::Create()
{
	return new MiniPaint::PolygonalLine();
}

Shape* PolygonCreator::Create()
{
	return new MiniPaint::Polygon();
}
