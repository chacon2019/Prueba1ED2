#ifndef KNOWNVARSIZE_H


#define KNOWNVARSIZE_H

#include "DataFile.h"


class KnownVarSize
{


private:

	DataFile * File;
	int codigo;
	
	char * name;
	double salary;

	char * job;

public:
	int sizeName;
	int sizeJob;
	KnownVarSize();
	void mostrarRegistro();
	char* toChar();
	void fromChar(char *);
	void escribirRegistro();
	void leerRegistro(int);
	void abrirArchivo(char *);
	void cerrarArchivo();
	int tamanoRegistro();







};
	
#endif // !KNOWNVARSIZE
