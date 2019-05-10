#include <iostream>
#include <cstring>
#include <cstdlib>
#include "Callback.h"
#include "UserData.h"
using namespace std;

int parseCallBack(const char* key, const char* value, void* usrData) //chequea si los datos ingresados por la linea de comandos son validos
{
	userData* myData = (userData*)usrData;
	bool program_success = CB_SUXS;

	//checking if option is valid
	if (key != NULL) //es opcion
	{
		if (!strcmp(key, "path"))
		{
			path tempPath(value);
			if (exists(tempPath))
			{
				if (is_directory(tempPath))
				{
					if (!(myData->setPath(tempPath)))
					{
						cout << "Error: Option 'path' has been set more than once" << endl;
						program_success = CB_ERR;
					}
				}
				else
				{
					cout << "Error: path is not a directory" << endl;
					program_success = CB_ERR;
				}
			}
			else
			{
				cout << "Error: path does not exist" << endl;
				program_success = CB_ERR;
			}
		}
		else if (!strcmp(key, "threshold"))
		{
			float tempValue = atof(value);
			if (tempValue >= CERO_PERCENT && tempValue <= HUNDRED_PERCENT)
			{
				if (!(myData->setThreshold(tempValue)))
				{
					cout << "Error: Option 'threshold' has been set more than once" << endl;
					program_success = CB_ERR;
				}
			}
			else
			{
				cout << "Error: threshold must be real number between 0 and 100" << endl;
				program_success = CB_ERR;
			}
		}
		else //option not valid
		{
			program_success = CB_ERR;
		}
	}

	else
	{
		cout << "This program does not accept parameters. Invalid input\n";
		getchar();		//pemite que el usuario visualize su codigo de error
		program_success = CB_ERR;
	}

	return program_success; //devuelve 1 si ingreso bien los datos y 0 si los ingreso mal
}
