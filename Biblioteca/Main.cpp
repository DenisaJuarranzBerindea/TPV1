//Denisa Juarranz Berindea

#include "Catalogo.hpp"
#include "ListaPrestamos.hpp"
#include <windows.h>
#include <iostream>
#include <string>

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    Catalogo catalogo;
    ListaPrestamos listaPrestamos;

    // Lee Catálogo y ListaPréstamos
    catalogo.leerCatalogo();
    listaPrestamos.leerPrestamos(catalogo);

    // Ordena los préstamos
    listaPrestamos.ordenarPrestamos();

    // Menú
    std::cout << "Seleccione::" << std::endl;
    std::cout << "a) Mostrar catálogo" << std::endl;
    std::cout << "b) Mostrar préstamos" << std::endl;
    std::cout << "c) Insertar ejemplar" << std::endl;
    std::cout << "d) Prestar ejemplar" << std::endl;
    std::cout << "e) Devolver ejemplar" << std::endl;
    std::cout << "f) Salir" << std::endl;

    // Leemos opción y accionamos en consecuencia
    char input = ' ';
    std::cin >> input;
    if (input == 'a')
    {
        catalogo.mostrarCatalogo();
    }
    else if (input == 'b')
    {
        listaPrestamos.mostrarPrestamos();
    }
    else if (input == 'c')
    {
        char tipo = ' ';
        std::string nombre;

        std::cout << "Tipo de ejemplar L) Libros / A) Audiovisual / J) Juegos: " << std::endl;
        std::cin >> tipo;
        std::cout << "Inserte el nombre del ejemplar: " << std::endl;
        std::getline(std::cin, nombre);
        std::cout << "Nombre: " << nombre << std::endl;

        catalogo.insertaEjemplar(tipo, nombre);
    }
    else if (input == 'd')
    {
        std::cout << "Inserta el código del ejemplar: " << std::endl;
        int cod = 0;
        std::cin >> cod;
        Ejemplar* e = catalogo.buscarEjemplar(cod, 0, catalogo.getTam());

        Date hoy = Date();

        std::cout << "Inserta tu usuario: " << std::endl;
        int u = 0;
        std::cin >> u;

        Prestamo p = Prestamo(e, hoy, u);

        listaPrestamos.insertaPrestamo(p);

        listaPrestamos.ordenarPrestamos();
    }
    else if (input == 'e')
    {
        std::cout << "Inserta el código del ejemplar: " << std::endl;
        int cod = 0;
        std::cin >> cod;
        Ejemplar* e = catalogo.buscarEjemplar(cod, 0, catalogo.getTam());

        Date hoy = Date();

        std::cout << "Inserta tu usuario: " << std::endl;
        int u = 0;
        std::cin >> u;

        Prestamo p = Prestamo(e, hoy, u);

        listaPrestamos.insertaPrestamo(p);

        listaPrestamos.ordenarPrestamos();
    }
    else if (input == 'f')
    {
        exit(0);
    }

    return 0;
}