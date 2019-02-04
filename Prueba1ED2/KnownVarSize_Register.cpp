#include "KnownVarSize_Register.h"
#include <iostream>


KnownVarSize::KnownVarSize()
{


	this->File = new DataFile((char *)"KnownVarSize.dat");

}




void KnownVarSize::mostrarRegistro() {


	std::cout << "Codigo: " << this->codigo << std::endl;
	std::cout << "Nombre: " << this->name << std::endl;
	std::cout << "Salario: " << this->salary << std::endl;
	std::cout << "Trabajo: " << this->job << std::endl;



}

char * KnownVarSize::toChar()
{
	const int size = this->tamanoRegistro();
	char *data = new char[size];

	memcpy(data, reinterpret_cast<char *>(&this->codigo), sizeof(this->codigo));

	memcpy(data + sizeof(this->codigo), reinterpret_cast<char *>(&this->sizeName), sizeof(this->sizeName));

	memcpy(data + sizeof(this->codigo) + sizeof(this->sizeName), this->name, this->sizeName);

	memcpy(data + sizeof(this->codigo) + sizeof(this->sizeName) + this->sizeName, reinterpret_cast<char *>(&this->salary), sizeof(this->salary));

	memcpy(data + sizeof(this->codigo) + sizeof(this->sizeName) + this->sizeName + sizeof(this->salary), reinterpret_cast<char *>(&this->sizeJob), sizeof(this->sizeJob));

	memcpy(data + sizeof(this->codigo) + sizeof(this->sizeName) + this->sizeName + sizeof(this->salary) + sizeof(this->sizeJob), this->job, this->sizeJob);

	return data;
}

void KnownVarSize::fromChar(char * data)
{
	memcpy(&this->codigo, data, sizeof(this->codigo));

	memcpy(&this->sizeName, data + sizeof(this->codigo), sizeof(this->sizeName));
	this->name = new char[this->sizeName];

	memcpy(this->name, data + sizeof(this->codigo) + sizeof(this->sizeName), this->sizeName);

	memcpy(&this->salary, data + sizeof(this->codigo) + sizeof(this->sizeName) + this->sizeName, sizeof(this->salary));

	memcpy(&this->sizeJob, data + sizeof(this->codigo) + sizeof(this->sizeName) + this->sizeName + sizeof(this->salary), sizeof(this->sizeJob));
	this->job = new char[this->sizeJob];

	memcpy(this->job, data + sizeof(this->codigo) + sizeof(this->sizeName) + this->sizeName + sizeof(this->salary) + sizeof(this->sizeJob), this->sizeJob);
}

void KnownVarSize::abrirArchivo(char *name)
{
	this->File = new DataFile(name);

}
void KnownVarSize::escribirRegistro() {

	this->File->write(this->toChar(), this->tamanoRegistro());


}
void KnownVarSize::leerRegistro(int pos) {

	int tam = 0;

	for (int i = 0; i <= pos; i++)
	{
		this->codigo = *(reinterpret_cast<int *>(this->File->read(tam, sizeof(int))));
		this->sizeName = *(reinterpret_cast<int *>(this->File->read(tam + sizeof(int), sizeof(int))));
		this->name = this->File->read(tam + sizeof(this->codigo) + sizeof(this->sizeName), this->sizeName);
		this->salary = *(reinterpret_cast<double *>(this->File->read(tam + sizeof(this->codigo) + sizeof(this->sizeName) + this->sizeName, sizeof(double))));
		this->sizeJob = *(reinterpret_cast<int *>(this->File->read(tam + sizeof(this->codigo) + sizeof(this->sizeName) + this->sizeName + sizeof(this->salary), sizeof(int))));
		this->job = this->File->read(tam + sizeof(this->codigo) + sizeof(this->sizeName) + this->sizeName + sizeof(this->salary) + sizeof(this->sizeJob), this->sizeJob);

		tam += this->tamanoRegistro();
	}
}

void KnownVarSize::cerrarArchivo() {
	File->close();
}
int KnownVarSize::tamanoRegistro() {


	int tamano = 0;

	tamano += sizeof(this->codigo);
	tamano += sizeof(this->sizeName);; //;
	tamano += strlen(this->name);
	tamano += sizeof(this->salary);
	tamano += sizeof(this->sizeJob);; //;
	tamano += strlen(this->job);

	return tamano;
}

