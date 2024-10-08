#include "Date.hpp"
#include "Ejemplar.hpp"
#include "checkML.h"
#include "Catalogo.hpp"

class Prestamo
{
	
private:
	Ejemplar* ejemplar;

	Date fecha;
	Date fechaDevolucion;

	int user;

public:
	// Constructoras
	Prestamo();
	Prestamo(Ejemplar* e, Date f, int u);

	// Operadores
	// Lectura
	friend std::istream& operator>>(std::istream& in, Prestamo& p);
	// Escritura
	friend std::ostream& operator<<(std::ostream& out, const Prestamo& p);
	// Comparación
	bool operator<(const Prestamo& prestamo) const;

	// Getters y Setters
	void setUser(int usuario) { user = usuario; }
	char getUser() { return user; }

	void setDate(Date f) { fecha = f; }
	void setDateDevol(Date f) { fechaDevolucion = f; }

	Date getDate() { return fecha; }
	Date getDateDevol() const { return fecha + duracionPrestamo((*this->ejemplar).getTipo()); }

	void setEjemplar(Ejemplar* e) { ejemplar = e; }
	Ejemplar* getEjemplar() { return ejemplar; }

	// Métodos
	int duracionPrestamo(int tipo) const
	{
		// Libros
		if (tipo == 0) return 30;

		// Audiovisual
		if (tipo == 1) return 7;

		// Juegos
		if (tipo == 2) return 14;
	}

	//Lectura
	void leePrestamo(const Catalogo&);
};