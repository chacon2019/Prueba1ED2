#include "DelimiterVarSize_Register.h"
#include <iostream>


Registro_1::Registro_1() {

	this->archivo = new DataFile((char *)"DelimiterVarSize_Register.dat");
}

//Registro_1::Registro_1(int cod, char * name, double salary, char* job)
//{
//	
//	this->codigo = cod;
//	this->nombre = new char[strlen(name)];
//	memcpy(&this->nombre, &name, strlen(name));
//	this->salario = salary;
//	this->trabajo = new char[strlen(job)];
//	memcpy(&this->trabajo, &job, strlen(job));
//}

void Registro_1::mostrarRegistro()
{
	std::cout << "Nombre: " << codigo << std::endl;
	std::cout << "Apellido: " << nombre << std::endl;
	std::cout << "Edad: " << salario << std::endl;
	std::cout << "Direccion: " << trabajo << std::endl;
}

void Registro_1::fromChar(char *data)
{
	char delimitador = ';';
	char finRegistro = '|';

	int posicion = 0;

	char *token = strtok(data, &delimitador);
	int longitud = strlen(token);


	memcpy(&codigo, &data[posicion], sizeof(int));
	posicion += sizeof(int) + 1;

	/////////////////////////////////////////////////
	token = strtok(NULL, &delimitador);
	longitud = strlen(token);

	memcpy(nombre, &data[posicion], longitud);
	posicion += longitud + 1;
	/////////////////////////////////////////////////
	token = strtok(NULL, &delimitador);


	memcpy(&salario, &data[posicion], sizeof(double));
	posicion += sizeof(double) + 1;

	/////////////////////////////////////////////////

	token = strtok(NULL, &finRegistro);
	longitud = strlen(token);

	memcpy(trabajo, &data[posicion], longitud);

}

char * Registro_1::toChar()
{
	char *buffer = new char[tamanoRegistro()];

	char delimitadorCampo = ';';
	char finRegistro = '|';

	int posicion = 0;

	memcpy(&buffer[posicion], &this->codigo, sizeof(int));
	posicion += sizeof(int);

	memcpy(&buffer[posicion], &delimitadorCampo, 1);
	posicion++;

	int longitud = strlen(this->nombre);
	memcpy(&buffer[posicion], this->nombre, longitud);
	posicion += longitud;

	memcpy(&buffer[posicion], &delimitadorCampo, 1);
	posicion++;

	memcpy(&buffer[posicion], &this->salario, sizeof(double));
	posicion += sizeof(double);


	memcpy(&buffer[posicion], &delimitadorCampo, 1);
	posicion++;

	longitud = strlen(this->trabajo);
	memcpy(&buffer[posicion], &this->trabajo, longitud);
	posicion += longitud;

	memcpy(&buffer[posicion], &finRegistro, 1);

	return buffer;

}

int Registro_1::tamanoRegistro()
{
	int tamano = 0;

	tamano += sizeof(int);
	tamano += 1; //;
	tamano += strlen(this->nombre);
	tamano += 1; //;
	tamano += sizeof(double);
	tamano += 1; //;
	tamano += strlen(this->trabajo);
	tamano += 1; //|

	return tamano;
}

void Registro_1::escribirRegistro()
{
	this->archivo->write(this->toChar(), this->tamanoRegistro());
}

void Registro_1::leerRegistro(int posicions)
{
	abrirArchivo();

	char *data = new char;
	int posicion = 0;

	char *byte = archivo->read(0, 1);


	char finRegistro = '|';

	while (byte != &finRegistro)
	{
		memcpy(&data[posicion], byte, 1);
		byte = archivo->read(0, 1);
	}

	if (byte == &finRegistro)
	{
		memcpy(&data[posicion], byte, 1);
	}

	fromChar(data);

	//char * data = archivo->leer(posicion, 
}

void Registro_1::abrirArchivo()
{
	archivo->open(ios::in | ios::out | ios::binary | ios::app);
}

void Registro_1::cerrarArchivo()
{
	archivo->close();
}

