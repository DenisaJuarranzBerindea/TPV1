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
    ListaPrestamo listaPrestamo;

    // carga catalogo y lista prestamos
    catalogo.leerCatalogo();
    listaPrestamo.leerPrestamos(catalogo);

    // ordena prestamos
    listaPrestamo.ordenarPrestamos();

    // mostrar un men� con opciones para:
    std::cout << "Seleccione::" << std::endl;
    std::cout << "a) Mostrar cat�logo" << std::endl;
    std::cout << "b) Mostrar pr�stamos" << std::endl;
    std::cout << "c) Insertar ejemplar" << std::endl;
    std::cout << "d) Prestar ejemplar" << std::endl;
    std::cout << "e) Devolver ejemplar" << std::endl;
    std::cout << "f) Salir" << std::endl;

    char input = ' ';
    std::cin >> input;
    if (input == 'a')
    {
        system("cls");
        catalogo.mostrarCatalogo();
    }
    else if (input == 'b')
    {
        system("cls");
        listaPrestamo.mostrarPrestamos();
    }
    else if (input == 'c')
    {
        system("cls");

        char tipo = ' ';
        std::string nombre;

        std::cout << "De que tipo es tu ejemplar: L) Libros / A) Audiovisual / J) Juegos" << std::endl;
        std::cin >> tipo;
        std::cout << "Inserte el nombre del ejemplar" << std::endl;
        //std::getline(std::cin, nombre);
        std::cin >> nombre;
        std::cout << "nombre: " << nombre << std::endl;

        catalogo.insertaEjemplar(tipo, nombre);
    }
    else if (input == 'd')
    {
        system("cls");

        std::cout << "Inserta el codigo del ejemplar a prestar" << std::endl;
        int cod = 0;
        std::cin >> cod;
        Ejemplar* e = catalogo.buscarEjemplar(cod, 0, catalogo.getTam());

        Date hoy = Date();

        std::cout << "Inserta tu numero de usuario" << std::endl;
        int u = 0;
        std::cin >> u;

        Prestamo p = Prestamo(e, hoy, u);

        listaPrestamo.insertaPrestamo(p);

        listaPrestamo.ordenarPrestamos();
    }
    else if (input == 'e')
    {
        system("cls");

        std::cout << "Inserta el codigo del ejemplar a prestar" << std::endl;
        int cod = 0;
        std::cin >> cod;
        Ejemplar* e = catalogo.buscarEjemplar(cod, 0, catalogo.getTam());

        Date hoy = Date();

        std::cout << "Inserta tu numero de usuario" << std::endl;
        int u = 0;
        std::cin >> u;

        Prestamo p = Prestamo(e, hoy, u);

        listaPrestamo.insertaPrestamo(p);

        listaPrestamo.ordenarPrestamos();
    }
    else if (input == 'f')
    {
        exit(0);
    }

    return 0;
}