#include  <iostream>
#include  <conio.h>
#include  <string>
#include "DelimiterVarSize_Register.h"
#include "FixedSize_Register.h"
#include "KnownVarSize_Register.h"




using namespace std;


int a;




int tamKnownVarSizeR;

int tamanoRegistrotamKnownVarSizeR(char * name, char * job) {


	int tamano = 0;

	tamano += 4;
	tamano += 4; //;
	tamano += strlen(name);
	tamano += 8;
	tamano += 4; //;
	tamano += strlen(job);

	return tamano;
}

int tamanoRegistro(char * nombre, char * trabajo)
{
	int tamano = 0;

	tamano += sizeof(int);
	tamano += 1; //;
	tamano += strlen(nombre);
	tamano += 1; //;
	tamano += sizeof(double);
	tamano += 1; //;
	tamano += strlen(trabajo);
	tamano += 1; //|

	return tamano;
}

char * toChar(int codigo, char *nombre, double salario, char * trabajo)
{
	char *buffer = new char[a];

	char delimitadorCampo = ';';
	char finRegistro = '|';

	int posicion = 0;

	memcpy(&buffer[posicion], &codigo, sizeof(int));
	posicion += sizeof(int);

	memcpy(&buffer[posicion], &delimitadorCampo, 1);
	posicion++;

	int longitud = strlen(nombre);
	memcpy(&buffer[posicion], nombre, longitud);
	posicion += longitud;

	memcpy(&buffer[posicion], &delimitadorCampo, 1);
	posicion++;

	memcpy(&buffer[posicion], &salario, sizeof(double));
	posicion += sizeof(double);


	memcpy(&buffer[posicion], &delimitadorCampo, 1);
	posicion++;

	longitud = strlen(trabajo);
	memcpy(&buffer[posicion], &trabajo, longitud);
	posicion += longitud;

	memcpy(&buffer[posicion], &finRegistro, 1);

	return buffer;

}

char * toCharFixedSize_Register(int codigo, char *nombre, double salario, char * trabajo)
{
	char *buffer = new char[62];

	memcpy(buffer, reinterpret_cast<char *>(&codigo), sizeof(int));
	buffer += sizeof(int);
	memcpy(buffer, nombre, 30);
	buffer += 30;
	memcpy(buffer, reinterpret_cast<char *>(&salario), sizeof(salario));
	buffer += sizeof(salario);
	memcpy(buffer, trabajo, 20);

	return buffer;
	

}

char * toCharKnownVarSizeR(int id, int sizeName,char *name, double salary, int sizeJob, char *job )
{
	char *buffer = new char[sizeof(id) + sizeof(sizeName) + sizeName + sizeof(salary) + sizeof(sizeJob) + sizeJob];

	memcpy(buffer, reinterpret_cast<char *>(&id), sizeof(id));
	buffer += +sizeof(id);
	memcpy(buffer, reinterpret_cast<char *>(&sizeName), sizeof(sizeName));
	buffer += sizeof(sizeName);
	memcpy(buffer, name, sizeName);
	buffer += sizeName;
	memcpy(buffer, reinterpret_cast<char *>(&salary), sizeof(salary));
	buffer += sizeof(salary);
	memcpy(buffer, reinterpret_cast<char *>(&sizeJob), sizeof(sizeJob));
	buffer += sizeof(sizeJob);
	memcpy(buffer, job, sizeJob);

	return buffer;
}








int main() {






	/*
				string g;
				string nombre = "";
				cout << "Archivo 1 : " << endl;
				cin >> g;

				nombre = "C:/Users/Marco Chacon/source/repos/Prueba1ED2/Prueba1ED2/" + g + ".dat";

				char * f = new char[nombre.length() + 1];
				strcpy(f, nombre.c_str());

				DataFile * archivo = new DataFile(f);
				archivo->abrir();
				Registro_1 * DelimiterVarSize_Register;
			*/







		int opcion;
		do
		{

			cout << " 1.FixedSize_Register : " << endl;
			cout << " 2. KnownVarSize_Register : " << endl;
			cout << " 3. DelimiterVarSize_Register : " << endl;
			cout << " 4. Salir : " << endl;
		
			char * unido3;



			cin >> opcion;

			Registro_1 * DelimiterVarSize_Register = new Registro_1();
			FixedSize_Register * FixedSize = new FixedSize_Register();
			KnownVarSize * KnownVarSizeR = new KnownVarSize();

			switch (opcion)
			{
			case 1:

				
				int case1;
				cout << " 1. Agregar Datos : " << endl;

				cout << " 2. Imprimir : " << endl;

				cin >> case1;
				switch (case1)
				{
					char * unido2;
				case 1:
					system("cls");

					FixedSize->abrirArchivo((char *)"FixedSize_Register.dat");

					char trabajo[20];
					char nombre[30];
					int codigo;
					double salario;

					cout << " Codigo: ";
					cin >> codigo;
					cout << " Nombre: ";
					cin >> nombre;
					cout << "Salario ";
					cin >> salario;
					cout << " Trabajo: ";
					cin >> trabajo;

					 unido2 = toCharFixedSize_Register(codigo, nombre, salario, trabajo);


					FixedSize->fromChar(unido2);
					FixedSize->escribirRegistro();
					FixedSize->cerrarArchivo();


					break;

					case 2 :

						
						int posicion;
						cout << "Ingrese la posición: " << endl;
						cin >> posicion;

						FixedSize->abrirArchivo((char *)"FixedSize_Register.dat");

						FixedSize->leerRegistro(posicion);
						FixedSize->mostrarRegistro();
						FixedSize->cerrarArchivo();

						break;


				}
				
				break;
			case 2:
			

				int case2;
				cout << " 1. Agregar Datos : " << endl;

				cout << " 2. Imprimir : " << endl;

				cin >> case2;
				switch (case2)
				{
				case 1:
					system("cls");

					KnownVarSizeR->abrirArchivo((char *)"KnownVarSize.dat");

					char trabajo[20];
					char nombre[30];
					int codigo;
					double salario;

					cout << " Codigo: ";
					cin >> codigo;
					cout << " Nombre: ";
					cin >> nombre;
					cout << "Salario ";
					cin >> salario;
					cout << " Trabajo: ";
					cin >> trabajo;
					tamKnownVarSizeR = tamanoRegistrotamKnownVarSizeR(nombre, trabajo);
					unido3 = toCharKnownVarSizeR(codigo, sizeof(nombre), nombre, salario,sizeof(trabajo), trabajo);


					KnownVarSizeR->fromChar(unido3);
					KnownVarSizeR->escribirRegistro();
					KnownVarSizeR->cerrarArchivo();


					break;

				case 2:

					KnownVarSizeR->abrirArchivo((char *)"KnownVarSize.dat");
					int posicion;
					cout << "Ingrese la posición: " << endl;
					cin >> posicion;
					KnownVarSizeR->leerRegistro(posicion);
					KnownVarSizeR->mostrarRegistro();
					KnownVarSizeR->cerrarArchivo();

					break;


				}

				break;

			case 3:
			
				int case3;

				cout << " 1. Agregar Datos : " << endl;

				cout << " 2. Imprimir : " << endl;

				cin >> case3;
				switch (case3)
				{
				case 1 :
					system("cls");
					
					DelimiterVarSize_Register->abrirArchivo();
		
					char trabajo[30];
					char nombre[30];
					int codigo;
					double salario;

					cout << " Codigo: " ;
					cin >> codigo;
					cout << " Nombre: ";
					cin >> nombre ;
					cout << "Salario " ;
					cin >> salario;
					cout << " Trabajo: ";
					cin >> trabajo;
					
					a= tamanoRegistro(nombre, trabajo);
					char * unido = toChar(codigo,nombre,salario,trabajo);


					DelimiterVarSize_Register->fromChar(unido);
					DelimiterVarSize_Register->escribirRegistro();
					DelimiterVarSize_Register->cerrarArchivo();
					

					break;

				//case 2 :

				//	//DelimiterVarSize_Register->abrirArchivo();
				//	///*int posicion;
				//	//cout << "Ingrese la posición: " << endl;
				//	//cin >> posicion;
				//	//DelimiterVarSize_Register->leerRegistro(posicion);*/
				//	//DelimiterVarSize_Register->mostrarRegistro();
				//	//DelimiterVarSize_Register->cerrarArchivo();

				//	break;

			
				}





				break;

			

			}

		} while (opcion != 4);





		

}

