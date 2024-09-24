#include "Date.h"		//Para acceder a Fecha

#include <iostream>
#include <fstream>		//Para lectura y escritura en archivo
#include <string>		//Para usar string
#include <windows.h>	//Para usar caracteres en Español

struct Ejemplar {
	int codigo;
	char tipo;
	std::string nombre;
};

struct Prestamo {
	int codigo;
	Date fecha;
	std::string nombre;
};


bool LeerCatalogo(const std::string& catalogo) {

	std::ifstream input;
	input.open(catalogo);
	
	if (!input.is_open()) {
		std::cout << "No se ha leer el catálogo" << std::endl;
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


int main()
{
	if (LeerCatalogo("catalogo.txt")) {
		std::cout << "patata";
	}

	return 0;
}

