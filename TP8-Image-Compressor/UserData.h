#pragma once
#ifndef USERDATA_H
#define USERDATA_H

#include "boost/filesystem.hpp"
#include <cstdbool>
using namespace boost::filesystem;

#define EMPTY 0		//los campos de la clase userData se inicializan con esta constante

class userData {

public:

	userData() {
		usrPath = EMPTY;	// se inicializa la data en EMPTY
		threshold = EMPTY;
	}

	path getPath(void);
	bool setPath(path& usrPath);

	float getThreshold(void);
	bool setThreshold(float& threshold);

	bool isDataFull();	//esta funcion devuelve 'true' si todos los datos han sido ingresados exitosamente, 'false' si no
	bool isPathFull();

private:
	path* usrPath;
	float threshold;
};


#endif