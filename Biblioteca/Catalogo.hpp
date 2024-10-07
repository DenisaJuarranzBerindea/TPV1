#pragma once

#include "Ejemplar.hpp"
#include "checkML.h"

class Catalogo
{
	// atributos privados
private:
	// array dinamico ArrayCatalogo de punteros a estructuras de tipo Ejemplar
	Ejemplar* ejs;
	int tamReal;
	int tam;

	// metodos publicos
public:
	// constructora
	Catalogo();
	Catalogo(std::istream&);

	// destructora
	~Catalogo();

	// lectura
	bool leerCatalogo();

	// Getters
	int getTam() { return tamReal; }
	Ejemplar* getEjemplar(int pos) const { return &ejs[pos]; }

	// metodos
	Ejemplar* buscarEjemplar(int cod, int ini, int fin) const;
	void insertaEjemplar(char tipo, std::string nombre);

	// render
	void mostrarCatalogo();
};