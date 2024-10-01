#include "Date.hpp"		//Para acceder a Fecha

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
	Date fecha;
	int usuario;
	Ejemplar* ej;
};

struct Catalogo {
	int tam;
	int tamReal;
	Ejemplar* ejs;
};

struct ListaPrestamos {
	int tam;
	int tamReal;
	Prestamo* pres;
};


bool LeerCatalogo(const std::string& archivo, Catalogo* cat) {

	std::ifstream input;
	input.open(archivo);
	
	if (!input.is_open()) {
		return false;
	}
	else {
;
		input >> cat->tam; //Leemos el número de ejemplares
		cat->ejs = new Ejemplar[cat->tam];
		cat->tamReal = 0;

		Ejemplar* ej = new Ejemplar();

		for (int i = 0; i < cat->tam; i++)
		{
			input >> ej->codigo >> ej->tipo;
			std::getline(input, ej->nombre);

			//Rellenamos el array del catalogo
			cat->ejs[i].codigo = ej->codigo;
			cat->ejs[i].tipo = ej->tipo;
			cat->ejs[i].nombre = ej->nombre;

			cat->tamReal++;
		}

		//Vaciamos memoria
		delete ej;
		ej = nullptr;

		return true;
	}

	input.close();

}

Ejemplar* BuscarEjemplar(int cod, Catalogo* cat, int ini, int fin) {

	Ejemplar* ej = new Ejemplar();

	int dif = fin - ini;

	//No hay ejemplares
	if (dif == 0) {
		return nullptr;
	}
	else if (dif == 1) {
		if (cat->ejs[ini].codigo == cod) {
			ej->codigo = cat->ejs[ini].codigo;
			ej->tipo = cat->ejs[ini].tipo;
			ej->nombre = cat->ejs[ini].nombre;

			return ej;
			//Vaciamos memoria
			delete ej;
			ej = nullptr;
		}
		else {
			return nullptr;
		}
	}

	int mitad = (ini + fin) / 2;

	if (cat->ejs[mitad].codigo < cod) {
		BuscarEjemplar(cod, cat, mitad, fin);
	}
	else if (cat->ejs[mitad].codigo > cod) {
		BuscarEjemplar(cod, cat, ini, mitad);
	}
	else if (cat->ejs[mitad].codigo == cod) {
		ej->codigo = cat->ejs[mitad].codigo;
		ej->tipo = cat->ejs[mitad].tipo;
		ej->nombre = cat->ejs[mitad].nombre;

		return ej;
		//Vaciamos memoria
		delete ej;
		ej = nullptr;
	}

}

bool LeerPrestamos(const std::string& archivo, ListaPrestamos* list, Catalogo* cat) {

	std::ifstream input;
	input.open(archivo);

	if (!input.is_open()) {
		return false;
	}
	else {
		
		input >> list->tam; //Leemos el número de prestados
		list->pres = new Prestamo[list->tam];
		list->tamReal = 0;

		Prestamo* pr = new Prestamo();

		for (int i = 0; i < list->tam; i++)
		{
			int cod;
			input >> cod >> pr->fecha >> pr->usuario ;
			
			//Rellenamos el array del catalogo
			list->pres[i].ej = BuscarEjemplar(cod, cat, 0, cat->tam);
			list->pres[i].fecha = pr->fecha;
			list->pres[i].usuario = pr->usuario;
		}

		//Vaciamos memoria
		delete pr;
		pr = nullptr;

		return true;
	}

	input.close();
}

bool operator<(const Prestamo& izdo, const Prestamo& dcho) {
	
	return izdo.fecha < dcho.fecha;
}

Date SacaFechaFin(Prestamo& prestamo) {

	if (prestamo.ej->tipo == 'L'){
		return prestamo.fecha + 30;
	}
	else if (prestamo.ej->tipo == 'J') {
		return prestamo.fecha + 14;
	}
	else if (prestamo.ej->tipo == 'A') {
		return prestamo.fecha + 7;
	}
}

void OrdenarPrestamos(ListaPrestamos* list) {


	for (int i = 0; i < list->tam; i++) {

		if (SacaFechaFin(list->pres[i + 1]) < SacaFechaFin(list->pres[i])) {
			Prestamo* aux = new Prestamo();
			aux->ej = list->pres[i].ej;
			aux->fecha = list->pres[i].fecha;
			aux->usuario = list->pres[i].usuario;

			list->pres[i].ej = list->pres[i + 1].ej;
			list->pres[i].fecha = list->pres[i + 1].fecha;
			list->pres[i].usuario = list->pres[i + 1].usuario;

			list->pres[i + 1].ej = aux->ej;
			list->pres[i + 1].fecha = aux->fecha;
			list->pres[i + 1].usuario = aux->usuario;
		}
		 

	}




	////Vaciamos memoria
	//delete fechaFin;
	//fechaFin = nullptr;
}

int main()
{
	SetConsoleOutputCP(CP_UTF8);

	Catalogo* cat = new Catalogo();
	ListaPrestamos* list = new ListaPrestamos();

	if (LeerCatalogo("catalogo.txt", cat)) {
		std::cout << "BIEN" << std::endl;
	}
	else {
		std::cout << "No se ha podido leer el archivo." << std::endl;
	}

	Ejemplar* ejBusca = new Ejemplar();
	ejBusca = BuscarEjemplar(1201, cat, 0, cat->tam);
	std::cout << ejBusca << std::endl;
	if (ejBusca == nullptr) {
		std::cout << "Artículo no encontrado." << std::endl;
	}
	else {
		std::cout << ejBusca->codigo << " " << ejBusca->tipo << ejBusca->nombre << std::endl;
	}

	if (LeerPrestamos("prestamos.txt", list, cat)) {
		std::cout << "BIEN" << std::endl;
		for (int i = 0; i < list->tam; i++)
		{
			std::cout << list->pres[i].ej->codigo << " " << list->pres[i].fecha << " " << list->pres[i].usuario << std::endl;
		}
	}
	else {
		std::cout << "No se ha podido leer el archivo." << std::endl;
	}

	return 0;
}

