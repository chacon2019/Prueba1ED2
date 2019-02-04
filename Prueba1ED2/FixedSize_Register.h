#ifndef FIXEDSIZE_REGISTER_H

#define FIXEDSIZE_REGISTER_H

#include "DataFile.h"

struct FixedSize_Register
{
public:
	FixedSize_Register();
	void mostrarRegistro();
	char* toChar();
	void fromChar(char *);
	void escribirRegistro();
	void leerRegistro(int);
	void abrirArchivo(char *);
	void cerrarArchivo();
	int tamanoRegistro();

private:
	DataFile * archivo;
	int codigo;
	char *nombre;
	double salario;
	char * trabajo;
};











#endif // !FixedSize_Register
