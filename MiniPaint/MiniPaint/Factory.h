#ifndef __Factory__
#define __Factory__

#include <vector>
#include "FabricsBase.h"
#include "Shape.h"

class Factory
{
public:
	static FabricsBase* GetCurrentFabric(int index);
private:	
	static FabricsBase* List[6];
	static std::vector<FabricsBase* > fabricsList;	
};

#endif
