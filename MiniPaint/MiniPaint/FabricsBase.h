#ifndef __FabricsBase__
#define __FabricsBase__

#include "DrawObject.h"
#include "Line.h"
#include "Pencil.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "PolygonalLine.h"
#include "Polygon.h"
#include "Text.h"

class FabricsBase
{
public:
	virtual DrawObject* Create(HPEN hPen, HBRUSH hBrush) = 0;
};

class LineCreator : public FabricsBase
{
public:		
	virtual DrawObject* Create(HPEN hPen, HBRUSH hBrush);
};

class PencilCreator : public FabricsBase
{
public:	
	virtual DrawObject* Create(HPEN hPen, HBRUSH hBrush);
};

class RectangleCreator : public FabricsBase
{
public:	
	virtual DrawObject* Create(HPEN hPen, HBRUSH hBrush);
};

class EllipseCreator : public FabricsBase
{
public:	
	virtual DrawObject* Create(HPEN hPen, HBRUSH hBrush);
};

class PolygonalLineCreator : public FabricsBase
{
public:	
	virtual DrawObject* Create(HPEN hPen, HBRUSH hBrush);
};

class PolygonCreator : public FabricsBase
{
public:	
	virtual DrawObject* Create(HPEN hPen, HBRUSH hBrush);
};

class TextCreator : public FabricsBase
{
public:
	virtual DrawObject* Create(HPEN hPen, HBRUSH hBrush);
};

#endif