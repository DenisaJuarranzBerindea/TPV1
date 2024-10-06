#include "Date.hpp"		//Para acceder a Fecha

#include <iostream>
#include <fstream>		//Para lectura y escritura en archivo
#include <string>		//Para usar string
#include <windows.h>	//Para usar caracteres en Español
#include <algorithm>	//Para el sort
#include <vector>		//Para el sort también
#include <ctime>		//Para usar la fecha actual	

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

//Método auxiliar para calcular la fecha de fin del prestamo segun el tipo de ejemplar
Date SacaFechaFin(const Prestamo& prestamo) {

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

bool operator<(const Prestamo& izdo, const Prestamo& dcho) {
	
	return SacaFechaFin(izdo) < SacaFechaFin(dcho);
}

void OrdenarPrestamos(ListaPrestamos& list) {

	std::vector<Prestamo> prestamos(list.tam);
	

	for (int i = 0; i < prestamos.size(); i++) {
		prestamos[i] = list.pres[i];
	}

	//Ordenamos por fecha de finalización
	std:sort(prestamos.begin(), prestamos.end());

	//Guardamos el orden del vector en la lista
	for (int i = 0; i < list.tam; i++)
	{
		//Rellenamos el array del catálogo
		list.pres[i].ej = prestamos[i].ej;
		list.pres[i].fecha = prestamos[i].fecha;
		list.pres[i].usuario = prestamos[i].usuario;
	}
}

int DiferenciaFechas(Prestamo& prestamo) {

	Date hoy = Date();

	int diferencia = SacaFechaFin(prestamo).diff(hoy);

	return diferencia;
}

int Penalizacion(Prestamo& prestamo) {

	if (DiferenciaFechas(prestamo) < 0) {
		return DiferenciaFechas(prestamo) * -2;
	}
	else {
		return 0;
	}
	
}

void MostrarPrestamos(ListaPrestamos* list) {

	for (int i = 0; i < list->tam; i++) {
		std::cout << list->pres[i].fecha << " (en ";

		if (DiferenciaFechas(list->pres[i]) >= 0 && DiferenciaFechas(list->pres[i]) <= 9){
			std::cout << "   ";
		}
		else if ((DiferenciaFechas(list->pres[i]) > 9 && DiferenciaFechas(list->pres[i]) <= 99) ||
			(DiferenciaFechas(list->pres[i]) > -10 && DiferenciaFechas(list->pres[i]) <= -1)) {
			std::cout << "  ";
		}
		else if (DiferenciaFechas(list->pres[i]) < -9 && DiferenciaFechas(list->pres[i]) >= -99) {
			std::cout << " ";
		}

		std::cout << DiferenciaFechas(list->pres[i]) << " días) " << list->pres[i].ej->nombre;

		if (Penalizacion(list->pres[i]) > 0) {
			std::cout << " (" << Penalizacion(list->pres[i]) << " días de penalización)";
		}
		
		std::cout << std::endl;
	}
}

int main()
{
	SetConsoleOutputCP(CP_UTF8);

	Catalogo* cat = new Catalogo();
	LeerCatalogo("catalogo.txt", cat);
	ListaPrestamos* list = new ListaPrestamos();
	LeerPrestamos("prestamos.txt", list, cat);

	OrdenarPrestamos(*list);

	MostrarPrestamos(list);

	return 0;
}

