#include "Ejemplar.hpp"
#include "checkML.h"

class Catalogo
{

private:
	// Array din�mico con punteros en tipo Ejemplar
	Ejemplar* ejs;
	int tamReal;
	int tam;


public:
	// Constructoras
	Catalogo();
	Catalogo(std::istream&);

	// Destructora
	~Catalogo();

	// Lectura
	bool leerCatalogo();

	// Getters
	int getTam() { return tamReal; }

	Ejemplar* getEjemplar(int pos) const { return &ejs[pos]; }

	// M�todos
	Ejemplar* buscarEjemplar(int cod, int ini, int fin);
	void insertaEjemplar(char tipo, std::string nombre);

	// Render
	void mostrarCatalogo();
};