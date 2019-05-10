#ifndef PARSER_H
#define PARSER_H

typedef enum {KEY = -4, VALUE, CB_OPT, CB_PAR}error_t;

//Este es el prototipo que debe cumplir la funcion que recibe parseCmdLine para funcionar correctamente.
//La funcion debe devolver un 0 en caso de exito y un 1 en caso de error.
typedef int(*pCallback) (const char*, const char*, void*);

/*
Esta funcion valida la forma de lo ingresado por linea de comandos y utiliza una funcion recibida para validar su coherencia
Recibe:
	argc: cantidad de argumentos a analizar
	argv: argumentos a analizar
	checkInputs: funcion que contiene los criterios de validacion segun la coherencia de los argumentos
	userData: puntero hacia una zona designada por el usuario para pasar a la funcion checkInputs
Devuelve:
	KEY si la clave de una opcion no fue ingresada
	VALUE si el valor de una opcion no fue ingresado
	CB_OPT si la funcion de validacion encontro un error de contenido en una opcion
	CB_PAR si la funcion de validacion encontro un error de contenido en un parametro
	sum - la suma de la cantidad de opciones y parametros - si no hubo ningun error
Clave: Argumento que comienza con '-' y requiere un valor como siguiente argumento. No puede ser vacia
Valor: Argumento precededido por una clave. No puede ser vacio
Parámetro: Argumento que no comienza con '-' y no es precedido por una clave
*/
int parseCmdLine(int argc, char const *argv[], pCallback checkInputs, void * userData);

#endif