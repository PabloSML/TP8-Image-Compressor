#pragma once
#ifndef CALLBACK_H
#define CALLBACK_H

#define CB_ERR 0		//Constantes de error y
#define CB_SUXS 1		//exito para este archivo

#define CERO_PERCENT 0.0
#define HUNDRED_PERCENT 100.0

//esta funcion valida 
int parseCallBack(const char* key, const char* value, void* usrData);
// Función que chequea si los datos ingresados por la línea de comandos son válidos

#endif // !CALLBACK_H
