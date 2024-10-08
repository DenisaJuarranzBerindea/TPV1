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
}

bool Catalogo::leerCatalogo()
{
    // abre el archivo coches.txt
    std::fstream catalogoRead("catalogo.txt");

    int c; // codigo del ejemplar
    char tc; // tipo del ejemplar, char
    int ti;
    std::string n; // nombre del ejemplar

    // saca el tama�o de la lista de coches
    catalogoRead >> tamReal;

    // crea el array dinamico
    ejs = new Ejemplar[tamReal];

    // bucle para leer los datos
    for (int i = 0; i < tamReal; i++)
    {
        catalogoRead >> c; // lee el codigo
        ejs[i].setCodigo(c); // lo mete

        catalogoRead >> tc; // lee el tipo

        if (tc == 'L') // libros
        {
            ti = 0;
        }
        else if (tc == 'A') // audiovisual
        {
            ti = 1;
        }
        else // juegos
        {
            ti = 2;
        }

        ejs[i].setTipo(ti); // lo mete 

        std::getline(catalogoRead, n); // lee el nombre
        ejs[i].setNombre(n); // lo mete
    }

    return catalogoRead.is_open(); // true -> archivo catalogo abierto / false -> error
}

Ejemplar* Catalogo::buscarEjemplar(int cod, int ini, int fin) const
{
    int elems = fin - ini;

    if (elems == 0) return nullptr; // vacio
    if (elems == 1) return getEjemplar(ini);

    int mit = (ini + fin) / 2;

    if (cod >= getEjemplar(mit)->getCodigo()) // busca derecha
    {
        return buscarEjemplar(cod, mit, fin);
    }
    if (cod < getEjemplar(mit)->getCodigo()) // busca izq
    {
        return buscarEjemplar(cod, ini, mit);
    }

    return nullptr;
}