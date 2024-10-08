#pragma once

#include <string>

class Ejemplar
{
private:
	int codigo;

	enum Tipo
	{
		Libro, Audiovisual, Juego
	};
	int t;

	std::string nombre;

	bool disponible;

public:
	// Constructoras
	Ejemplar();
	Ejemplar(int c, char t, std::string n);

	// Operadores
	// Lectura
	friend std::istream& operator>>(std::istream& in, Ejemplar& e);
	// Escritura
	friend std::ostream& operator<<(std::ostream& out, const Ejemplar& e);

	// Getters y Setters
	void setCodigo(int c) { codigo = c; }
	int getCodigo() { return codigo; }

	void setTipo(int tipo) { t = Tipo(tipo); }
	int getTipo() { return Tipo(t); }

	void setNombre(std::string n) { nombre = n; }
	std::string getNombre() const { return nombre; }

	// Métodos
	void presta();
	void devuelve();
};