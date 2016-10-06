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
	virtual DrawObject* Create(int thickness, COLORREF colorPen, COLORREF colorBrush) = 0;
};

class LineCreator : public FabricsBase
{
public:		
	virtual DrawObject* Create(int thickness, COLORREF colorPen, COLORREF colorBrush);
};

class PencilCreator : public FabricsBase
{
public:	
	virtual DrawObject* Create(int thickness, COLORREF colorPen, COLORREF colorBrush);
};

class RectangleCreator : public FabricsBase
{
public:	
	virtual DrawObject* Create(int thickness, COLORREF colorPen, COLORREF colorBrush);
};

class EllipseCreator : public FabricsBase
{
public:	
	virtual DrawObject* Create(int thickness, COLORREF colorPen, COLORREF colorBrush);
};

class PolygonalLineCreator : public FabricsBase
{
public:	
	virtual DrawObject* Create(int thickness, COLORREF colorPen, COLORREF colorBrush);
};

class PolygonCreator : public FabricsBase
{
public:	
	virtual DrawObject* Create(int thickness, COLORREF colorPen, COLORREF colorBrush);
};

class TextCreator : public FabricsBase
{
public:
	virtual DrawObject* Create(int thickness, COLORREF colorPen, COLORREF colorBrush);
};

#endif