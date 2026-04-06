#include <iostream>
#include <fstream>

#include "GestorSanciones.h"
#include "tipos.h"

int main() {

    // Guardamos el nombre de los ficheros por si necesitamos usarlos mas adelante
    cadena sanciones = "Utils/sanciones.dat";
    cadena radares = "Utils/radares";
    cadena vehiculos = "Utils/coches.dat";
    cadena tipos = "Utils/tipossanciones.dat";

    // Creamos el objeto
    GestorSanciones gs(sanciones, radares, vehiculos, tipos);

    // Comprobamos que se haya abierto correctamente
    if (!gs.getFicheroSancionesActivo()) {
        std::cout << "\n\nERROR -- ERROR AL ABRIR EL FICHERO\n\n";
        exit(EXIT_FAILURE);
    }

    int opcion = 0;
    coche annadir = {};

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
        std::cout << "      8. Mostrar Lecturas de Radar" << std::endl;
        std::cout << "      0. Salir" << std::endl;
        std::cout << std::endl;
        std::cout << "Seleccione una opción: "; std::cin >> opcion;

        if (opcion < 0 || opcion > 8) {
            std::cout << "ERROR: Por favor, introduzca una opción válida (0-7)" << std::endl;
        }

        switch (opcion) {
            case 0:
                break;
            case 1:
                cadena matriculaConsultar;
                std::cout << std::endl;
                std::cout << " ***** CONSULTA VEHÍCULO *****" << std::endl;
                std::cout << " =============================" << std::endl;
                std::cout << " Por favor, introduzca la matrícula a consultar: ";
                std::cin >> matriculaConsultar;
                gs.mostrarVehiculo(matriculaConsultar);

                break;
            case 2:
                std::cout << std::endl;
                std::cout << " ***** AÑADIR VEHÍCULO *****" << std::endl;
                std::cout << " ===========================" << std::endl;
                std::cout << "  - Introduzca matrícula: ";
                std::cin >> annadir.matricula;
                // std::cout << "  - Introduzca Fecha ITV: ";
                // std::cin >> anadir.fechaitv;
                std::cout << "  - Introduzca marca: ";
                std::cin >> annadir.marca;
                std::cout << "  - Introduzca modelo: ";
                std::cin >> annadir.modelo;

                // Añadimos el vehñiculo
                gs.anyadirVehiculo(annadir);

                break;
            case 3:
                gs.mostrarRadares();
                break;
            case 4:
                // Consultamos al usuario el código del radar que quiere ver
                int codigo;
                std::cout << std::endl;
                std::cout << " ***** CONSULTA RADAR ***** " << std::endl;
                std::cout << " ========================== " << std::endl;
                std::cout << " Por favor, introduzca el codigo a consultar: ";
                std::cin >> codigo;
                gs.mostrarRadar(codigo);
                break;
            case 5:
                // Consultamos al usuario el código del radar que quiere ver
                int cod5;
                std::cout << std::endl;
                std::cout << " ***** CONSULTA LECTURAS RADAR ***** " << std::endl;
                std::cout << " =================================== " << std::endl;
                std::cout << " Por favor, introduzca el codigo a consultar: ";
                std::cin >> cod5;
                gs.mostrarLecturasRadar(cod5);
                break;
            case 6:
                std::cout << std::endl << "Opción seleccionada: Mostrar Ficheros de Sanciones" << std::endl << std::endl;
                break;
            case 7:
                int anno;
                std::cout << std::endl;
                std::cout << " ***** CONSULTA SANCIONES ***** " << std::endl;
                std::cout << " ============================== " << std::endl;
                std::cout << " Por favor, introduzca el año a consultar: ";
                std::cin >> anno;
                std::cout << std::endl;
                gs.mostrarTipoSancion(anno);
                break;
            case 8:
                int codRa;
                std::cout << std::endl;
                std::cout << " ***** CONSULTA LECTURAS ***** " << std::endl;
                std::cout << " ============================== " << std::endl;
                std::cout << " Por favor, introduzca el codigo del radar a consultar: ";
                std::cin >> codRa;
                std::cout << std::endl;
                gs.mostrarLecturasRadar(codRa);
                break;
            default:
                break;
        }

    }while(opcion != 0);

    return 0;
}
