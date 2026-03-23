#include <iostream>

#include "estructuras.h"

int main() {

    int opcion = 0;

    do {
        std::cout << "     Sanciones APP. Menú Principal     " << std::endl;
        std::cout << "=======================================" << std::endl;
        std::cout << "      1. Consulta Vehículo" << std::endl;
        std::cout << "      2. Añadir Vehículo" << std::endl;
        std::cout << "      3. Mostrar Radares" << std::endl;
        std::cout << "      4. Mostrar Radar" << std::endl;
        std::cout << "      5. Procesar Radar" << std::endl;
        std::cout << "      6. Mostrar Fichero de Sanciones" << std::endl;
        std::cout << "      7. Mostrar Cuantía de Sanción" << std::endl;
        std::cout << "      0. Salir" << std::endl;
        std::cout << std::endl;
        std::cout << "Seleccione una opción: "; std::cin >> opcion;

        if (opcion < 0 || opcion > 7) {
            std::cout << "ERROR: Por favor, introduzca una opción válida (0-7)" << std::endl;
        }

        switch (opcion) {
            case 0:
                break;
            case 1:
                std::cout << std::endl << "Opción seleccionada: Consulta de Vehiculo" << std::endl << std::endl;
                break;
            case 2:
                std::cout << std::endl << "Opción seleccionada: Añadir Vehiculo" << std::endl << std::endl;
                break;
            case 3:
                std::cout << std::endl << "Opción seleccionada: Mostrar Radares" << std::endl << std::endl;
                break;
            case 4:
                std::cout << std::endl << "Opción seleccionada: Mostrar Radar" << std::endl << std::endl;
                break;
            case 5:
                std::cout << std::endl << "Opción seleccionada: Procesar Radar" << std::endl << std::endl;
                break;
            case 6:
                std::cout << std::endl << "Opción seleccionada: Mostrar Ficheros de Sanciones" << std::endl << std::endl;
                break;
            case 7:
                std::cout << std::endl << "Opción seleccionada: Mostrar Cuantía de Sancion" << std::endl << std::endl;
                break;
        }

    }while(opcion != 0);

    return 0;
}