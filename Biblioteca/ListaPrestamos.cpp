#include "ListaPrestamos.hpp"

#include <algorithm>
#include <fstream>
#include <cmath>
#include <vector>

ListaPrestamos::ListaPrestamos()
{

}

ListaPrestamos::ListaPrestamos(std::istream& const e, const Catalogo& c)
{

}

ListaPrestamos::~ListaPrestamos()
{
    delete[] pres;
    pres = nullptr;
}

bool ListaPrestamos::leerPrestamos(Catalogo& catalogo)
{
    // abre el archivo coches.txt
    std::fstream prestamoRead("prestamos.txt");

    int c; // codigo del ejemplar
    int u; // usuario del prestamo
    Date fecha; // fecha del prestamo

    // saca el tamaño de la lista de coches
    prestamoRead >> tamReal;

    // crea el array dinamico
    pres = new Prestamo[tamReal];

    // bucle para leer los datos
    for (int i = 0; i < tamReal; i++)
    {
        prestamoRead >> c; // lee el codigo
        pres[i].setEjemplar(catalogo.buscarEjemplar(c, 0, catalogo.getTam())); // lo mete

        prestamoRead >> fecha; // lee la fecha
        pres[i].setDate(fecha); // la mete

        prestamoRead >> u; // lee el user
        pres[i].setUser(u); // lo mete 
    }

    return prestamoRead.is_open(); // true -> archivo prestamos abierto / false -> error  
}

void ListaPrestamos::ordenarPrestamos()
{
    Prestamo* a = pres + 8;
    std::sort(pres, a);
}

void ListaPrestamos::insertaPrestamo(const Prestamo&)
{
    // insertar en el hueco que le corresponde por orden de código

}

void ListaPrestamos::devuelvePrestamo(const Prestamo&)
{

}

void ListaPrestamos::mostrarPrestamos()
{
    int quedan;
    Date prest;
    Date devol;
    Date* hoy = new Date();

    for (int i = 0; i < tamReal; i++)
    {
        prest = pres[i].getDate();
        devol = pres[i].getDateDevol();
        std::cout << (devol);
        std::cout << " ";
        quedan = (devol.diff(*hoy));
        std::cout << "(en  " << quedan << " dias)";
        std::cout << " ";
        std::cout << pres[i].getEjemplar()->getNombre();
        if (quedan < 0)
        {
            std::cout << " ";
            std::cout << "(" << abs(quedan) * 2 << " dias de penalizacion)";
        }
        std::cout << std::endl;
    }

    delete hoy;
}