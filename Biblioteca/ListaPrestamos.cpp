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
    // Abre el archivo
    std::fstream prestamo("prestamos.txt");

    int c; // Código
    int u; // Usuario
    Date fecha; // Fecha

    // Tamaño
    prestamo >> tamReal;

    // Array dinámico
    pres = new Prestamo[tamReal];

    // Lee los datos
    for (int i = 0; i < tamReal; i++)
    {
        prestamo >> c; 
        pres[i].setEjemplar(catalogo.buscarEjemplar(c, 0, catalogo.getTam()));

        prestamo >> fecha;
        pres[i].setDate(fecha);

        prestamo >> u;
        pres[i].setUser(u);
    }

    return prestamo.is_open(); 
}

void ListaPrestamos::ordenarPrestamos()
{
    Prestamo* a = pres + tamReal;
    std::sort(pres, a);
}

void ListaPrestamos::insertaPrestamo(const Prestamo&)
{
    tamReal++;
}

void ListaPrestamos::devuelvePrestamo(const Prestamo&)
{
    tamReal--;
}

void ListaPrestamos::mostrarPrestamos()
{
    int quedan;
    Date prest;
    Date devol;
    Date* hoy = new Date();

    for (int i = 0; i < tamReal; i++) {
        prest = pres[i].getDate();
        devol = pres[i].getDateDevol();
        std::cout << (devol) ;

        quedan = (devol.diff(*hoy));
        std::cout << "(en ";
        if (quedan >= 0 && quedan <= 9) {
            std::cout << "   ";
        }
        else if ((quedan > 9 && quedan <= 99) || (quedan > -10 && quedan <= -1)) {
            std::cout << "  ";
        }
        else if (quedan < -9 && quedan >= -99) {
            std::cout << " ";
        }
        std::cout << quedan << " días) ";
        std::cout << pres[i].getEjemplar()->getNombre();

        if (quedan < 0)
        {
            std::cout << " ";
            std::cout << "(" << abs(quedan) * 2 << " días de penalización)";
        }
        std::cout << std::endl;
    }

    delete hoy;
}