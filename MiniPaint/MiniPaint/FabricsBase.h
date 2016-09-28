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
	virtual DrawObject* Create(HPEN hPen) = 0;
};

class LineCreator : public FabricsBase
{
public:		
	virtual DrawObject* Create(HPEN hPen);
};

class PencilCreator : public FabricsBase
{
public:	
	virtual DrawObject* Create(HPEN hPen);
};

class RectangleCreator : public FabricsBase
{
public:	
	virtual DrawObject* Create(HPEN hPen);
};

class EllipseCreator : public FabricsBase
{
public:	
	virtual DrawObject* Create(HPEN hPen);
};

class PolygonalLineCreator : public FabricsBase
{
public:	
	virtual DrawObject* Create(HPEN hPen);
};

class PolygonCreator : public FabricsBase
{
public:	
	virtual DrawObject* Create(HPEN hPen);
};

class TextCreator : public FabricsBase
{
public:
	virtual DrawObject* Create(HPEN hPen);
};

#endif