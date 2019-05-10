#include <cstdlib>
#include "UserData.h"

//esta funcion devuelve 'true' si todos los datos han sido ingresados exitosamente, 'false' si no
bool 
userData::isDataFull()
{
	bool dataFull = true;

	if (usrPath == EMPTY)
		dataFull = false;
	if (threshold == EMPTY)
		dataFull = false;
	return dataFull;
}

bool
userData::isPathFull()
{
	bool pathFull = false;
	if (usrPath != EMPTY)
		pathFull = true;
	return pathFull;
}

path* userData::getPath(void) { return usrPath; }

bool
userData::setPath(path* usrPath)
{
	bool success = false;
	if (this->usrPath == EMPTY)
	{
		this->usrPath = usrPath;
		success = true;
	}
	return success;
}

float userData::getThreshold(void) { return threshold; }

bool
userData::setThreshold(float& threshold)
{
	bool success = false;
	if (this->threshold == EMPTY)
	{
		this->threshold = threshold;
		success = true;
	}
	return success;
}