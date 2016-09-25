#ifndef __FabricsBase__
#define __FabricsBase__

#include "Shape.h"
#include "Line.h"
#include "Pencil.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "PolygonalLine.h"
#include "Polygon.h"

class FabricsBase
{
public:
	virtual Shape* Create() = 0;
};

class LineCreator : public FabricsBase
{
public:		
	virtual Shape* Create();
};

class PencilCreator : public FabricsBase
{
public:	
	virtual Shape* Create();
};

class RectangleCreator : public FabricsBase
{
public:	
	virtual Shape* Create();
};

class EllipseCreator : public FabricsBase
{
public:	
	virtual Shape* Create();
};

class PolygonalLineCreator : public FabricsBase
{
public:	
	virtual Shape* Create();
};

class PolygonCreator : public FabricsBase
{
public:	
	virtual Shape* Create();
};

#endif