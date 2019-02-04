#ifndef REGISTRO_1

#define REGISTRO_1

#include "DataFile.h"

class Registro_1
{
public:
	Registro_1();
	//Registro_1(int, char *, double, char*);
	void mostrarRegistro();
	char* toChar();
	void fromChar(char *);
	void escribirRegistro();
	void leerRegistro(int);
	void abrirArchivo();
	void cerrarArchivo();
	int tamanoRegistro();

private:
	DataFile * archivo;
	int codigo;
	char *nombre;
	double salario;
	char *trabajo;
};

#endif // !REGISTRO_1
