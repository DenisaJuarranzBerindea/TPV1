#include "Catalogo.hpp"

#include <fstream>
#include <iostream>

Catalogo::Catalogo()
{

}

Catalogo::Catalogo(std::istream&)
{

}

Catalogo::~Catalogo()
{
    delete[] ejs;
    ejs = nullptr;
}

bool Catalogo::leerCatalogo()
{
    // Abre el archivo para la lectura
    std::fstream catalogo("catalogo.txt");

    int cod; // Código
    char tc; // Tipo, char
    int ti; //Tipo, int, para cuestiones internas
    std::string n; // Nombre

    // Tamaño
    catalogo >> tamReal;

    // Array dinámico
    ejs = new Ejemplar[tamReal];

    // Lee los datos
    for (int i = 0; i < tamReal; i++)
    {
        catalogo >> cod;  
        ejs[i].setCodigo(cod); 

        catalogo >> tc; 

        if (tc == 'L') ti = 0;// Libro
        else if (tc == 'A') ti = 1; // Audiovisual
        else ti = 2; // Juego

        ejs[i].setTipo(ti); 

        std::getline(catalogo, n);
        ejs[i].setNombre(n);
    }

    return catalogo.is_open(); 
}

//Búsqueda binaria
Ejemplar* Catalogo::buscarEjemplar(const int cod, int ini, int fin) 
{
    int elems = fin - ini;

    if (elems == 0) return nullptr;
    if (elems == 1) return getEjemplar(ini);

    int mit = (ini + fin) / 2;

    if (cod >= getEjemplar(mit)->getCodigo()) // Dcha
    {
        return buscarEjemplar(cod, mit, fin);
    }
    if (cod < getEjemplar(mit)->getCodigo()) // Izqda
    {
        return buscarEjemplar(cod, ini, mit);
    }

    return nullptr;
}