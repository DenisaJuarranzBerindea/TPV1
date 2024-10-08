#include "Prestamo.hpp"
#include "Catalogo.hpp"
#include "checkML.h"

class ListaPrestamos
{
private:
	// Array dinámico con punteros en tipo Prestamo
	Prestamo* pres;
	int tamReal;
	int tam;

public:
	// Constructoras
	ListaPrestamos();
	ListaPrestamos(std::istream& const e, const Catalogo& c);

	// Destructora
	~ListaPrestamos();

	// Operador escritura
	friend std::ostream& operator<<(std::ostream& out, const ListaPrestamos&);

	// Lectura
	bool leerPrestamos(Catalogo& catalogo); // esto ya no se lee aqui

	// Métodos
	void ordenarPrestamos();
	void insertaPrestamo(const Prestamo&);
	void devuelvePrestamo(const Prestamo&);

	// Render
	void mostrarPrestamos();
};