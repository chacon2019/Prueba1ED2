#include <iostream>
#include <cstring>
#include "FixedSize_Register.h"
using namespace std;

FixedSize_Register::FixedSize_Register() {



	this->nombre = new char[30];
	this->trabajo = new char[20];


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

void FixedSize_Register::mostrarRegistro()
{
	std::cout << "Codigo: " << this->codigo << std::endl;
	std::cout << "Nombre: " << this->nombre << std::endl;
	std::cout << "Salario: " << this->salario << std::endl;
	std::cout << "Trabajo: " << this->trabajo << std::endl;
}

void FixedSize_Register::fromChar(char * buffer)
{


	memcpy(&this->codigo, buffer, sizeof(this->codigo));
	buffer += sizeof(this->codigo);
	memcpy(this->nombre, buffer, 30);
	buffer += 30;
	memcpy(&this->salario, buffer, sizeof(this->salario));
	buffer += sizeof(this->salario);
	memcpy(this->trabajo, buffer, 20);

}

char * FixedSize_Register::toChar()
{
	const int size = this->tamanoRegistro();
	char *buffer = new char[size];

	memcpy(buffer, reinterpret_cast<char *>(&this->codigo), sizeof(this->codigo));
	buffer += sizeof(this->codigo);
	memcpy(buffer, this->nombre, 30);
	buffer += 30;
	memcpy(buffer, reinterpret_cast<char *>(&this->salario), sizeof(this->salario));
	buffer += sizeof(this->salario);
	memcpy(buffer, this->trabajo, 20);

	return buffer;

}

int FixedSize_Register::tamanoRegistro()
{
	int tamano = 0;

	tamano += sizeof(int);
	tamano += 30;
	tamano += sizeof(double);
	tamano += 20;

	return tamano;
}

void FixedSize_Register::escribirRegistro()
{

	this->archivo->write(this->toChar(), this->tamanoRegistro());

}


void FixedSize_Register::leerRegistro(int posicions)
{

	archivo->open(ios::in | ios::out | ios::binary | ios::app);
	char *buffer = this->archivo->read(posicions, this->tamanoRegistro());
	this->fromChar(buffer);
	this->archivo->close();
	delete buffer;

}


void FixedSize_Register::abrirArchivo(char * file)
{

	
	this->archivo = new DataFile(file);
	archivo->open(ios::in | ios::out | ios::binary | ios::app);

}

void FixedSize_Register::cerrarArchivo()
{
	archivo->close();
}


