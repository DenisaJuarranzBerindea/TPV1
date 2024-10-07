#pragma once

#include "Prestamo.hpp"
#include "Catalogo.hpp"
#include "checkML.h"

class ListaPrestamo
{
	// atributos privados
private:
	// array dinamico ArrayPrestamo de punteros a estructuras de tipo Prestamo
	Prestamo* pres;
	int tamReal;
	int tam;

	// metodos publicos
public:
	// constructora
	ListaPrestamo();
	ListaPrestamo(std::istream& const e, const Catalogo& c);

	// destructora
	~ListaPrestamo();

	// operador salida
	friend std::ostream& operator<<(std::ostream& out, const ListaPrestamo&);

	// lectura
	bool leerPrestamos(Catalogo& catalogo); // esto ya no se lee aqui

	// metodos
	void ordenarPrestamos();
	void insertaPrestamo(const Prestamo&);

	// render
	void mostrarPrestamos();
};