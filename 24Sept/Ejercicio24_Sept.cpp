#include "Date.h"		//Para acceder a Fecha

#include <iostream>
#include <fstream>		//Para lectura y escritura en archivo
#include <string>		//Para usar string
#include <windows.h>	//Para usar caracteres en Español
#include <algorithm>

struct Ejemplar {
	int codigo;
	char tipo;
	std::string nombre;
};

struct Prestamo {
	int codigo;
	Date fecha;
	int usuario;
};

struct Catalogo {
	int tamanyo;



};


bool LeerCatalogo(const std::string& catalogo) {

	std::ifstream input;
	input.open(catalogo);
	
	if (!input.is_open()) {
		std::cout << "No se ha podido leer el archivo" << std::endl;
		return false;
	}
	else {
		int n = 0;
		std::cin >> n; //Leemos el número de ejemplares

		for (int i = 0; i < n; i++)
		{
			Ejemplar* ejemplar = new Ejemplar();
			std::cin >> ejemplar->codigo >> ejemplar->tipo;
			std::getline(std::cin, ejemplar->nombre);
		}

		return true;
	}

	input.close();
}

bool LeerPrestamos(const std::string& prestamo) {


	std::ifstream input;
	input.open(prestamo);

	if (!input.is_open()) {
		std::cout << "No se ha podido leer el archivo" << std::endl;
		return false;
	}
	else {
		int n = 0;
		std::cin >> n; //Leemos el número de ejemplares

		for (int i = 0; i < n; i++)
		{
			Prestamo* prestamos = new Prestamo();
			std::cin >> prestamos->codigo >> prestamos->fecha >> prestamos->usuario;
		}

		return true;
	}

	input.close();
}

void ordenarPrestamos() {
	//Sort(puntero a primer elemento de la lista prestamo, puntero a final lista prestamo + 1)


}



int main()
{
	SetConsoleOutputCP(CP_UTF8);


	if (!LeerCatalogo("catalogo.txt")) {
		std::cout << "patata";
	}

	return 0;
}

