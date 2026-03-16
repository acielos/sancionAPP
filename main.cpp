#include <iostream>

#include "estructuras.h"

int main() {

    int opcion = 0;

    do {
        std::cout << "     Sanciones APP. Menú Principal     " << std::endl;;
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

    }while(opcion != 0);
}