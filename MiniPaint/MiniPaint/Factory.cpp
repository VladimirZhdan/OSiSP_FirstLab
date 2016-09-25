#include "stdafx.h"
#include "Factory.h"

std::vector<FabricsBase* > Factory::fabricsList = {
	new LineCreator(),
	new PencilCreator(),
	new RectangleCreator(),
	new EllipseCreator(),
	new PolygonalLineCreator(),
	new PolygonCreator()
};

FabricsBase* Factory::GetCurrentFabric(int index)
{			
	return Factory::fabricsList[index - 1];
}
